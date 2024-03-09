using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace VulkanParser
{
    internal class VulkanGenLoader
    {
        private VulkanParser m_parser = null;

        private void EmitTwoNewLines(StreamWriter outputFile)
        {
            outputFile.WriteLine();
            outputFile.WriteLine();
        }

        private void EmitFunctionPointers(string modifier, StreamWriter outputFile)
        {
            // Write function pointer declaration blocks
            foreach (var version in m_parser.Versions)
            {
                if (!version.HasAnyCommands)
                    continue;

                outputFile.WriteLine("#if defined({0})", version.Version);

                if (version.RootCommands.Count > 0)
                {
                    outputFile.WriteLine("// Root commands");
                    foreach (var command in version.RootCommands)
                    {
                        outputFile.WriteLine("{0}PFN_{1} {1};", modifier, command.Name);
                    }
                }

                if (version.InstanceCommands.Count > 0)
                {
                    outputFile.WriteLine("// Instance commands");
                    foreach (var command in version.InstanceCommands)
                    {
                        outputFile.WriteLine("{0}PFN_{1} {1};", modifier, command.Name);
                    }
                }

                if (version.DeviceCommands.Count > 0)
                {
                    outputFile.WriteLine("// Device commands");
                    foreach (var command in version.DeviceCommands)
                    {
                        outputFile.WriteLine("{0}PFN_{1} {1};", modifier, command.Name);
                    }
                }

                outputFile.WriteLine("#endif // defined({0})", version.Version);
            }
        }

        private void EmitHeader(string outputDir)
        {
            StreamWriter outputFile = new StreamWriter(Path.Combine(outputDir, "LoaderVk.h"), true);

            string topMatterStr = """
                //
                // This code is licensed under the MIT License (MIT).
                // THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
                // ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
                // IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
                // PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
                //
                // Author:  David Elder
                //

                #pragma once

                namespace Kodiak::VK
                {

                // Loads the function vkGetInstanceProcAddr, which is used to load VkInstance functions and (optionally) VkDevice functions.
                VkResult InitializeLoader();

                // Loads all the VkInstance and VkDevice functions for an given VkInstance.
                void LoadInstanceFunctions(VkInstance instance);

                // Loads only the VkInstance functions.  Must call LoadDeviceFunctions separately.
                void LoadInstanceFunctionsOnly(VkInstance instance);

                // Loads VkDevice functions for a given VkDevice.
                void LoadDeviceFunctions(VkDevice device);

                } // namespace Kodiak::VK
                """;

            // Write top matter
            outputFile.WriteLine(topMatterStr);
            EmitTwoNewLines(outputFile);
            outputFile.Flush();


            EmitFunctionPointers("extern ", outputFile);
            outputFile.Flush();

            outputFile.Close();
        }

        private void EmitInitializeLoaderImpl(StreamWriter outputFile)
        {
            string topMatterStr = """
                VkResult Kodiak::VK::InitializeLoader()
                {
                    HMODULE module = LoadLibraryA("vulkan-1.dll");
                    if (!module)
                    {
                        return VK_ERROR_INITIALIZATION_FAILED;
                    }

                    vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)(void(*)(void))GetProcAddress(module, "vkGetInstanceProcAddr");
                """;
            outputFile.WriteLine(topMatterStr);
            outputFile.WriteLine();
            outputFile.Flush();

            // Root functions
            foreach(var version in m_parser.Versions)
            {
                if (version.RootCommands.Count > 0)
                {
                    outputFile.WriteLine("#if defined({0})", version.Version);
                    foreach (var command in version.RootCommands)
                    {
                        if (command.DeclarationOnly)
                        {
                            continue;
                        }

                        string cmdName = command.Name;
                        outputFile.WriteLine("\t{0} = (PFN_{0})vkGetInstanceProcAddr(nullptr, \"{0}\");", cmdName);
                    }
                    outputFile.WriteLine("#endif // defined({0})", version.Version);
                }
            }
            outputFile.WriteLine();

            string bottomMatterStr = """
                    return VK_SUCCESS;
                }
                """;
            outputFile.WriteLine(bottomMatterStr);
        }

        private void EmitLoadInstanceFunctionsImpl(StreamWriter outputFile)
        {
            string topMatterStr = """
                void Kodiak::VK::LoadInstanceFunctions(VkInstance instance)
                {
                """;
            outputFile.WriteLine(topMatterStr);

            foreach(var version in m_parser.Versions)
            {
                if (version.InstanceCommands.Count > 0 || version.DeviceCommands.Count > 0)
                {
                    outputFile.WriteLine("#if defined({0})", version.Version);

                    if (version.InstanceCommands.Count > 0)
                    {
                        outputFile.WriteLine("\t// Instance commands");
                        foreach(var command in version.InstanceCommands)
                        {
                            if (command.DeclarationOnly)
                            {
                                continue;
                            }

                            string cmdName = command.Name;
                            outputFile.WriteLine("\t{0} = (PFN_{0})vkGetInstanceProcAddr(instance, \"{0}\");", cmdName);
                        }
                    }

                    if (version.DeviceCommands.Count > 0)
                    {
                        outputFile.WriteLine("\t// Device commands");
                        foreach (var command in version.DeviceCommands)
                        {
                            if (command.DeclarationOnly)
                            {
                                continue;
                            }

                            string cmdName = command.Name;
                            outputFile.WriteLine("\t{0} = (PFN_{0})vkGetInstanceProcAddr(instance, \"{0}\");", cmdName);
                        }
                    }
                    outputFile.WriteLine("#endif // defined({0})", version.Version);
                }
            }

            outputFile.WriteLine("}");
        }

        private void EmitLoadInstanceFunctionsOnlyImpl(StreamWriter outputFile)
        {
            string topMatterStr = """
                void Kodiak::VK::LoadInstanceFunctionsOnly(VkInstance instance)
                {
                """;
            outputFile.WriteLine(topMatterStr);

            foreach (var version in m_parser.Versions)
            {
                if (version.InstanceCommands.Count > 0)
                {
                    outputFile.WriteLine("#if defined({0})", version.Version);

                    if (version.InstanceCommands.Count > 0)
                    {
                        outputFile.WriteLine("\t// Instance commands");
                        foreach (var command in version.InstanceCommands)
                        {
                            if (command.DeclarationOnly)
                            {
                                continue;
                            }

                            string cmdName = command.Name;
                            outputFile.WriteLine("\t{0} = (PFN_{0})vkGetInstanceProcAddr(instance, \"{0}\");", cmdName);
                        }
                    }

                    outputFile.WriteLine("#endif // defined({0})", version.Version);
                }
            }

            outputFile.WriteLine("}");
        }

        private void EmitLoadDeviceFunctionsImpl(StreamWriter outputFile)
        {
            string topMatterStr = """
                void Kodiak::VK::LoadDeviceFunctions(VkDevice device)
                {
                """;
            outputFile.WriteLine(topMatterStr);

            foreach (var version in m_parser.Versions)
            {
                if (version.DeviceCommands.Count > 0)
                {
                    outputFile.WriteLine("#if defined({0})", version.Version);

                    if (version.DeviceCommands.Count > 0)
                    {
                        outputFile.WriteLine("\t// Device commands");
                        foreach (var command in version.DeviceCommands)
                        {
                            if (command.DeclarationOnly)
                            {
                                continue;
                            }

                            string cmdName = command.Name;
                            outputFile.WriteLine("\t{0} = (PFN_{0})vkGetDeviceProcAddr(device, \"{0}\");", cmdName);
                        }
                    }
                    outputFile.WriteLine("#endif // defined({0})", version.Version);
                }
            }

            outputFile.WriteLine("}");
        }

        private void EmitSource(string outputDir)
        {
            StreamWriter outputFile = new StreamWriter(Path.Combine(outputDir, "LoaderVk.cpp"), true);

            string topMatterStr = """
                //
                // This code is licensed under the MIT License (MIT).
                // THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
                // ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
                // IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
                // PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
                //
                // Author:  David Elder
                //

                #include "Stdafx.h"

                #include "LoaderVk.h"
                """;

            outputFile.WriteLine(topMatterStr);
            EmitTwoNewLines(outputFile);
            outputFile.Flush();

            EmitInitializeLoaderImpl(outputFile);
            EmitTwoNewLines(outputFile);
            outputFile.Flush();

            EmitLoadInstanceFunctionsImpl(outputFile);
            EmitTwoNewLines(outputFile);
            outputFile.Flush();

            EmitLoadInstanceFunctionsOnlyImpl(outputFile);
            EmitTwoNewLines(outputFile);
            outputFile.Flush();

            EmitLoadDeviceFunctionsImpl(outputFile);
            EmitTwoNewLines(outputFile);
            outputFile.Flush();

            EmitFunctionPointers("", outputFile);
            outputFile.Flush();

            outputFile.Close();
        }

        public void Emit(string outputDir)
        { 
            EmitHeader(outputDir);
            EmitSource(outputDir);
        }

        public VulkanGenLoader(VulkanParser parser)
        {
            m_parser = parser;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Linq;

namespace VulkanParser
{
    internal class VulkanParser
    {
        private List<VulkanVersion> m_versions = new List<VulkanVersion>();
        private XElement m_rootElem = null;
        private Dictionary<string, string> m_typeMap = new Dictionary<string, string>();
        private Dictionary<string, XElement> m_commandMap = new Dictionary<string, XElement>();
        private int m_headerVersion = 0;
        private List<VulkanExtension> m_extensions = new List<VulkanExtension>();
        private HashSet<string> m_knownVersions = new HashSet<string>();

        public List<VulkanVersion> Versions
        { 
            get { return m_versions; } 
        }  

        private void ParseVersions()
        {
            // ==========================================================================
            //
            //  Gathers all core commands per Vulkan version (1.0, 1.1, etc)
            //
            // ==========================================================================

            IEnumerable<XElement> features =
                from el in m_rootElem.Descendants("feature")
                where el.Attribute("api").Value.Split(',').Contains("vulkan")
                select el;

            foreach (XElement feature in features)
            {
                string versionName = (string?)feature.Attribute("name") ?? "";

                m_knownVersions.Add(versionName);

                VulkanVersion vulkanVersion = new VulkanVersion();

                vulkanVersion.Parse(feature);

                m_versions.Add(vulkanVersion);
            }
        }

        private void ParseTypes()
        {
            IEnumerable<XElement> types =
                from el in m_rootElem.Elements("types")
                from cl in el.Elements("type")
                select cl;

            foreach (var type in types)
            {
                var nameElem = type.Element("name");
                if (nameElem != null)
                {
                    string name = nameElem.Value;
                    string parent = "";
                    var parentAttr = type.Attribute("parent");
                    if (parentAttr != null)
                    {
                        parent = (string)parentAttr;
                    }
                    m_typeMap[name] = parent;
                }
            }
        }

        private void ParseCommands()
        {
            IEnumerable<XElement> commands =
                from el in m_rootElem.Elements("commands")
                from cl in el.Elements("command")
                select cl;

            foreach (var commandElem in commands)
            {
                var alias = commandElem.Attribute("alias");
                if (alias == null)
                {
                    string name = (string?)commandElem.Element("proto").Element("name") ?? "";
                    m_commandMap[name] = commandElem;
                }
            }

            foreach (var commandElem in commands)
            {
                var alias = commandElem.Attribute("alias");
                if (alias != null)
                {
                    string name = (string?)commandElem.Attribute("name") ?? "";
                    m_commandMap[name] = m_commandMap[commandElem.Attribute("alias").Value];
                }
            }
        }

        private void ParseHeaderVersion()
        {
            IEnumerable<XElement> headerVersions =
                from el in m_rootElem.Elements("types")
                from cl in el.Elements("type")
                where (string)cl.Attribute("api") == "vulkan" && (string)cl.Element("name") == "VK_HEADER_VERSION"
                select cl;

            m_headerVersion = Int32.Parse(headerVersions.First().Value.Split(' ').Last());
        }

        private void ParseExtensions()
        {
            IEnumerable<XElement> extensions =
                from el in m_rootElem.Descendants("extension")
                where el.Attribute("supported").Value.Split(',').Contains("vulkan")
                select el;

            foreach (XElement extension in extensions)
            {
                VulkanExtension vulkanExtension = new VulkanExtension(m_knownVersions);

                vulkanExtension.Parse(extension);

                m_extensions.Add(vulkanExtension);
            }
        }

        private void AssignCommandsToParents()
        {
            foreach (var version in m_versions)
            {
                foreach (VulkanCommand command in version.Commands)
                {
                    // Special case handling of the GetProcAddr functions
                    if (command.Name == "vkGetInstanceProcAddr")
                    {
                        command.Type = "root";
                        command.DeclarationOnly = true;
                        version.RootCommands.Add(command);
                        continue;
                    }

                    if (command.Name == "vkGetDeviceProcAddr")
                    {
                        command.Type = "instance";
                        version.InstanceCommands.Add(command);
                        continue;
                    }

                    // Handle everything else
                    string cmdParent = FindCommandParent(command.Name);
                    if (cmdParent == "VkInstance")
                    {
                        command.Type = "instance";
                        version.InstanceCommands.Add(command);
                    }
                    else if (cmdParent == "VkDevice")
                    {
                        command.Type = "device";
                        version.DeviceCommands.Add(command);
                    }
                    else
                    {
                        command.Type = "root";
                        version.RootCommands.Add(command);
                    }
                }
            }
        }

        private bool IsDescendantType(string name, string baseName)
        {
            if (baseName == "")
            {
                return false;
            }

            if (name == baseName)
            {
                return true;
            }

            if (!m_typeMap.ContainsKey(name))
            {
                return false;
            }

            string parentName = m_typeMap[name];
            if (parentName == baseName)
            {
                return true;
            }
            else if (parentName == "")
            {
                return false;
            }

            return IsDescendantType(parentName, baseName);
        }

        private string FindCommandParent(string cmdName)
        {
            XElement cmdElem = m_commandMap[cmdName];
            XElement paramElem = cmdElem.Element("param");
            if (paramElem != null)
            {
                string paramType = (string?)paramElem.Element("type") ?? "";
                if (IsDescendantType(paramType, "VkDevice"))
                {
                    return "VkDevice";
                }
                else if (IsDescendantType(paramType, "VkInstance"))
                {
                    return "VkInstance";
                }
            }
            return "";
        }

        public void Parse()
        {
            string urlString = "https://raw.githubusercontent.com/KhronosGroup/Vulkan-Docs/main/xml/vk.xml";

            XmlTextReader reader = new XmlTextReader(urlString);

            m_rootElem = XElement.Load(reader);

            ParseVersions();
            ParseTypes();
            ParseCommands();
            ParseExtensions();

            AssignCommandsToParents();

            ParseHeaderVersion();
        }

        public void Print()
        {
            foreach (var version in m_versions)
            {
                version.Print();
            }

            Console.WriteLine("Header version: {0}", m_headerVersion);

            foreach (var extension in m_extensions)
            {
                extension.Print();
            }
        }
    }
}

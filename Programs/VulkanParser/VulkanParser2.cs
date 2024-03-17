using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Linq;

namespace VulkanParser
{
    internal class VulkanParser2
    {
        private IDictionary<string, List<string>> m_commandGroups = new Dictionary<string, List<string>>();
        private ISet<string> m_instanceCommands = new HashSet<string>();
        private IDictionary<string, List<string>> m_commandsToGroups = new Dictionary<string, List<string>>();
        private IDictionary<string, XElement> m_commands = new Dictionary<string, XElement>();
        private IDictionary<string, string> m_types = new Dictionary<string, string>();
        private XElement? m_rootElem = null;
        private List<string> m_blockNames = new List<string>() {
            "INIT_LOADER",
            "LOAD_INSTANCE",
            "LOAD_DEVICE",
            "HEADER_FUNCTION_PTRS",
            "SOURCE_FUNCTION_PTRS"
        };
        private IDictionary<string, List<string>> m_blocks = new Dictionary<string, List<string>>();

        private static string Defined(string val)
        {
            return "defined(" + val + ")";
        }

        private static string Defined(Match match)
        {
            return "defined(" + match.Value + ")";
        }

        private static string Depends(string depends)
        {
            return Regex.Replace(depends, "[a-zA-Z0-9_]+", Defined).Replace(",", " || ").Replace("+", " && ");
        }

        public VulkanParser2()
        {
            foreach (var name in m_blockNames)
            {
                m_blocks[name] = new List<string>();
            }
        }

        private void ParseFeatures()
        {
            // Parse features (aka Vulkan versions)
            IEnumerable<XElement> features =
                from el in m_rootElem.Descendants("feature")
                where el.Attribute("api").Value.Split(',').Contains("vulkan")
                select el;

            foreach (XElement feature in features)
            {
                string key = Defined((string?)feature.Attribute("name") ?? "");

                IEnumerable<XElement> commands =
                    from el in feature.Descendants("require")
                    from cl in el.Elements("command")
                    select cl;

                foreach (XElement command in commands)
                {
                    if (!m_commandGroups.ContainsKey(key))
                    {
                        m_commandGroups.Add(key, new List<string>());
                    }
                    m_commandGroups[key].Add((string?)command.Attribute("name") ?? "");
                }
            }
        }

        private void ParseExtensions()
        {
            // Parse extensions
            IEnumerable<XElement> extensions =
                from el in m_rootElem.Descendants("extension")
                where el.Attribute("supported").Value.Split(',').Contains("vulkan")
                orderby el.Attribute("name").Value
                select el;

            foreach (var extension in extensions)
            {
                string name = (string?)extension.Attribute("name") ?? "";
                string type = (string?)extension.Attribute("type") ?? "";

                Console.WriteLine("{0}", name);

                IEnumerable<XElement> requires =
                    from cl in extension.Elements("require")
                    select cl;

                foreach (XElement require in requires)
                {
                    string key = Defined(name);

                    string feature = (string?)require.Attribute("feature") ?? "";
                    if (feature.Length > 0)
                    {
                        foreach (var f in feature.Split(","))
                        {
                            key += " && " + Defined(f);
                        }
                    }

                    string ext = (string?)require.Attribute("extension") ?? "";
                    if (ext.Length > 0)
                    {
                        foreach (var f in ext.Split(","))
                        {
                            key += " && " + Defined(f);
                        }
                    }

                    string dep = (string?)require.Attribute("depends") ?? "";
                    if (dep.Length > 0)
                    {
                        dep = Depends(dep);
                        key += " && " + (dep.Contains("||") ? ("(" + dep + ")") : dep);
                    }

                    IEnumerable<XElement> commands =
                        from el in require.Descendants("command")
                        select el;

                    foreach (XElement command in commands)
                    {
                        if (!m_commandGroups.ContainsKey(key))
                        {
                            m_commandGroups.Add(key, new List<string>());
                        }
                        m_commandGroups[key].Add((string?)command.Attribute("name") ?? "");

                        if (type == "instance")
                        {
                            m_instanceCommands.Add((string?)command.Attribute("name") ?? "");
                        }
                    }
                }
            }
        }

        private void ProcessCommandKeys()
        {
            foreach (var kvp in m_commandGroups)
            {
                foreach (var name in kvp.Value)
                {
                    if (!m_commandsToGroups.ContainsKey(name))
                    {
                        m_commandsToGroups.Add(name, new List<string>());
                    }
                    m_commandsToGroups[name].Add(kvp.Key);
                }
            }

            foreach (var kvp in m_commandGroups)
            {
                m_commandGroups[kvp.Key] = (from name in kvp.Value where m_commandsToGroups[name].Count == 1 select name).ToList();
            }

            foreach (var kvp in m_commandsToGroups)
            {
                if (kvp.Value.Count == 1)
                    continue;
                string key = kvp.Value[0];
                for (int i = 1; i < kvp.Value.Count; ++i)
                {
                    key += " || (" + kvp.Value[i] + ")";
                }

                if (!m_commandGroups.ContainsKey(key))
                {
                    m_commandGroups.Add(key, new List<string>());
                }
                m_commandGroups[key].Add(kvp.Key);
            }
        }

        private void ProcessCommandAliases()
        {
            IEnumerable<XElement> allCommands =
               from el in m_rootElem.Elements("commands")
               from cl in el.Elements("command")
               select cl;

            foreach (var commandElem in allCommands)
            {
                var alias = commandElem.Attribute("alias");
                if (alias == null)
                {
                    string name = (string?)commandElem.Element("proto").Element("name") ?? "";
                    m_commands[name] = commandElem;
                }
            }

            foreach (var commandElem in allCommands)
            {
                var alias = commandElem.Attribute("alias");
                if (alias != null)
                {
                    string name = (string?)commandElem.Attribute("name") ?? "";
                    m_commands[name] = m_commands[alias.Value];
                }
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
                    m_types[name] = parent;
                }
            }
        }

        private void PopulateBlocks()
        {
            foreach(var kvp in m_commandGroups)
            {
                var group = kvp.Key;

                string ifdef = "#if " + group;

                foreach(var name in m_blockNames)
                {
                    m_blocks[name].Add(ifdef);
                }

                foreach(var name in kvp.Value)
                {             
                    string type = FindCommandParent(name);

                    if (IsDescendantType(type, "VkDevice") && !m_instanceCommands.Contains(name))
                    {
                        m_blocks["LOAD_DEVICE"].Add(string.Format("\t{0} = (PFN_{0})load(context, \"{0}\");", name));
                    }
                    else if (IsDescendantType(type, "VkInstance"))
                    {
                        m_blocks["LOAD_INSTANCE"].Add(string.Format("\t{0} = (PFN_{0})load(context, \"{0}\");", name));
                    }
                    else if(type != "")
                    {
                        m_blocks["INIT_LOADER"].Add(string.Format("\t{0} = (PFN_{0})load(context, \"{0}\");", name));
                    }

                    m_blocks["HEADER_FUNCTION_PTRS"].Add(string.Format("extern PFN_{0} {0};", name));
                    m_blocks["SOURCE_FUNCTION_PTRS"].Add(string.Format("PFN_{0} {0};", name));
                }

                foreach(var name in m_blockNames)
                {
                    if (m_blocks[name].Last() == ifdef)
                    {
                        m_blocks[name].RemoveAt(m_blocks[name].Count - 1);
                    }
                    else
                    {
                        m_blocks[name].Add(string.Format("#endif // {0}", group));
                    }
                }
            }
        }

        private void PatchFile(string outputDir, string fileName)
        {
            List<string> result = new List<string>();
            string? block = null;

            string fullPath = outputDir + "\\" + fileName;

            using(StreamReader reader = new StreamReader(fullPath))
            {
                string? line;
                while((line = reader.ReadLine()) is not null)
                {
                    if (block is not null)
                    {
                        if(line == block)
                        {
                            result.Add(line);
                            block = null;
                        }
                    }
                    else
                    {
                        result.Add(line);

                        if (line.TrimStart().StartsWith("// KODIAK_GEN_"))
                        {
                            block = line;
                            result.AddRange(m_blocks[line.TrimStart().Substring(14)]);
                        }
                    }
                }
            }

            using (StreamWriter writer = new StreamWriter(fullPath))
            {
                foreach(var line in result)
                {
                    writer.WriteLine(line);
                }
            }
        }

        public void EmitFiles()
        {
            string workingDir = Directory.GetCurrentDirectory();
            Console.WriteLine("Working directory: {0}", workingDir);

            string outputDir = workingDir + "\\Generated";

            if (!Directory.Exists(outputDir))
            {
                Directory.CreateDirectory(outputDir);
            }
            
            PatchFile(outputDir, "LoaderVK.h");
            PatchFile(outputDir, "LoaderVK.cpp");
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

            if (!m_types.ContainsKey(name))
            {
                return false;
            }

            string parentName = m_types[name];
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
            if (cmdName == "vkGetInstanceProcAddr")
            {
                return "";
            }
            else if (cmdName == "vkGetDeviceProcAddr")
            {
                return "VkInstance";
            }

            XElement cmdElem = m_commands[cmdName];
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
            return "Root";
        }

        public void Parse()
        {
            string urlString = "https://raw.githubusercontent.com/KhronosGroup/Vulkan-Docs/main/xml/vk.xml";

            XmlTextReader reader = new XmlTextReader(urlString);

            m_rootElem = XElement.Load(reader);

            ParseFeatures();

            ParseExtensions();

            ProcessCommandKeys();

            ProcessCommandAliases();

            ParseTypes();

            PopulateBlocks();

            EmitFiles();
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace VulkanParser
{
    internal enum EVersion
    {
        VK_VERSION_1_0,
        VK_VERSION_1_1,
        VK_VERSION_1_2,
        VK_VERSION_1_3
    }

    internal class VulkanVersion
    {
        private List<VulkanCommand> m_commands = new List<VulkanCommand>();
        private List<VulkanCommand> m_rootCommands = new List<VulkanCommand>();
        private List<VulkanCommand> m_instanceCommands = new List<VulkanCommand>();
        private List<VulkanCommand> m_deviceCommands = new List<VulkanCommand>();

        public List<VulkanCommand> Commands
        {
            get { return m_commands; }
        }

        public List<VulkanCommand> RootCommands
        {
            get { return m_rootCommands; }
        }

        public List<VulkanCommand> InstanceCommands
        {
            get { return m_instanceCommands; }
        }

        public List<VulkanCommand> DeviceCommands
        {
            get { return m_deviceCommands; }
        }

        public EVersion Version { get; protected set; } = EVersion.VK_VERSION_1_0;

        public bool HasAnyCommands
        {
            get
            {
                return m_rootCommands.Count > 0 || m_instanceCommands.Count > 0 || m_deviceCommands.Count > 0;
            }
        }

        public void Parse(XElement element)
        {
            // Read attributes
            string attrName = (string?)element.Attribute("name") ?? "";

            // Set attributes
            Version = attrName != "" ? (EVersion)Enum.Parse(typeof(EVersion), attrName) : EVersion.VK_VERSION_1_0;

            IEnumerable<XElement> commands =
                    from el in element.Descendants("require")
                    from cl in el.Elements("command")
                    select cl;

            foreach (XElement command in commands)
            {
                VulkanCommand vkCommand = new VulkanCommand();
                
                vkCommand.Name = (string?)command.Attribute("name") ?? "";
                vkCommand.Version = Version;
                vkCommand.Depends = Version.ToString();

                m_commands.Add(vkCommand);
            }
        }

        public void Print()
        {
            Console.WriteLine(Version.ToString());

            Console.WriteLine("  Root commands:");
            foreach (var command in RootCommands)
            {
                Console.WriteLine("    {0}", command.ToString(true));
            }

            Console.WriteLine("  Instance commands:");
            foreach (var command in InstanceCommands)
            {
                Console.WriteLine("    {0}", command.ToString(true));
            }

            Console.WriteLine("  Device commands:");
            foreach (var command in DeviceCommands)
            {
                Console.WriteLine("    {0}", command.ToString(true));
            }

            Console.WriteLine();
        }
    }
}

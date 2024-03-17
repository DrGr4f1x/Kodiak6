using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace VulkanParser
{
    internal class VulkanExtension
    {
        private List<VulkanCommand> m_commands = new List<VulkanCommand>();
        private HashSet<string> m_knownVersions;

        public string Name { get; protected set; } = "";

        public string Author { get; protected set; } = "";

        public string Type { get; protected set; } = "";

        public string Number { get; protected set; } = "";

        public string PromotedToVersion { get; protected set; } = "";

        public string PromotedToExtension { get; protected set; } = "";

        public string PromotedTo
        {
            get
            {
                return (PromotedToVersion != "") ? PromotedToVersion : PromotedToExtension;
            }

            protected set
            {
                if (m_knownVersions.Contains(value))
                {
                    PromotedToVersion = value;
                }
                else
                {
                    PromotedToExtension = value;
                }
            }
        }

        public string DeprecatedByVersion { get; protected set; } = "";

        public string DeprecatedByExtension { get; protected set; } = "";

        public string DeprecatedBy
        {
            get
            {
                return (DeprecatedByVersion != "") ? DeprecatedByVersion : DeprecatedByExtension;
            }

            protected set
            {
                if (m_knownVersions.Contains(value))
                {
                    DeprecatedByVersion = value;
                }
                else
                {
                    DeprecatedByExtension = value;
                }
            }
        }

        public string ObsoletedByVersion { get; protected set; } = "";

        public string ObsoletedByExtension { get; protected set; } = "";

        public string ObsoletedBy
        {
            get
            {
                return (ObsoletedByVersion != "") ? ObsoletedByVersion : ObsoletedByExtension;
            }

            protected set
            {
                if (m_knownVersions.Contains(value))
                {
                    ObsoletedByVersion = value;
                }
                else
                {
                    ObsoletedByExtension = value;
                }
            }
        }

        public string Depends { get; protected set; } = "";

        public List<VulkanCommand> Commands
        {
            get { return m_commands; }
        }

        public bool HasAnyCommands
        {
            get { return m_commands.Count > 0; }
        }

        public VulkanExtension(HashSet<string> knownVersions)
        {
            m_knownVersions = knownVersions;
        }

        public void Parse(XElement element)
        {
            // Assign attributes
            Name = (string?)element.Attribute("name") ?? "";
            Author = (string?)element.Attribute("type") ?? "";
            Type = (string?)element.Attribute("type") ?? "";
            Number = (string?)element.Attribute("number") ?? "";
            Depends = (string?)element.Attribute("depends") ?? "";
            PromotedTo = (string?)element.Attribute("promotedto") ?? "";
            DeprecatedBy = (string?)element.Attribute("deprecatedby") ?? "";
            ObsoletedBy = (string?)element.Attribute("obsoletedby") ?? "";

            Depends = ParseDepends(Depends);

            IEnumerable<XElement> requires =
                from cl in element.Elements("require")
                select cl;

            foreach (XElement require in requires)
            {
                string dependsStr = "";
                
                if (require.Attribute("depends") != null)
                {
                    dependsStr = (string?)require.Attribute("depends") ?? "";
                }

                IEnumerable<XElement> commands =
                    from command in require.Elements("command")
                    select command;

                foreach (XElement command in commands)
                {
                    VulkanCommand vkCommand = new VulkanCommand();

                    vkCommand.Name = (string?)command.Attribute("name") ?? "";
                    vkCommand.Type = Type;
                    vkCommand.Depends = ParseDepends(dependsStr);

                    Commands.Add(vkCommand);
                }
            }
        }

        public void Print()
        {
            Console.WriteLine(Name);
            Console.WriteLine("  Author: {0}", Author);
            Console.WriteLine("  Type: {0}", Type);
            Console.WriteLine("  Number: {0}", Number);

            if (Depends != "")
            {
                Console.WriteLine("  Depends: {0}", Depends);
            }

            if (PromotedTo != "")
            {
                Console.WriteLine("  PromotedTo: {0}", PromotedTo);
            }

            if (DeprecatedBy != "")
            {
                Console.WriteLine("  DeprecatedBy: {0}", DeprecatedBy);
            }

            if (ObsoletedBy != "")
            {
                Console.WriteLine("  ObsoletedBy: {0}", ObsoletedBy);
            }

            if (m_commands.Count > 0)
            {
                Console.WriteLine("  Commands");
                foreach (var command in m_commands)
                {
                    Console.WriteLine("    {0}", command.ToString(false));
                }
            }
            Console.WriteLine();
        }

        private static string Define(Match match)
        {
            return "defined(" + match.Value + ")";
        }

        private static string ParseDepends(string depends)
        {
            return Regex.Replace(depends, "[a-zA-Z0-9_]+", Define).Replace(",", " || ").Replace("+", " && ");
        }
    }
}

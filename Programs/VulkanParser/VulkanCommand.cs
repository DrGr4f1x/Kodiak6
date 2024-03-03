using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VulkanParser
{
    internal class VulkanCommand
    {
        public string Name { get; set; } = "";
        public string Type { get; set; } = "";
        public EVersion Version { get; set; } = EVersion.VK_VERSION_1_0;
        public string Depends { get; set; } = "";

        public string ToString(bool bSimple)
        {
            if (bSimple)
            {
                return Name;
            }
            else
            {
                return String.Format("{0} [Type: {1}, Version: {2}, Depends: {3}", Name, Type, Version, Depends);
            }
        }
    }
}

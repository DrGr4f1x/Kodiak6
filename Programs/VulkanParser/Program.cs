using System;
using System.Collections.Generic;
using System.Diagnostics.Tracing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Linq;

namespace VulkanParser
{
    internal class Program
    {
        private List<VulkanVersion> m_versions = new List<VulkanVersion>();

        static void Main(string[] args)
        {
            //// Parse the registry
            //VulkanParser parser = new VulkanParser();
            //parser.Parse();

            //parser.Print();

            //// Emit headers and source files
            //VulkanGenerator generator = new VulkanGenerator(parser);
            //generator.EmitFiles();

            VulkanParser2 parser2 = new VulkanParser2();
            parser2.Parse();
        }
    }
}

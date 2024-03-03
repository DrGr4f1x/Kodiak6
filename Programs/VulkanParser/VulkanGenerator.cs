using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace VulkanParser
{
    internal class VulkanGenerator
    {
        private VulkanParser m_parser = null;

        public void EmitFiles()
        {
            string workingDir = Directory.GetCurrentDirectory();
            Console.WriteLine("Working directory: {0}", workingDir);

            string outputDir = workingDir + "\\Generated";

            if (Directory.Exists(outputDir))
            {
                Directory.Delete(outputDir, true);
            }
            Directory.CreateDirectory(outputDir);

            // Emit the loader files
            VulkanGenLoader loaderGen = new VulkanGenLoader(m_parser);
            loaderGen.Emit(outputDir);
        }

        public VulkanGenerator(VulkanParser parser)
        {
            m_parser = parser;
        }
    }
}

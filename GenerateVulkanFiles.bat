@ECHO OFF
REM This batch file reads the Vulkan registry and generates several c++ files.
pushd .\Programs\VulkanParser\bin\Release\net8.0
VulkanParser.exe
popd
xcopy .\Programs\VulkanParser\bin\Release\net8.0\Generated\*.* Engine\Graphics\VK\Generated\. /Y
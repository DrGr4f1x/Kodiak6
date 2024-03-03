@ECHO OFF
REM This batch file reads the Vulkan registry and generates several c++ files.
Programs\VulkanParser\Bin\Release\VulkanParser.exe
xcopy Programs\VulkanParser\Bin\Release\Generated\*.* Engine\Graphics\VK\. /Y
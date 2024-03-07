@ECHO OFF
REM This batch file reads the Vulkan registry and generates several c++ files.
Programs\VulkanParser\bin\Release\net8.0\VulkanParser.exe
xcopy Programs\VulkanParser\bin\Release\net8.0\Generated\*.* Engine\Graphics\VK\. /Y
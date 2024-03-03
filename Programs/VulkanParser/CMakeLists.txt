#
# This code is licensed under the MIT License (MIT).
# THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
# IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
# PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
#
# Author:  David Elder
#

cmake_minimum_required(VERSION 3.24)

project(VulkanParser VERSION 1.0.0 LANGUAGES CSharp)

include(CSharpUtilities)

add_executable(VulkanParser
	Program.cs
	VulkanCommand.cs
	VulkanExtension.cs
	VulkanGenerator.cs
	VulkanGenLoader.cs
	VulkanParser.cs
	VulkanVersion.cs)

set(CMAKE_CSharp_FLAGS "/langversion:11")
set_property(TARGET VulkanParser PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
set_property(TARGET VulkanParser PROPERTY WIN32_EXECUTABLE TRUE)

set_property(TARGET VulkanParser PROPERTY VS_DOTNET_REFERENCES
	"Microsoft.CSharp"
	"System"
	"System.Diagnostics.Tracing"
	"System.IO"
	"System.Linq"
	"System.Reflection"
	"System.Threading.Tasks"
	"System.Xml"
	"System.Xml.Linq")

set_target_properties(VulkanParser PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin")
set_target_properties(VulkanParser PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set_target_properties(VulkanParser PROPERTIES FOLDER "Programs")
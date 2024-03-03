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

set(NAME Main)

project(${NAME} VERSION 6.0.0 LANGUAGES CXX CSharp)

include(SetupConfigurations.cmake)

include_directories(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Use FindVulkan module added with CMAKE 3.7
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
	message(STATUS "Using module to find Vulkan")
	find_package(Vulkan)
endif()

add_subdirectory(External)
add_subdirectory(Engine)
add_subdirectory(Apps)
add_subdirectory(Programs)
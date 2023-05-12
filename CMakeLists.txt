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

include(SetupConfigurations.cmake)

set(NAME Main)

project(${NAME} VERSION 6.0.0)

include_directories(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(External)
add_subdirectory(Engine)
add_subdirectory(Apps)
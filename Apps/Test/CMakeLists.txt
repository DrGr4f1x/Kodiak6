#
# This code is licensed under the MIT License (MIT).
# THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
# IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
# PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
#
# Author:  David Elder
#

set(APP_NAME Test)

# Macro to add a source file to the root group
macro(ADDFILEROOT file_list source_file)
	list(APPEND ${file_list} ${source_file})
	source_group("" FILES ${source_file})
endmacro()

# Initialize empty file list
set(FILE_LIST "")

# Root files
ADDFILEROOT(FILE_LIST Main.cpp)
ADDFILEROOT(FILE_LIST Stdafx.h)
ADDFILEROOT(FILE_LIST Stdafx.cpp)
ADDFILEROOT(FILE_LIST TestApp.h)
ADDFILEROOT(FILE_LIST TestApp.cpp)
ADDFILEROOT(FILE_LIST packages.config)

# Target executable
add_executable(${APP_NAME} WIN32 ${FILE_LIST})
add_compile_definitions($<$<CONFIG:Release>:RELEASE> $<$<CONFIG:Release>:_RELEASE> $<$<CONFIG:Release>:NDEBUG>)
add_compile_definitions($<$<CONFIG:Profile>:PROFILE> $<$<CONFIG:Profile>:_PROFILE> $<$<CONFIG:Profile>:BDEBUG>)
add_compile_definitions($<$<CONFIG:Debug>:DEBUG> $<$<CONFIG:Debug>:_DEBUG>)

set_property(TARGET ${APP_NAME} PROPERTY VS_PACKAGE_REFERENCES "Microsoft.Direct3D.D3D12_1.611.2")

if (MSVC)
	set_target_properties(${APP_NAME} PROPERTIES COMPILE_FLAGS "/YuStdafx.h")
	set_source_files_properties(Stdafx.cpp PROPERTIES COMPILE_FLAGS "/YcStdafx.h")
endif(MSVC)

target_link_libraries(${APP_NAME} Engine ${WINLIBS} ${Vulkan_LIBRARIES})

set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin")
set_target_properties(${APP_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set_target_properties(${APP_NAME} PROPERTIES FOLDER "Apps")
set_target_properties(${APP_NAME} PROPERTIES 
	LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
	LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE"
	LINK_FLAGS_PROFILE "/SUBSYSTEM:CONSOLE"
)

target_link_directories(${APP_NAME} PUBLIC ${Vulkan_LIBRARY})
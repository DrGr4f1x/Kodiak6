#
# This code is licensed under the MIT License (MIT).
# THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
# IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
# PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
#
# Author:  David Elder
#

# Macro to add a source file to the root group
macro(ADDFILEROOT file_list source_file)
	list(APPEND ${file_list} ${source_file})
	source_group("" FILES ${source_file})
endmacro()

# Macro to add a source file to a source group
macro(ADDFILEGROUP file_list group source_file)
	list(APPEND ${file_list} ${source_file})
	source_group(${group} FILES ${source_file})
endmacro()

# Initialize empty file list
set(FILE_LIST "")

# Root files
ADDFILEROOT(FILE_LIST Application.h)
ADDFILEROOT(FILE_LIST Application.cpp)
ADDFILEROOT(FILE_LIST Stdafx.h)
ADDFILEROOT(FILE_LIST Stdafx.cpp)

# Core files
ADDFILEGROUP(FILE_LIST Core Core/BitmaskEnum.h)
ADDFILEGROUP(FILE_LIST Core Core/CoreEnums.h)
ADDFILEGROUP(FILE_LIST Core Core/Utility.h)
ADDFILEGROUP(FILE_LIST Core Core/Utility.cpp)

add_library(Engine STATIC ${FILE_LIST})

if (MSVC)
	set_target_properties(Engine PROPERTIES COMPILE_FLAGS "/YuStdafx.h")
	set_source_files_properties(Stdafx.cpp PROPERTIES COMPILE_FLAGS "/YcStdafx.h")
endif(MSVC)

set_target_properties(Engine PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIRECTORY}/Lib"
)
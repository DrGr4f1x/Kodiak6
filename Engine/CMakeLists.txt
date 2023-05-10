#
# This code is licensed under the MIT License (MIT).
# THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
# IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
# PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
#
# Author:  David Elder
#

# Top-level
file(GLOB SOURCE *.cpp)
file(GLOB HEADERS *.h)
source_group("" FILES ${SOURCE})
source_group("" FILES ${HEADERS})

# Core
file(GLOB CORE_SOURCE *.cpp)
file(GLOB CORE_HEADERS *.h)
source_group(Core FILES ${CORE_SOURCE})
source_group(Core FILES ${CORE_HEADERS})


add_library(Engine STATIC
	${SOURCE}
	${HEADERS}
	${CORE_SOURCE}
	${CORE_HEADERS}
)

if (MSVC)
	set_target_properties(Engine PROPERTIES COMPILE_FLAGS "/YuStdafx.h")
	set_source_files_properties(Stdafx.cpp PROPERTIES COMPILE_FLAGS "/YcStdafx.h")
endif(MSVC)

set_target_properties(Engine PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIRECTORY}/Lib"
)
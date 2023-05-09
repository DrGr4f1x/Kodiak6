#
# This code is licensed under the MIT License (MIT).
# THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
# ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
# IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
# PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
#
# Author:  David Elder
#

set(EngineInclude
	Core/BitmaskEnum.h
	Application.h
	Stdafx.h
)

set(EngineSrc
	Application.cpp
	Stdafx.cpp
)

add_library(Engine STATIC
	${EngineInclude}
	${EngineSrc}
)

if (MSVC)
	set_target_properties(Engine PROPERTIES COMPILE_FLAGS "/YuStdafx.h")
	set_source_files_properties(Stdafx.cpp PROPERTIES COMPILE_FLAGS "/YcStdafx.h")
endif(MSVC)

set_target_properties(Engine PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIRECTORY}/Lib"
	LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIRECTORY}/Lib"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIRECTORY}/Bin"
)
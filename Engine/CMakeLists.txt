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
ADDFILEROOT(FILE_LIST FileSystem.h)
ADDFILEROOT(FILE_LIST FileSystem.cpp)
ADDFILEROOT(FILE_LIST InputSystem.h)
ADDFILEROOT(FILE_LIST InputSystem.cpp)
ADDFILEROOT(FILE_LIST LogSystem.h)
ADDFILEROOT(FILE_LIST LogSystem.cpp)
ADDFILEROOT(FILE_LIST Stdafx.h)
ADDFILEROOT(FILE_LIST Stdafx.cpp)

# Core files
ADDFILEGROUP(FILE_LIST Core Core/BitmaskEnum.h)
ADDFILEGROUP(FILE_LIST Core Core/Color.h)
ADDFILEGROUP(FILE_LIST Core Core/Color.cpp)
ADDFILEGROUP(FILE_LIST Core Core/CoreEnums.h)
ADDFILEGROUP(FILE_LIST Core Core/DWParam.h)
ADDFILEGROUP(FILE_LIST Core Core/Hash.h)
ADDFILEGROUP(FILE_LIST Core Core/Hash.cpp)
ADDFILEGROUP(FILE_LIST Core Core/NonCopyable.h)
ADDFILEGROUP(FILE_LIST Core Core/NonMovable.h)
ADDFILEGROUP(FILE_LIST Core Core/Utility.h)
ADDFILEGROUP(FILE_LIST Core Core/Utility.cpp)
ADDFILEGROUP(FILE_LIST Core Core/VectorMath.h)

# Core\Math files
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/CommonMath.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/BoundingBox.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/BoundingBox.cpp)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/BoundingPlane.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/BoundingSphere.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Frustum.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Frustum.cpp)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Functions.inl)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Matrix3.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Matrix4.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Quaternion.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Random.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Random.cpp)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Scalar.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Transform.h)
ADDFILEGROUP(FILE_LIST Core/Math Core/Math/Vector.h)

add_library(Engine STATIC ${FILE_LIST})

if (MSVC)
	set_target_properties(Engine PROPERTIES COMPILE_FLAGS "/YuStdafx.h")
	set_source_files_properties(Stdafx.cpp PROPERTIES COMPILE_FLAGS "/YcStdafx.h")
endif(MSVC)

set_target_properties(Engine PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIRECTORY}/Lib"
)

set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Release>:RELEASE>)
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Profile>:PROFILE>)
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS $<$<CONFIG:Debug>:DEBUG>)
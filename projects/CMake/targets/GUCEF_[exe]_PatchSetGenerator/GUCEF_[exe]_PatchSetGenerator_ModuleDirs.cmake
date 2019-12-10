#-------------------------------------------------------------------
# This file was automatically generated by ProjectGenerator
# which is tooling part the build system designed for GUCEF
#     (Galaxy Unlimited Framework)
# For the latest info, see http://www.VanvelzenSoftware.com/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
#


if (WIN32)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefPATCHER ${CMAKE_BINARY_DIR}/gucefPATCHER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../tools/PatchSetGenerator ${CMAKE_BINARY_DIR}/PatchSetGenerator )
elseif (WIN64)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefPATCHER ${CMAKE_BINARY_DIR}/gucefPATCHER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../tools/PatchSetGenerator ${CMAKE_BINARY_DIR}/PatchSetGenerator )
else()
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../tools/PatchSetGenerator ${CMAKE_BINARY_DIR}/PatchSetGenerator )
endif()

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
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/libparsifal ${CMAKE_BINARY_DIR}/libparsifal )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../plugins/CORE/dstorepluginPARSIFALXML ${CMAKE_BINARY_DIR}/dstorepluginPARSIFALXML )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../tools/ProjectGen ${CMAKE_BINARY_DIR}/ProjectGen )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../tools/ProjectGenerator ${CMAKE_BINARY_DIR}/ProjectGenerator )

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


if (EMSCRIPTEN)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (GLX)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (GTK)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (IOS)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (NACL)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (POSIX)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (SDL)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (SYMBIAN)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
elseif (UNIX)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
else()
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCOM ${CMAKE_BINARY_DIR}/gucefCOM )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCOMCORE ${CMAKE_BINARY_DIR}/gucefCOMCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefCORE ${CMAKE_BINARY_DIR}/gucefCORE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefDRN ${CMAKE_BINARY_DIR}/gucefDRN )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefGUI ${CMAKE_BINARY_DIR}/gucefGUI )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefIMAGE ${CMAKE_BINARY_DIR}/gucefIMAGE )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefINPUT ${CMAKE_BINARY_DIR}/gucefINPUT )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefLOADER ${CMAKE_BINARY_DIR}/gucefLOADER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMATH ${CMAKE_BINARY_DIR}/gucefMATH )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMT ${CMAKE_BINARY_DIR}/gucefMT )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefMULTIPLAY ${CMAKE_BINARY_DIR}/gucefMULTIPLAY )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefPATCHER ${CMAKE_BINARY_DIR}/gucefPATCHER )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefPRODMAN ${CMAKE_BINARY_DIR}/gucefPRODMAN )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefSMDRN ${CMAKE_BINARY_DIR}/gucefSMDRN )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../platform/gucefVFS ${CMAKE_BINARY_DIR}/gucefVFS )
endif()

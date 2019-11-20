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


if (LINUX32)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/freetype ${CMAKE_BINARY_DIR}/freetype )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/MyGUIEngine ${CMAKE_BINARY_DIR}/MyGUI.Engine )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Platforms/OpenGL/OpenGLPlatform ${CMAKE_BINARY_DIR}/MyGUI.OpenGLPlatform )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Tools/LayoutEditor ${CMAKE_BINARY_DIR}/MyGUI.LayoutEditor )
elseif (LINUX64)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/freetype ${CMAKE_BINARY_DIR}/freetype )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/MyGUIEngine ${CMAKE_BINARY_DIR}/MyGUI.Engine )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Platforms/OpenGL/OpenGLPlatform ${CMAKE_BINARY_DIR}/MyGUI.OpenGLPlatform )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Tools/LayoutEditor ${CMAKE_BINARY_DIR}/MyGUI.LayoutEditor )
elseif (WIN32)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/freetype ${CMAKE_BINARY_DIR}/freetype )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/MyGUIEngine ${CMAKE_BINARY_DIR}/MyGUI.Engine )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Platforms/OpenGL/OpenGLPlatform ${CMAKE_BINARY_DIR}/MyGUI.OpenGLPlatform )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Tools/LayoutEditor ${CMAKE_BINARY_DIR}/MyGUI.LayoutEditor )
elseif (WIN64)
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/freetype ${CMAKE_BINARY_DIR}/freetype )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/MyGUIEngine ${CMAKE_BINARY_DIR}/MyGUI.Engine )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Platforms/OpenGL/OpenGLPlatform ${CMAKE_BINARY_DIR}/MyGUI.OpenGLPlatform )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Tools/LayoutEditor ${CMAKE_BINARY_DIR}/MyGUI.LayoutEditor )
else()
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/MyGui/Tools/LayoutEditor ${CMAKE_BINARY_DIR}/MyGUI.LayoutEditor )
endif()

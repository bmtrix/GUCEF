--------------------------------------------------------------------
-- This file was automatically generated by ProjectGenerator
-- which is tooling part the build system designed for GUCEF
--     (Galaxy Unlimited Framework)
-- For the latest info, see http://www.VanvelzenSoftware.com/
--
-- The contents of this file are placed in the public domain. Feel
-- free to make use of it in any way you like.
--------------------------------------------------------------------
--

-- Configuration for module: guidriverRocketOpenGL


project( "guidriverRocketOpenGL" )
location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
language( "C++" )

configuration( { "ANDROID" } )
language( "C" )

configuration( { "LINUX" } )
language( "C" )

configuration( { "OSX" } )
language( "C" )

configuration( { "WIN32" } )
language( "C" )

configuration( { "WIN64" } )
language( "C" )

kind( "SharedLib" )
links( { "RocketControls", "RocketCore", "gucefCORE", "gucefGUI", "gucefINPUT", "gucefMT", "guidriverRocket" } )
links( { "RocketControls", "RocketCore", "gucefCORE", "gucefGUI", "gucefINPUT", "gucefMT", "guidriverRocket" } )
defines( { "GUIDRIVERROCKETGL_BUILD_MODULE" } )

configuration( { "ANDROID" } )
  links( { "EGL", "GLESv1_CM" } )

configuration( { "LINUX" } )
  links( { "GL" } )

configuration( { "WIN32" } )
  links( { "OpenGL32.lib" } )

configuration( { "WIN64" } )
  links( { "OpenGL32.lib" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/guidriverRocketOpenGL.h",
  "include/guidriverRocketOpenGL_config.h",
  "include/guidriverRocketOpenGL_CRocketGuiDriver.h",
  "include/guidriverRocketOpenGL_CRocketRenderInterfaceOpenGL.h",
  "include/guidriverRocketOpenGL_macros.h",
  "include/guidriverRocketOpenGL_pluginAPI.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/guidriverRocketOpenGL_CRocketGuiDriver.cpp",
  "src/guidriverRocketOpenGL_CRocketRenderInterfaceOpenGL.cpp",
  "src/guidriverRocketOpenGL_pluginAPI.cpp"
 } )


configuration( {} )
includedirs( { "../../../common/include", "../../../dependencies/freetype/include", "../../../dependencies/freetype/include/freetype", "../../../dependencies/freetype/include/freetype/config", "../../../dependencies/freetype/include/freetype/internal", "../../../dependencies/freetype/include/freetype/internal/services", "../../../dependencies/freetype/src/winfonts", "../../../dependencies/libRocket/Include", "../../../dependencies/libRocket/Include/Rocket", "../../../dependencies/libRocket/Include/Rocket/Controls", "../../../dependencies/libRocket/Include/Rocket/Core", "../../../dependencies/libRocket/Include/Rocket/Core/Python", "../../../dependencies/libRocket/Include/Rocket/Debugger", "../../../dependencies/libRocket/Source/Controls", "../../../dependencies/libRocket/Source/Core", "../../../gucefCORE/include", "../../../gucefGUI/include", "../../../gucefIMAGE/include", "../../../gucefINPUT/include", "../../../gucefMT/include", "../../../gucefVFS/include", "../guidriverRocket/include", "include" } )

configuration( { "ANDROID" } )
includedirs( { "../../../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../../../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../../../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../../../gucefCORE/include/mswin" } )

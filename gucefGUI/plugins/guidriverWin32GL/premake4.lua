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

-- Configuration for module: guidriverWin32GL


configuration( { "WIN32" } )
  project( "guidriverWin32GL" )

configuration( { "WIN64" } )
  project( "guidriverWin32GL" )
location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
language( "C" )

configuration( { "WIN32" } )
language( "C++" )

configuration( { "WIN64" } )
language( "C++" )

configuration( { "WIN32" } )
kind( "SharedLib" )
configuration( { "WIN64" } )
kind( "SharedLib" )

configuration( { "WIN32" } )
  links( { "gucefCORE", "gucefGUI", "gucefMT" } )
  links( { "Opengl32", "gucefCORE", "gucefGUI", "gucefMT" } )
  defines( { "GUIDRIVERWIN32GL_BUILD_MODULE" } )

configuration( { "WIN64" } )
  links( { "gucefCORE", "gucefGUI", "gucefMT" } )
  links( { "Opengl32", "gucefCORE", "gucefGUI", "gucefMT" } )
  defines( { "GUIDRIVERWIN32GL_BUILD_MODULE" } )


configuration( { "WIN32" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include/guidriverWin32GL.h",
      "include/guidriverWin32GL_config.h",
      "include/guidriverWin32GL_CWin32GLWindowContext.h",
      "include/guidriverWin32GL_CWin32GLWindowManagerImp.h",
      "include/guidriverWin32GL_macros.h",
      "include/guidriverWin32GL_pluginAPI.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/guidriverWin32GL_CWin32GLWindowContext.cpp",
      "src/guidriverWin32GL_CWin32GLWindowManagerImp.cpp",
      "src/guidriverWin32GL_pluginAPI.cpp"
    } )



configuration( { "WIN64" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "include/guidriverWin32GL.h",
      "include/guidriverWin32GL_config.h",
      "include/guidriverWin32GL_CWin32GLWindowContext.h",
      "include/guidriverWin32GL_CWin32GLWindowManagerImp.h",
      "include/guidriverWin32GL_macros.h",
      "include/guidriverWin32GL_pluginAPI.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/guidriverWin32GL_CWin32GLWindowContext.cpp",
      "src/guidriverWin32GL_CWin32GLWindowManagerImp.cpp",
      "src/guidriverWin32GL_pluginAPI.cpp"
    } )


configuration( {} )
includedirs( { "../../../common/include", "../../../gucefCORE/include", "../../../gucefGUI/include", "../../../gucefIMAGE/include", "../../../gucefMT/include", "../../../gucefVFS/include" } )

configuration( { "WIN32" } )
includedirs( { "../../../gucefCORE/include/mswin", "include" } )

configuration( { "WIN64" } )
includedirs( { "../../../gucefCORE/include/mswin", "include" } )

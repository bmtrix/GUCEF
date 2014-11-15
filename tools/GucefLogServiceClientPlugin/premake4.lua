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

-- Configuration for module: GucefLogServiceClientPlugin


project( "GucefLogServiceClientPlugin" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C++" )



configuration( {} )
kind( "SharedLib" )

configuration( {} )
links( { "GucefLogServiceLib", "gucefCOM", "gucefCOMCORE", "gucefCORE", "gucefMT" } )
links( { "GucefLogServiceLib", "gucefCOM", "gucefCOMCORE", "gucefCORE", "gucefMT" } )


configuration( {} )
defines( { "GUCEF_LOGSERVICECLIENTPLUGIN_BUILD_MODULE" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/GucefLogServiceClientPlugin.h",
  "include/GucefLogServiceClientPlugin_config.h",
  "include/GucefLogServiceClientPlugin_macros.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/GucefLogServiceClientPlugin.cpp"
 } )


configuration( {} )
includedirs( { "../../common/include", "../../gucefCOM/include", "../../gucefCOMCORE/include", "../../gucefCORE/include", "../../gucefMT/include", "../GucefLogServiceLib/include", "include" } )

configuration( { "ANDROID" } )
includedirs( { "../../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../../gucefCOMCORE/include/mswin", "../../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../../gucefCOMCORE/include/mswin", "../../gucefCORE/include/mswin" } )

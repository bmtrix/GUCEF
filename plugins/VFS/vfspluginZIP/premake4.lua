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

-- Configuration for module: vfspluginZIP


project( "vfspluginZIP" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C++" )



configuration( {} )
kind( "SharedLib" )

configuration( {} )
links( { "gucefCORE", "gucefMT", "gucefVFS", "zziplib" } )
links( { "gucefCORE", "gucefMT", "gucefVFS", "zziplib" } )


configuration( {} )
defines( { "GUCEF_VFSPLUGIN_ZIP_BUILD_MODULE", "ZZIP_HAVE_STDINT_H" } )
  links( { "z" } )
  
configuration( { LINUX } )
links( { "zlib" } )
  links( { "zlib" } )
  
configuration( { WIN32 } )
links( { "zlib" } )
  links( { "zlib" } )
  
configuration( { WIN64 } )
links( { "zlib" } )
  links( { "zlib" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/vfspluginZIP.h",
  "include/vfspluginZIP_config.h",
  "include/vfspluginZIP_CZIPArchive.h",
  "include/vfspluginZIP_CZipIOAccess.h",
  "include/vfspluginZIP_macros.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/vfspluginZIP.cpp",
  "src/vfspluginZIP_CZIPArchive.cpp",
  "src/vfspluginZIP_CZipIOAccess.cpp"
 } )


configuration( {} )
includedirs( { "../../../common/include", "../../../dependencies/zziplib", "../../../dependencies/zziplib/zzip", "../../../gucefCORE/include", "../../../gucefMT/include", "../../../gucefVFS/include", "include" } )

configuration( { "ANDROID" } )
includedirs( { "../../../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../../../dependencies/zlib", "../../../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../../../dependencies/zlib", "../../../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../../../dependencies/zlib", "../../../gucefCORE/include/mswin" } )

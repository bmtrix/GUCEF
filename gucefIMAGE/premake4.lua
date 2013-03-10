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

-- Configuration for module: gucefIMAGE


project( "gucefIMAGE" )
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
links( { "gucefCORE", "gucefMT" } )
links( { "gucefCORE", "gucefMT" } )
defines( { "GUCEFIMAGE_BUILD_MODULE" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/CGUCEFIMAGEModule.h",
  "include/gucefIMAGE.h",
  "include/gucefIMAGEDLLInit.h",
  "include/gucefIMAGE_CGUIImageCodec.h",
  "include/gucefIMAGE_CIImageCodec.h",
  "include/gucefIMAGE_CImage.h",
  "include/gucefIMAGE_CImageCodecPlugin.h",
  "include/gucefIMAGE_CImageCodecPluginManager.h",
  "include/gucefIMAGE_CImageCodecRegistry.h",
  "include/gucefIMAGE_CImageGlobal.h",
  "include/gucefIMAGE_CIMGCodec.h",
  "include/gucefIMAGE_config.h",
  "include/gucefIMAGE_CPixelMap.h",
  "include/gucefIMAGE_CPluginImageCodecItem.h",
  "include/gucefIMAGE_ETypes.h",
  "include/gucefIMAGE_imagedata.h",
  "include/gucefIMAGE_macros.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/CGUCEFIMAGEModule.cpp",
  "src/gucefIMAGE.cpp",
  "src/gucefIMAGE_CCPluginImageCodecItem.cpp",
  "src/gucefIMAGE_CGUIImageCodec.cpp",
  "src/gucefIMAGE_CIImageCodec.cpp",
  "src/gucefIMAGE_CImage.cpp",
  "src/gucefIMAGE_CImageCodecPlugin.cpp",
  "src/gucefIMAGE_CImageCodecPluginManager.cpp",
  "src/gucefIMAGE_CImageCodecRegistry.cpp",
  "src/gucefIMAGE_CImageGlobal.cpp",
  "src/gucefIMAGE_CIMGCodec.cpp",
  "src/gucefIMAGE_CPixelMap.cpp"
 } )


configuration( {} )
includedirs( { "../common/include", "../gucefCORE/include", "../gucefMT/include", "include" } )

configuration( { "ANDROID" } )
includedirs( { "../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../gucefCORE/include/mswin" } )

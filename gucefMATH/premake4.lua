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

-- Configuration for module: gucefMATH


project( "gucefMATH" )
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


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/gucefMATH.h",
  "include/gucefMATH_CModule.h",
  "include/gucefMATH_config.h",
  "include/gucefMATH_CTDirectionVector2D.h",
  "include/gucefMATH_CTDirectionVector3D.h",
  "include/gucefMATH_CTMatrix3D.h",
  "include/gucefMATH_CTMatrix4D.h",
  "include/gucefMATH_CTPoint2D.h",
  "include/gucefMATH_CTPoint3D.h",
  "include/gucefMATH_CTSpace.h",
  "include/gucefMATH_CTVector1D.h",
  "include/gucefMATH_CTVector2D.h",
  "include/gucefMATH_CTVector3D.h",
  "include/gucefMATH_ETypes.h",
  "include/gucefMATH_macros.h",
  "include/gucefMATH_points.h",
  "include/gucefMATH_vectors.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/gucefMATH_CModule.cpp"
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

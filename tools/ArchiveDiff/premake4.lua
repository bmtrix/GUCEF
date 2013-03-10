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

-- Configuration for module: ArchiveDiff


configuration( { "LINUX" } )
  project( "ArchiveDiff" )

configuration( { "WIN32" } )
  project( "ArchiveDiff" )

configuration( { "WIN64" } )
  project( "ArchiveDiff" )
location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
language( "C" )

configuration( { "LINUX" } )
language( "C++" )

configuration( { "WIN32" } )
language( "C++" )

configuration( { "WIN64" } )
language( "C++" )

configuration( { "LINUX" } )
kind( "ConsoleApp" )
configuration( { "WIN32" } )
kind( "WindowedApp" )
configuration( { "WIN64" } )
kind( "WindowedApp" )

configuration( { "LINUX" } )
  links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )
  links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )
  defines( { "ARCHIVEDIFF_BUILD_MODULE" } )

configuration( { "WIN32" } )
  links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )
  links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )
  defines( { "ARCHIVEDIFF_BUILD_MODULE" } )

configuration( { "WIN64" } )
  links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )
  links( { "ArchiveDiffLib", "gucefCORE", "gucefMT", "gucefPATCHER" } )
  defines( { "ARCHIVEDIFF_BUILD_MODULE" } )


configuration( { "LINUX" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/ArchiveDiff_main.cpp"
    } )



configuration( { "WIN32" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/ArchiveDiff_main.cpp"
    } )



configuration( { "WIN64" } )
    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/ArchiveDiff_main.cpp"
    } )


configuration( {} )
includedirs( { "../../common/include", "../../gucefCOM/include", "../../gucefCOMCORE/include", "../../gucefCORE/include", "../../gucefMT/include", "../../gucefPATCHER/include", "../ArchiveDiffLib/include" } )

configuration( { "LINUX" } )
includedirs( { "../../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../../gucefCORE/include/mswin" } )

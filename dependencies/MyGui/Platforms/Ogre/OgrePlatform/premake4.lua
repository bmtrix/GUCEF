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

-- Configuration for module: MyGUI.OgrePlatform


configuration( { "LINUX" } )
  project( "MyGUI.OgrePlatform" )

configuration( { "WIN32" } )
  project( "MyGUI.OgrePlatform" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C" )

configuration( { "LINUX" } )
language( "C++" )

configuration( { "WIN32" } )
language( "C++" )

configuration( { "LINUX" } )


configuration( { LINUX } )
kind( "SharedLib" )
configuration( { "WIN32" } )


configuration( { WIN32 } )
kind( "SharedLib" )
  
configuration( { LINUX } )
links( { "MyGUI.Engine", "OgreMain" } )
  links( { "MyGUI.Engine", "OgreMain" } )
  
configuration( { WIN32 } )
links( { "MyGUI.Engine", "OgreMain" } )
  links( { "MyGUI.Engine", "OgreMain" } )


configuration( { "LINUX" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "../../../Common/FileSystemInfo/FileSystemInfo.h",
      "include/MyGUI_LastHeader.h",
      "include/MyGUI_OgreDataManager.h",
      "include/MyGUI_OgreDataStream.h",
      "include/MyGUI_OgreDiagnostic.h",
      "include/MyGUI_OgrePlatform.h",
      "include/MyGUI_OgreRenderManager.h",
      "include/MyGUI_OgreRTTexture.h",
      "include/MyGUI_OgreTexture.h",
      "include/MyGUI_OgreVertexBuffer.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/MyGUI_OgreDataManager.cpp",
      "src/MyGUI_OgreDataStream.cpp",
      "src/MyGUI_OgreRenderManager.cpp",
      "src/MyGUI_OgreRTTexture.cpp",
      "src/MyGUI_OgreTexture.cpp",
      "src/MyGUI_OgreVertexBuffer.cpp"
    } )



configuration( { "WIN32" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "../../../Common/FileSystemInfo/FileSystemInfo.h",
      "include/MyGUI_LastHeader.h",
      "include/MyGUI_OgreDataManager.h",
      "include/MyGUI_OgreDataStream.h",
      "include/MyGUI_OgreDiagnostic.h",
      "include/MyGUI_OgrePlatform.h",
      "include/MyGUI_OgreRenderManager.h",
      "include/MyGUI_OgreRTTexture.h",
      "include/MyGUI_OgreTexture.h",
      "include/MyGUI_OgreVertexBuffer.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "src/MyGUI_OgreDataManager.cpp",
      "src/MyGUI_OgreDataStream.cpp",
      "src/MyGUI_OgreRenderManager.cpp",
      "src/MyGUI_OgreRTTexture.cpp",
      "src/MyGUI_OgreTexture.cpp",
      "src/MyGUI_OgreVertexBuffer.cpp"
    } )


configuration( {} )
includedirs( { "../../../../freetype/include", "../../../../freetype/include/freetype", "../../../../freetype/include/freetype/config", "../../../../freetype/include/freetype/internal", "../../../../freetype/include/freetype/internal/services", "../../../../freetype/src/winfonts", "../../../MyGUIEngine/include" } )

configuration( { "LINUX" } )
includedirs( { "../../../Common/FileSystemInfo", "include" } )

configuration( { "WIN32" } )
includedirs( { "../../../Common/FileSystemInfo", "include" } )

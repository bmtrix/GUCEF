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

-- Configuration for module: MyGUI.SkinEditor


configuration( { "LINUX" } )
  project( "MyGUI.SkinEditor" )

configuration( { "WIN32" } )
  project( "MyGUI.SkinEditor" )

configuration( { "WIN64" } )
  project( "MyGUI.SkinEditor" )

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

configuration( { "WIN64" } )
language( "C++" )

configuration( { "LINUX" } )


configuration( { LINUX } )
kind( "ConsoleApp" )
configuration( { "WIN32" } )


configuration( { WIN32 } )
kind( "WindowedApp" )
configuration( { "WIN64" } )


configuration( { WIN64 } )
kind( "WindowedApp" )
  
configuration( { LINUX } )
links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  

configuration( { LINUX } )
defines( { "MYGUI_USE_FREETYPE" } )
  
configuration( { WIN32 } )
links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  

configuration( { WIN32 } )
defines( { "MYGUI_USE_FREETYPE" } )
  
configuration( { WIN64 } )
links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  links( { "MyGUI.Engine", "MyGUI.OpenGLPlatform", "freetype" } )
  

configuration( { WIN64 } )
defines( { "MYGUI_USE_FREETYPE" } )


configuration( { "LINUX" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "ActionManager.h",
      "Application.h",
      "AreaSelectorControl.h",
      "BackgroundControl.h",
      "Binary.h",
      "ColourManager.h",
      "ColourPanel.h",
      "CommandManager.h",
      "EditorState.h",
      "ExportManager.h",
      "HorizontalSelectorBlackControl.h",
      "HorizontalSelectorControl.h",
      "HotKeyCommand.h",
      "HotKeyManager.h",
      "ItemHolder.h",
      "Localise.h",
      "MainMenuControl.h",
      "MainPane.h",
      "MessageBoxFadeControl.h",
      "MessageBoxManager.h",
      "MyGUI_FilterNoneSkin.h",
      "PositionSelectorBlackControl.h",
      "PositionSelectorControl.h",
      "Property.h",
      "PropertyAdvisor.h",
      "PropertyAlignControl.h",
      "PropertyBoolControl.h",
      "PropertyColourControl.h",
      "PropertyControl.h",
      "PropertyInt2Control.h",
      "PropertyInt4Control.h",
      "PropertyIntControl.h",
      "PropertyRegionTypeControl.h",
      "PropertySet.h",
      "PropertyTexturesControl.h",
      "RecentFilesManager.h",
      "RegionControl.h",
      "RegionItem.h",
      "RegionListControl.h",
      "RegionPropertyControl.h",
      "RegionTextureControl.h",
      "SelectorControl.h",
      "SeparatorControl.h",
      "SeparatorItem.h",
      "SeparatorListControl.h",
      "SeparatorPropertyControl.h",
      "SeparatorTextureControl.h",
      "SettingsGeneralControl.h",
      "SettingsManager.h",
      "SettingsResourcePathsControl.h",
      "SettingsResourcesControl.h",
      "SettingsSector.h",
      "SettingsWindow.h",
      "SkinControl.h",
      "SkinItem.h",
      "SkinListControl.h",
      "SkinManager.h",
      "SkinPropertyControl.h",
      "SkinTextureControl.h",
      "StateControl.h",
      "StateController.h",
      "StateItem.h",
      "StateListControl.h",
      "StateManager.h",
      "StatePropertyControl.h",
      "StateTextureControl.h",
      "TestState.h",
      "TestWindow.h",
      "TextFieldControl.h",
      "TextureBrowseCell.h",
      "TextureBrowseControl.h",
      "TextureBrowseItemBox.h",
      "TextureControl.h",
      "TextureToolControl.h",
      "VerticalSelectorBlackControl.h",
      "VerticalSelectorControl.h",
      "../../Common/Precompiled.h",
      "../../Common/Base/InputFocusInfo.h",
      "../../Common/Base/Main.h",
      "../../Common/Base/StatisticInfo.h",
      "../../Common/Base/OpenGL/BaseManager.h",
      "../../Common/Input/InputConverter.h",
      "../../Common/Input/OIS/InputManager.h",
      "../../Common/Input/OIS/PointerManager.h",
      "../../Common/ItemBox/BaseCellView.h",
      "../../Common/ItemBox/BaseItemBox.h",
      "../../Common/ItemBox/ItemDropInfo.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "ActionManager.cpp",
      "Application.cpp",
      "AreaSelectorControl.cpp",
      "BackgroundControl.cpp",
      "ColourManager.cpp",
      "ColourPanel.cpp",
      "CommandManager.cpp",
      "EditorState.cpp",
      "ExportManager.cpp",
      "HorizontalSelectorBlackControl.cpp",
      "HorizontalSelectorControl.cpp",
      "HotKeyManager.cpp",
      "MainMenuControl.cpp",
      "MainPane.cpp",
      "MessageBoxFadeControl.cpp",
      "MessageBoxManager.cpp",
      "MyGUI_FilterNoneSkin.cpp",
      "PositionSelectorBlackControl.cpp",
      "PositionSelectorControl.cpp",
      "Property.cpp",
      "PropertyAlignControl.cpp",
      "PropertyBoolControl.cpp",
      "PropertyColourControl.cpp",
      "PropertyControl.cpp",
      "PropertyInt2Control.cpp",
      "PropertyInt4Control.cpp",
      "PropertyIntControl.cpp",
      "PropertyRegionTypeControl.cpp",
      "PropertySet.cpp",
      "PropertyTexturesControl.cpp",
      "RecentFilesManager.cpp",
      "RegionControl.cpp",
      "RegionItem.cpp",
      "RegionListControl.cpp",
      "RegionPropertyControl.cpp",
      "RegionTextureControl.cpp",
      "SelectorControl.cpp",
      "SeparatorControl.cpp",
      "SeparatorItem.cpp",
      "SeparatorListControl.cpp",
      "SeparatorPropertyControl.cpp",
      "SeparatorTextureControl.cpp",
      "SettingsGeneralControl.cpp",
      "SettingsManager.cpp",
      "SettingsResourcePathsControl.cpp",
      "SettingsResourcesControl.cpp",
      "SettingsSector.cpp",
      "SettingsWindow.cpp",
      "SkinControl.cpp",
      "SkinItem.cpp",
      "SkinListControl.cpp",
      "SkinManager.cpp",
      "SkinPropertyControl.cpp",
      "SkinTextureControl.cpp",
      "StateControl.cpp",
      "StateItem.cpp",
      "StateListControl.cpp",
      "StateManager.cpp",
      "StatePropertyControl.cpp",
      "StateTextureControl.cpp",
      "TestState.cpp",
      "TestWindow.cpp",
      "TextFieldControl.cpp",
      "TextureBrowseCell.cpp",
      "TextureBrowseControl.cpp",
      "TextureBrowseItemBox.cpp",
      "TextureControl.cpp",
      "TextureToolControl.cpp",
      "VerticalSelectorBlackControl.cpp",
      "VerticalSelectorControl.cpp",
      "../../Common/Precompiled.cpp",
      "../../Common/Base/OpenGL/BaseManager.cpp",
      "../../Common/Input/OIS/InputManager.cpp",
      "../../Common/Input/OIS/PointerManager.cpp"
    } )



configuration( { "WIN32" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "ActionManager.h",
      "Application.h",
      "AreaSelectorControl.h",
      "BackgroundControl.h",
      "Binary.h",
      "ColourManager.h",
      "ColourPanel.h",
      "CommandManager.h",
      "EditorState.h",
      "ExportManager.h",
      "HorizontalSelectorBlackControl.h",
      "HorizontalSelectorControl.h",
      "HotKeyCommand.h",
      "HotKeyManager.h",
      "ItemHolder.h",
      "Localise.h",
      "MainMenuControl.h",
      "MainPane.h",
      "MessageBoxFadeControl.h",
      "MessageBoxManager.h",
      "MyGUI_FilterNoneSkin.h",
      "PositionSelectorBlackControl.h",
      "PositionSelectorControl.h",
      "Property.h",
      "PropertyAdvisor.h",
      "PropertyAlignControl.h",
      "PropertyBoolControl.h",
      "PropertyColourControl.h",
      "PropertyControl.h",
      "PropertyInt2Control.h",
      "PropertyInt4Control.h",
      "PropertyIntControl.h",
      "PropertyRegionTypeControl.h",
      "PropertySet.h",
      "PropertyTexturesControl.h",
      "RecentFilesManager.h",
      "RegionControl.h",
      "RegionItem.h",
      "RegionListControl.h",
      "RegionPropertyControl.h",
      "RegionTextureControl.h",
      "SelectorControl.h",
      "SeparatorControl.h",
      "SeparatorItem.h",
      "SeparatorListControl.h",
      "SeparatorPropertyControl.h",
      "SeparatorTextureControl.h",
      "SettingsGeneralControl.h",
      "SettingsManager.h",
      "SettingsResourcePathsControl.h",
      "SettingsResourcesControl.h",
      "SettingsSector.h",
      "SettingsWindow.h",
      "SkinControl.h",
      "SkinItem.h",
      "SkinListControl.h",
      "SkinManager.h",
      "SkinPropertyControl.h",
      "SkinTextureControl.h",
      "StateControl.h",
      "StateController.h",
      "StateItem.h",
      "StateListControl.h",
      "StateManager.h",
      "StatePropertyControl.h",
      "StateTextureControl.h",
      "TestState.h",
      "TestWindow.h",
      "TextFieldControl.h",
      "TextureBrowseCell.h",
      "TextureBrowseControl.h",
      "TextureBrowseItemBox.h",
      "TextureControl.h",
      "TextureToolControl.h",
      "VerticalSelectorBlackControl.h",
      "VerticalSelectorControl.h",
      "../../Common/Precompiled.h",
      "../../Common/Base/InputFocusInfo.h",
      "../../Common/Base/Main.h",
      "../../Common/Base/StatisticInfo.h",
      "../../Common/Base/OpenGL/BaseManager.h",
      "../../Common/Input/InputConverter.h",
      "../../Common/Input/Win32API/InputManager.h",
      "../../Common/Input/Win32API/PointerManager.h",
      "../../Common/ItemBox/BaseCellView.h",
      "../../Common/ItemBox/BaseItemBox.h",
      "../../Common/ItemBox/ItemDropInfo.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "ActionManager.cpp",
      "Application.cpp",
      "AreaSelectorControl.cpp",
      "BackgroundControl.cpp",
      "ColourManager.cpp",
      "ColourPanel.cpp",
      "CommandManager.cpp",
      "EditorState.cpp",
      "ExportManager.cpp",
      "HorizontalSelectorBlackControl.cpp",
      "HorizontalSelectorControl.cpp",
      "HotKeyManager.cpp",
      "MainMenuControl.cpp",
      "MainPane.cpp",
      "MessageBoxFadeControl.cpp",
      "MessageBoxManager.cpp",
      "MyGUI_FilterNoneSkin.cpp",
      "PositionSelectorBlackControl.cpp",
      "PositionSelectorControl.cpp",
      "Property.cpp",
      "PropertyAlignControl.cpp",
      "PropertyBoolControl.cpp",
      "PropertyColourControl.cpp",
      "PropertyControl.cpp",
      "PropertyInt2Control.cpp",
      "PropertyInt4Control.cpp",
      "PropertyIntControl.cpp",
      "PropertyRegionTypeControl.cpp",
      "PropertySet.cpp",
      "PropertyTexturesControl.cpp",
      "RecentFilesManager.cpp",
      "RegionControl.cpp",
      "RegionItem.cpp",
      "RegionListControl.cpp",
      "RegionPropertyControl.cpp",
      "RegionTextureControl.cpp",
      "SelectorControl.cpp",
      "SeparatorControl.cpp",
      "SeparatorItem.cpp",
      "SeparatorListControl.cpp",
      "SeparatorPropertyControl.cpp",
      "SeparatorTextureControl.cpp",
      "SettingsGeneralControl.cpp",
      "SettingsManager.cpp",
      "SettingsResourcePathsControl.cpp",
      "SettingsResourcesControl.cpp",
      "SettingsSector.cpp",
      "SettingsWindow.cpp",
      "SkinControl.cpp",
      "SkinItem.cpp",
      "SkinListControl.cpp",
      "SkinManager.cpp",
      "SkinPropertyControl.cpp",
      "SkinTextureControl.cpp",
      "StateControl.cpp",
      "StateItem.cpp",
      "StateListControl.cpp",
      "StateManager.cpp",
      "StatePropertyControl.cpp",
      "StateTextureControl.cpp",
      "TestState.cpp",
      "TestWindow.cpp",
      "TextFieldControl.cpp",
      "TextureBrowseCell.cpp",
      "TextureBrowseControl.cpp",
      "TextureBrowseItemBox.cpp",
      "TextureControl.cpp",
      "TextureToolControl.cpp",
      "VerticalSelectorBlackControl.cpp",
      "VerticalSelectorControl.cpp",
      "../../Common/Precompiled.cpp",
      "../../Common/Base/OpenGL/BaseManager.cpp",
      "../../Common/Input/Win32API/InputManager.cpp",
      "../../Common/Input/Win32API/PointerManager.cpp"
    } )



configuration( { "WIN64" } )
    vpaths { ["Platform Headers"] = { "**.h", "**.hpp", "**.hxx" } }
    files( {
      "ActionManager.h",
      "Application.h",
      "AreaSelectorControl.h",
      "BackgroundControl.h",
      "Binary.h",
      "ColourManager.h",
      "ColourPanel.h",
      "CommandManager.h",
      "EditorState.h",
      "ExportManager.h",
      "HorizontalSelectorBlackControl.h",
      "HorizontalSelectorControl.h",
      "HotKeyCommand.h",
      "HotKeyManager.h",
      "ItemHolder.h",
      "Localise.h",
      "MainMenuControl.h",
      "MainPane.h",
      "MessageBoxFadeControl.h",
      "MessageBoxManager.h",
      "MyGUI_FilterNoneSkin.h",
      "PositionSelectorBlackControl.h",
      "PositionSelectorControl.h",
      "Property.h",
      "PropertyAdvisor.h",
      "PropertyAlignControl.h",
      "PropertyBoolControl.h",
      "PropertyColourControl.h",
      "PropertyControl.h",
      "PropertyInt2Control.h",
      "PropertyInt4Control.h",
      "PropertyIntControl.h",
      "PropertyRegionTypeControl.h",
      "PropertySet.h",
      "PropertyTexturesControl.h",
      "RecentFilesManager.h",
      "RegionControl.h",
      "RegionItem.h",
      "RegionListControl.h",
      "RegionPropertyControl.h",
      "RegionTextureControl.h",
      "SelectorControl.h",
      "SeparatorControl.h",
      "SeparatorItem.h",
      "SeparatorListControl.h",
      "SeparatorPropertyControl.h",
      "SeparatorTextureControl.h",
      "SettingsGeneralControl.h",
      "SettingsManager.h",
      "SettingsResourcePathsControl.h",
      "SettingsResourcesControl.h",
      "SettingsSector.h",
      "SettingsWindow.h",
      "SkinControl.h",
      "SkinItem.h",
      "SkinListControl.h",
      "SkinManager.h",
      "SkinPropertyControl.h",
      "SkinTextureControl.h",
      "StateControl.h",
      "StateController.h",
      "StateItem.h",
      "StateListControl.h",
      "StateManager.h",
      "StatePropertyControl.h",
      "StateTextureControl.h",
      "TestState.h",
      "TestWindow.h",
      "TextFieldControl.h",
      "TextureBrowseCell.h",
      "TextureBrowseControl.h",
      "TextureBrowseItemBox.h",
      "TextureControl.h",
      "TextureToolControl.h",
      "VerticalSelectorBlackControl.h",
      "VerticalSelectorControl.h",
      "../../Common/Precompiled.h",
      "../../Common/Base/InputFocusInfo.h",
      "../../Common/Base/Main.h",
      "../../Common/Base/StatisticInfo.h",
      "../../Common/Base/OpenGL/BaseManager.h",
      "../../Common/Input/InputConverter.h",
      "../../Common/Input/Win32API/InputManager.h",
      "../../Common/Input/Win32API/PointerManager.h",
      "../../Common/ItemBox/BaseCellView.h",
      "../../Common/ItemBox/BaseItemBox.h",
      "../../Common/ItemBox/ItemDropInfo.h"
    } )

    vpaths { ["Platform Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
    files( {
      "ActionManager.cpp",
      "Application.cpp",
      "AreaSelectorControl.cpp",
      "BackgroundControl.cpp",
      "ColourManager.cpp",
      "ColourPanel.cpp",
      "CommandManager.cpp",
      "EditorState.cpp",
      "ExportManager.cpp",
      "HorizontalSelectorBlackControl.cpp",
      "HorizontalSelectorControl.cpp",
      "HotKeyManager.cpp",
      "MainMenuControl.cpp",
      "MainPane.cpp",
      "MessageBoxFadeControl.cpp",
      "MessageBoxManager.cpp",
      "MyGUI_FilterNoneSkin.cpp",
      "PositionSelectorBlackControl.cpp",
      "PositionSelectorControl.cpp",
      "Property.cpp",
      "PropertyAlignControl.cpp",
      "PropertyBoolControl.cpp",
      "PropertyColourControl.cpp",
      "PropertyControl.cpp",
      "PropertyInt2Control.cpp",
      "PropertyInt4Control.cpp",
      "PropertyIntControl.cpp",
      "PropertyRegionTypeControl.cpp",
      "PropertySet.cpp",
      "PropertyTexturesControl.cpp",
      "RecentFilesManager.cpp",
      "RegionControl.cpp",
      "RegionItem.cpp",
      "RegionListControl.cpp",
      "RegionPropertyControl.cpp",
      "RegionTextureControl.cpp",
      "SelectorControl.cpp",
      "SeparatorControl.cpp",
      "SeparatorItem.cpp",
      "SeparatorListControl.cpp",
      "SeparatorPropertyControl.cpp",
      "SeparatorTextureControl.cpp",
      "SettingsGeneralControl.cpp",
      "SettingsManager.cpp",
      "SettingsResourcePathsControl.cpp",
      "SettingsResourcesControl.cpp",
      "SettingsSector.cpp",
      "SettingsWindow.cpp",
      "SkinControl.cpp",
      "SkinItem.cpp",
      "SkinListControl.cpp",
      "SkinManager.cpp",
      "SkinPropertyControl.cpp",
      "SkinTextureControl.cpp",
      "StateControl.cpp",
      "StateItem.cpp",
      "StateListControl.cpp",
      "StateManager.cpp",
      "StatePropertyControl.cpp",
      "StateTextureControl.cpp",
      "TestState.cpp",
      "TestWindow.cpp",
      "TextFieldControl.cpp",
      "TextureBrowseCell.cpp",
      "TextureBrowseControl.cpp",
      "TextureBrowseItemBox.cpp",
      "TextureControl.cpp",
      "TextureToolControl.cpp",
      "VerticalSelectorBlackControl.cpp",
      "VerticalSelectorControl.cpp",
      "../../Common/Precompiled.cpp",
      "../../Common/Base/OpenGL/BaseManager.cpp",
      "../../Common/Input/Win32API/InputManager.cpp",
      "../../Common/Input/Win32API/PointerManager.cpp"
    } )


configuration( {} )
includedirs( { "../../../freetype/include", "../../../freetype/include/freetype", "../../../freetype/include/freetype/config", "../../../freetype/include/freetype/internal", "../../../freetype/include/freetype/internal/services", "../../../freetype/src/winfonts", "../../Common/FileSystemInfo", "../../MyGUIEngine/include", "../../Platforms/OpenGL/OpenGLPlatform/include", "../../Platforms/OpenGL/OpenGLPlatform/include/GL" } )

configuration( { "LINUX" } )
includedirs( { "../SkinEditor", "../../Common", "../../Common/Base", "../../Common/Base/OpenGL", "../../Common/Input", "../../Common/Input/OIS", "../../Common/ItemBox" } )

configuration( { "WIN32" } )
includedirs( { "../SkinEditor", "../../Common", "../../Common/Base", "../../Common/Base/OpenGL", "../../Common/Input", "../../Common/Input/Win32API", "../../Common/ItemBox" } )

configuration( { "WIN64" } )
includedirs( { "../SkinEditor", "../../Common", "../../Common/Base", "../../Common/Base/OpenGL", "../../Common/Input", "../../Common/Input/Win32API", "../../Common/ItemBox" } )

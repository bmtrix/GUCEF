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

-- Configuration for module: gucefGUI


project( "gucefGUI" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C++" )



configuration( {} )
kind( "SharedLib" )

configuration( {} )
links( { "gucefCORE", "gucefIMAGE", "gucefMT", "gucefVFS" } )
links( { "gucefCORE", "gucefIMAGE", "gucefMT", "gucefVFS" } )


configuration( {} )
defines( { "GUCEF_GUI_BUILD_MODULE" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/gucefGUI.h",
  "include/gucefGUI_CButton.h",
  "include/gucefGUI_CCheckbox.h",
  "include/gucefGUI_CCombobox.h",
  "include/gucefGUI_CEditbox.h",
  "include/gucefGUI_CFileSystemDialog.h",
  "include/gucefGUI_CForm.h",
  "include/gucefGUI_CFormBackend.h",
  "include/gucefGUI_CFormEx.h",
  "include/gucefGUI_CFormFactory.h",
  "include/gucefGUI_CGridView.h",
  "include/gucefGUI_CGUIDriver.h",
  "include/gucefGUI_CGuiGlobal.h",
  "include/gucefGUI_CGUIManager.h",
  "include/gucefGUI_CIFileSystemInfoProvider.h",
  "include/gucefGUI_CIGUIContext.h",
  "include/gucefGUI_CImageFrame.h",
  "include/gucefGUI_CLabel.h",
  "include/gucefGUI_CListBox.h",
  "include/gucefGUI_CMenuBar.h",
  "include/gucefGUI_CModule.h",
  "include/gucefGUI_config.h",
  "include/gucefGUI_CPopupMenu.h",
  "include/gucefGUI_CProgressBar.h",
  "include/gucefGUI_CPushButton.h",
  "include/gucefGUI_CRenderContext.h",
  "include/gucefGUI_CSpinner.h",
  "include/gucefGUI_CTabContentPane.h",
  "include/gucefGUI_CTabControl.h",
  "include/gucefGUI_CTextbox.h",
  "include/gucefGUI_CTreeview.h",
  "include/gucefGUI_CUDim.h",
  "include/gucefGUI_CUVector.h",
  "include/gucefGUI_CVideoOptions.h",
  "include/gucefGUI_CVideoSettings.h",
  "include/gucefGUI_CWidget.h",
  "include/gucefGUI_CWidgetFactory.h",
  "include/gucefGUI_CWindow.h",
  "include/gucefGUI_CWindowContext.h",
  "include/gucefGUI_CWindowManager.h",
  "include/gucefGUI_CWindowManagerBackend.h",
  "include/gucefGUI_ETypes.h",
  "include/gucefGUI_macros.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/gucefGUI.cpp",
  "src/gucefGUI_CButton.cpp",
  "src/gucefGUI_CCheckbox.cpp",
  "src/gucefGUI_CCombobox.cpp",
  "src/gucefGUI_CEditbox.cpp",
  "src/gucefGUI_CFileSystemDialog.cpp",
  "src/gucefGUI_CForm.cpp",
  "src/gucefGUI_CFormBackend.cpp",
  "src/gucefGUI_CFormEx.cpp",
  "src/gucefGUI_CFormFactory.cpp",
  "src/gucefGUI_CGridView.cpp",
  "src/gucefGUI_CGUIDriver.cpp",
  "src/gucefGUI_CGuiGlobal.cpp",
  "src/gucefGUI_CGUIManager.cpp",
  "src/gucefGUI_CIFileSystemInfoProvider.cpp",
  "src/gucefGUI_CIGUIContext.cpp",
  "src/gucefGUI_CImageFrame.cpp",
  "src/gucefGUI_CLabel.cpp",
  "src/gucefGUI_CListbox.cpp",
  "src/gucefGUI_CMenuBar.cpp",
  "src/gucefGUI_CModule.cpp",
  "src/gucefGUI_CPopupMenu.cpp",
  "src/gucefGUI_CProgressBar.cpp",
  "src/gucefGUI_CPushButton.cpp",
  "src/gucefGUI_CRenderContext.cpp",
  "src/gucefGUI_CSpinner.cpp",
  "src/gucefGUI_CTabContentPane.cpp",
  "src/gucefGUI_CTabControl.cpp",
  "src/gucefGUI_CTextbox.cpp",
  "src/gucefGUI_CTreeview.cpp",
  "src/gucefGUI_CUDim.cpp",
  "src/gucefGUI_CUVector.cpp",
  "src/gucefGUI_CVideoOptions.cpp",
  "src/gucefGUI_CVideoSettings.cpp",
  "src/gucefGUI_CWidget.cpp",
  "src/gucefGUI_CWidgetFactory.cpp",
  "src/gucefGUI_CWindow.cpp",
  "src/gucefGUI_CWindowContext.cpp",
  "src/gucefGUI_CWindowManager.cpp",
  "src/gucefGUI_CWindowManagerBackend.cpp"
 } )


configuration( {} )
includedirs( { "../common/include", "../gucefCORE/include", "../gucefIMAGE/include", "../gucefMT/include", "../gucefVFS/include", "include" } )

configuration( { "ANDROID" } )
includedirs( { "../gucefCORE/include/android" } )

configuration( { "LINUX" } )
includedirs( { "../gucefCORE/include/linux" } )

configuration( { "WIN32" } )
includedirs( { "../gucefCORE/include/mswin" } )

configuration( { "WIN64" } )
includedirs( { "../gucefCORE/include/mswin" } )

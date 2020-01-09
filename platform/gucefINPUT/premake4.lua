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

-- Configuration for module: gucefINPUT


project( "gucefINPUT" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C++" )



configuration( {} )
kind( "SharedLib" )

configuration( {} )
links( { "gucefCORE", "gucefMT" } )
links( { "gucefCORE", "gucefMT" } )


configuration( {} )
defines( { "GUCEFINPUT_BUILD_MODULE" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/CGUCEFINPUTModule.h",
  "include/CInputActionMap.h",
  "include/CInputContext.h",
  "include/CInputController.h",
  "include/CInputDriverPlugin.h",
  "include/gucefINPUT.h",
  "include/gucefINPUTDLLInit.h",
  "include/gucefINPUT_ActionEventData.h",
  "include/gucefINPUT_CAbstractInputDevice.h",
  "include/gucefINPUT_CActionEventData.h",
  "include/gucefINPUT_CInputDevice.h",
  "include/gucefINPUT_CInputDriver.h",
  "include/gucefINPUT_CInputDriverPluginManager.h",
  "include/gucefINPUT_CInputGlobal.h",
  "include/gucefINPUT_CInputObserverSwitch.h",
  "include/gucefINPUT_CKeyboard.h",
  "include/gucefINPUT_CKeyModStateChangedEventData.h",
  "include/gucefINPUT_CKeyStateChangedEventData.h",
  "include/gucefINPUT_CMouse.h",
  "include/gucefINPUT_CMouseButtonEventData.h",
  "include/gucefINPUT_CMouseMovedEventData.h",
  "include/gucefINPUT_config.h",
  "include/gucefINPUT_CTConcreteActionEventData.h",
  "include/gucefINPUT_ETypes.h",
  "include/gucefINPUT_keyboard.h",
  "include/gucefINPUT_macros.h",
  "include/inputdriverpluginstructs.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/CGUCEFINPUTModule.cpp",
  "src/CInputActionMap.cpp",
  "src/CInputContext.cpp",
  "src/CInputController.cpp",
  "src/CInputDriverPlugin.cpp",
  "src/gucefINPUT.cpp",
  "src/gucefINPUT_CAbstractInputDevice.cpp",
  "src/gucefINPUT_CActionEventData.cpp",
  "src/gucefINPUT_CInputDriver.cpp",
  "src/gucefINPUT_CInputDriverPluginManager.cpp",
  "src/gucefINPUT_CInputGlobal.cpp",
  "src/gucefINPUT_CInputObserverSwitch.cpp",
  "src/gucefINPUT_CKeyboard.cpp",
  "src/gucefINPUT_CKeyModStateChangedEventData.cpp",
  "src/gucefINPUT_CKeyStateChangedEventData.cpp",
  "src/gucefINPUT_CMouse.cpp",
  "src/gucefINPUT_CMouseButtonEventData.cpp",
  "src/gucefINPUT_CMouseMovedEventData.cpp",
  "src/gucefINPUT_keyboard.cpp"
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
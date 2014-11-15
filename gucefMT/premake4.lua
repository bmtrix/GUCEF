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

-- Configuration for module: gucefMT


project( "gucefMT" )

configuration( {} )
  location( os.getenv( "PM4OUTPUTDIR" ) )

configuration( {} )
  targetdir( os.getenv( "PM4TARGETDIR" ) )

configuration( {} )
language( "C++" )



configuration( {} )
kind( "SharedLib" )


configuration( {} )
defines( { "GUCEF_MT_BUILD_MODULE" } )
  links( { "pthread" } )
  links( { "Winmm" } )
  links( { "Winmm" } )


configuration( {} )
vpaths { ["Headers"] = { "**.h", "**.hpp", "**.hxx" } }
files( {
  "include/gucefMT.h",
  "include/gucefMT_basicMacros.h",
  "include/gucefMT_CActiveObject.h",
  "include/gucefMT_CCondition.h",
  "include/gucefMT_CCriticalSection.h",
  "include/gucefMT_CGUCEFMTModule.h",
  "include/gucefMT_CICloneable.h",
  "include/gucefMT_CMutex.h",
  "include/gucefMT_config.h",
  "include/gucefMT_CReadWriteLock.h",
  "include/gucefMT_CScopeMutex.h",
  "include/gucefMT_CSemaphore.h",
  "include/gucefMT_CTMailBox.h",
  "include/gucefMT_dvmtoswrap.h",
  "include/gucefMT_DVRWLOCK.h",
  "include/gucefMT_ETypes.h",
  "include/gucefMT_macros.h",
  "include/gucefMT_mutex.h"
 } )



configuration( {} )
vpaths { ["Source"] = { "**.c", "**.cpp", "**.cs", "**.asm" } }
files( {
  "src/gucefMT.cpp",
  "src/gucefMT_CActiveObject.cpp",
  "src/gucefMT_CCondition.cpp",
  "src/gucefMT_CCriticalSection.cpp",
  "src/gucefMT_CGUCEFMTModule.cpp",
  "src/gucefMT_CICloneable.cpp",
  "src/gucefMT_CMutex.cpp",
  "src/gucefMT_CReadWriteLock.cpp",
  "src/gucefMT_CScopeMutex.cpp",
  "src/gucefMT_CSemaphore.cpp",
  "src/gucefMT_CTMailBox.cpp",
  "src/gucefMT_dvmtoswrap.c",
  "src/gucefMT_DVRWLOCK.c",
  "src/gucefMT_MUTEX.c"
 } )


configuration( {} )
includedirs( { "../common/include", "include" } )

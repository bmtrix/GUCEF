CALL CMakeCommon.bat

ECHO *** Set MVC11 specifics and run CMake ***

SET MVC11_OUTPUTDIR="%OUTPUTDIR%\MVC11"
CMake.exe -DBUILD_SHARED_LIBS=ON -G"Visual Studio 11" -H"%SRCROOTDIR%" -B%MVC11_OUTPUTDIR%
PAUSE
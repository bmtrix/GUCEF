for /f %%i in ("%0") do SET VS2010_BATCHPATH=%%~dpi

SET PM5OUTSUBDIR=PM5MVC10
SET PM5TARGETSUBDIR=PM5MVC10\bin
SET NOPAUSE=TRUE

CALL Premake5Common.bat

ECHO *** Set MVC10 specifics and run Pemake 5 ***

CD %GUCEF_HOME%
%VS2010_BATCHPATH%\premake5.exe vs2010
PAUSE
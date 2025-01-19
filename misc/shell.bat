@echo off
REM Initialize the Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

REM Add your project directory to the PATH for convenience
set path=C:\handmade\misc;%path%

REM Optional: Change directory to the project folder
cd /d C:\handmade\misc

REM Indicate success
echo Environment set up. Ready to use 'cl'.

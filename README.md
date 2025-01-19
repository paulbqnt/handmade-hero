# Handmade Hero

My personal fork of *Handmade Hero*, an ongoing project by Casey Muratori to create a complete, professional-quality game from scratch in C.

---
## Prerequisites

- **Operating System**: Windows
- **IDE**: Visual Studio Community 2022
---

## Day 1 - Setting Up the Windows Build
[Watch the Video](https://www.youtube.com/watch?v=Ee3EtYb8d1o)

This session focuses on creating `shell.bat` and `build.bat` to simplify building and debugging the project.

### Steps

#### 1. Create the Project Folder Structure

Create the `C:\handmade` folder with the following subdirectories:

(code, data, misc)

---

#### 2. Modify the Microsoft Command Prompt

Update the shortcut for the Command Prompt to load the project environment automatically:

- **Properties > Shortcut > Target**:

`%windir%\system32\cmd.exe /k C:\handmade\misc\shell.bat`

---

#### 3. Create `shell.bat`

Place the following script in `C:\handmade\misc\shell.bat`:

```batch
@echo off
REM Initialize the Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

REM Add the project directory to the PATH for convenience
set path=C:\handmade\misc;%path%

REM Optional: Change directory to the misc folder
cd /d C:\handmade\misc

REM Indicate success
echo Environment set up. Ready to use 'cl'.
```

---

#### 4. Create the Build Script

Save the following script as `C:\handmade\code\build.bat`

```batch
@echo off
REM Create the build folder if it doesn’t exist
mkdir ..\..\build

REM Navigate to the build directory
pushd ..\..\build

REM Compile the code
cl -Zi ..\handmade\code\win32_handmade.cpp user32.lib gdi32.lib

REM Return to the original directory
popd
```
---

## Day 2 - Opening a Win32 Window
[Watch the Video](https://www.youtube.com/watch?v=4ROiWonnWGk)

Define the basic structure for creating a Win32 window (based on window.h).

---

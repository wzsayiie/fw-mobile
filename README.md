## Introduction

This is a framework and demonstration for mobile development.

Currently developing by
*Xcode*, *Android Studio* and *Unity* are supported.

## Directories Structure

**App Projects:**

These are `Android Studio`, `Xcode` and `Unity` projects,

* app_android/
* app_ios/
* app_unity/

**App Build Scripts:**

For building Android and iOS app, and placing them to *BUILD/*.
Files without suffix name for macOS, and *.bat for Windows.

* build_android
* build_android.bat
* build_ios
* build_unity_android
* build_unity_android.bat
* build_unity_ios

**Portable Custom App:**

Lightweight application framework.
Developer can use them to build little, portable application.

* core_xapp/
* core_xgame/

**Tools:**

Tools and the projects
(created by `Xcode`, `Visual Studio` and `Visutal Studio for Mac`)
can build them,
developer can use them to edit source files and project files.

* EDITOR_CPP/
* EDITOR_CPP_OSX/
* EDITOR_CPP_WIN32/
* EDITOR_CS/
* EDITOR_CS_OSX/
* EDITOR_CS_WIN32/

These scripts traverse headers and create new homonymic headers
which reference former to *GENERATED_HEADERS/*.
It will avoid developer adding vast header search paths tediously.

* generate_headers
* generate_headers.bat

**Unity Package Export Scripts**

These scripts will export the generic part of *app_unity/Assets*
to **unitypackage** to *BUILD/*.

* export_unity_pkg
* export_unity_pkg.bat

**Portable Library:**

The corss-platform source,
that can be compiled and executed on Android and iOS.

* library_android/
* library_ios/
* library0/
* library1/

**Library Build Scripts:**

The scripts will compile portable libary,
and copy them to *app_unity/Assets/Plugins*.

* makelib_android
* makelib_android.bat
* makelib_ios.bat
* makelib_ios_res
* makelib_osx
* makelib_win32.bat

*NOTE*: macOS and Windows build scripts are provided,
because developer need the library possibly on Unity editor.

**External Libraries from Thirds:**

* thirds_android/
* thirds_ios/

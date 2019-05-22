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

* build_as_apk
* build_as_apk.bat
* build_unity_apk
* build_unity_apk.bat
* build_unity_ipa
* build_xcode_ipa

**Tools:**

Tools and the projects
(created by `Xcode`, `Visual Studio` and `Visutal Studio for Mac`)
can build them,
developer can use them to edit source files and project files.

* EDITOR_CPP/
* EDITOR_CPP_OSX/
* EDITOR_CPP_WINDOWS/
* EDITOR_CS_OSX/
* EDITOR_CS_WINDOWS/

These scripts traverse headers and create new homonymic headers
which reference former to *GENERATED_HEADERS/*.
It will avoid developer adding vast header search paths tediously.

* generate_headers
* generate_headers.bat

**Portable Library:**

The corss-platform source,
that can be compiled and executed on Android and iOS.

* library
* library_android
* library_ios

**Library Build Scripts:**

The scripts will compile portable libary,
and copy them to *app_unity/Assets/Plugins*.

* make_as_aar
* make_as_aar.bat
* make_vs_dll.bat
* make_xcode_a_ios
* make_xcode_bundle_ios
* make_xcode_dylib_osx

*NOTE*: macOS and Windows build scripts are provided,
because developer need the library possibly on Unity editor.

**Portable Custom App:**

Lightweight application framework.
Developer can use them to build little, portable application.

* program_cpp
* program_lua

**External Libraries from Thirds:**

* thirds_android/
* thirds_ios/

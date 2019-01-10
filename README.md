## Introduction

This is a framework and demonstration for mobile development.

Currently developing by
*Xcode*, *Android Studio* and *Unity* are supported.

## Top Directory's Naming Style

If a direcotory is *necessary* for building Android and iOS app,
then it named by *lowercase* and *underline*,
otherwise it's name constituted by uppercase and underline.

## Directories Structure

**App Projects:**

These are `Android Studio`, `Xcode` and `Unity` project,

* app_android/
* app_ios/
* app_unity/

**App Build Scripts:**

For building Android and iOS app, and placing them to *build/*.
to run `*.sh` on macOS, run `*.bat` on Windows.

* build/
* build_android.sh
* build_android.bat
* build_ios.sh
* build_unity.sh
* build_unity.bat

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

**Portable Library:**

The corss-platform source,
that can be compiled and executed on Android and iOS.

*NOTE*: there are macOS and Windows Project,
because developer need the library possibly on Unity editor.

* library
* library_android
* library_ios
* library_osx
* library_windows

**Library Build Scripts:**

The scripts will compile portable libary,
and copy them to *app_unity/Plugins*.

* lib_build_android.bat
* lib_build_android.sh
* lib_build_ios.sh
* lib_build_osx.sh
* lib_build_windows.bat

**Resource Dispatch:**

Copy the recource files (e.g. configuration files, pictures) to *app_unity*.

* lib_copy_res.bat
* lib_copy_res.sh

**External Libraries from Thirds:**

* thirds_android/
* thirds_ios/

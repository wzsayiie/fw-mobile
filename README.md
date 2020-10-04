# Introduction

This is a framework and demonstration for mobile development.
Currently developing by **Xcode** and **Android Studio** are supported.

# Directory Structure

## App Projects

These are **Android Studio** and **Xcode** projects.

- app_android/
- app_ios/

## App Build Scripts

For building **Android** and **iOS** app, and placing them to *BUILD/*.

- build_android
- build_android.bat
- build_ios

## Tools

These scripts traverse headers and create new homonymic headers
which reference former to *GENERATED_HEADERS/*.
It will avoid developer adding vast header search paths tediously.

- generate_headers
- generate_headers.bat

## Portable Libraries

The corss-platform source and platform-related projects.
the source can be compiled and execute on **Android** and **iOS**.

- library_android/
- library_ios/
- library/

## Library Build Scripts

The scripts will compile portable libary, and place them to *BUILD/*.

- makelib_android
- makelib_android.bat
- makelib_ios
- makelib_ios_res

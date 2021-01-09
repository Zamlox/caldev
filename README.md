![example workflow name](https://github.com/Zamlox/caldev/workflows/CI/badge.svg)

# caldev
**C**ross-platform **A**pplication **L**ibrary for **DEV**elopment

caldev is an open source project to provide following core features for application development:
   - Graphic User Interface (GUI)
   - Network communication
   
Other features will be added later as needed.

Project is developed in Visual Studio Code using C++17 language and tries to leverage existing open source components to achieve its goal.


## Build

Build system is based on bazel (https://bazel.build/) developed by Google, which is a free software tool that allows for automation of building and testing software.
This project can be built on following platforms:
  * Windows x86 32bit/64bit
  * Linux x86 32bit/64bit
  * macOS x86 64bit
	
Available bazel targets for bulilding the library:
  * caldev32 (for 32bit)
  * caldev (for 64bit)

## How to build
Use following command lines from shell to build (command must be executed within 'src' folder).

x86 32bit Windows:
```
bazel build --config=i386_windows :caldev32
```
x86 32bit Linux:
```
bazel build --config=i386_linux :caldev32
```
x86 64bit all platforms (Windows, Linux, macOS):
```
bazel build :caldev
```


## Unit tests

Unit tests are developed using google test framework and executed on all supported platforms.
To execute unit tests run ```unittests``` binary within src/bazel-bin folder.


## Bindings

Currently bindings are developed for C++ and [Rebol2](http://www.rebol.com/docs/docs.html) but can be developed for any programming language which has support for calling functions exported by shared libraries.


## Examples
Examples can be found in ```src/examples``` folder.  
Currently only GUI demo exist and it can be built using following command line:
```
bazel buil :demo_gui
```
Binary can be found in ```src/bazel-bin``` folder.  
Rebol2 demo can be executed using [Rebol2/View](http://www.rebol.com/download-view.html) interpreter.

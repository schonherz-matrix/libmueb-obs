# matrix-obs

OBS Studio plugin for Schönherz Mátrix Streaming

## Prerequisites

Qt **5.12**(LTS) or above is recommended

**C++ 20** compatible compiler

libmueb

Build tools for Qt(platform dependent):

- **MSVC**(Desktop development with C++)/MinGW on **Windows**
- **build-essential** on **Unix/Linux**

Old Qt5Network(**5.10.1**) module for official OBS builds:

- [Windows](http://download.qt.io/online/qtsdkrepository/windows_x86/desktop/qt5_5101/qt.qt5.5101.win64_msvc2017_64/5.10.1-0-201802092252qtbase-Windows-Windows_10-MSVC2017-Windows-Windows_10-X86_64.7z)
- [Linux](http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_5101/qt.qt5.5101.gcc_64/5.10.1-0-201802092252qtbase-Linux-RHEL_7_4-GCC-Linux-RHEL_7_4-X86_64.7z)
- [MacOS](http://download.qt.io/online/qtsdkrepository/mac_x64/desktop/qt5_5101/qt.qt5.5101.clang_64/5.10.1-0-201802092250qtbase-MacOS-MacOS_10_12-Clang-MacOS-MacOS_10_12-X86_64.7z)

OBS Studio dev files

- [Install instructions](https://github.com/obsproject/obs-studio/wiki/Install-Instructions)

## How to build

set these cmake variables to the correct path:

- Qt5_DIR
- libmueb_DIR
- libobs_DIR

**Build everything in release mode**

Use Qt Creator **without shadow build**

Using command line simply run

```bash
mkdir build && cd build
cmake .. -DQt5_DIR=PATH -Dlibmueb_DIR=PATH -Dlibobs_DIR=PATH
make
```
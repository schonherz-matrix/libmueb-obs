# matrix-obs

OBS Studio plugin for Schönherz Mátrix Streaming

## Prerequisites

Qt **5.12**(LTS) or above is recommended

**C++ 20** compatible compiler

libmueb

Build tools for Qt(platform dependent):

- **MSVC**(Desktop development with C++)/MinGW on **Windows**
- **build-essential** on **Unix/Linux**

Official OBS builds with Qt version **5.10.1** is not supported!

- You should build your own OBS with Qt **5.12**(LTS) or above

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

## How to install

Put these shared libraries inside obs-plugins/64bit directory

- matrix-obs
- muebtransmitter
- Qt5Network

## Issues

When starting the output with the hotkey OBS might crash unexpectedly

When closing OBS it will print this to the debugger

```
Freeing OBS context data
output 'matrix-obs-output' destroyed
	1 output(s) were remaining
...
Number of memory leaks: 1
```

There is no **memory leak** because matrix-obs-output is automatically destroyed and currently there is no way to call [obs_output_release](https://obsproject.com/docs/reference-outputs.html?highlight=obs_output_release#c.obs_output_release) function safely.

Output is destroyed before module unload so can't do it from there.
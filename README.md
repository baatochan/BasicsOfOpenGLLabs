# Basics of OpenGL labs
Few OpenGL apps written in C++ during OpenGL course at the University (grafika komputerowa).

Author: Bartosz Rodziewicz

## Map of the repo

This repo consists of `grafika/` folder which is CLion project and single `*.cpp`
files in `/`.

To make use of `*.cpp` files take the one you want to open, change the name to `main.cpp` and paste it in `grafika/`. Then run CLion, compile and run.

## Tasks done during the course

Every single `*.cpp` file in `/` is one single task. There are two groups of those
tasks:
* `lab#-#.cpp` are tasks copy-pasted from lab task instructions,
* others are tasks that we had to do by ourselves and those were:
  * `sierpinskiCarpet.cpp` - simple app that draws Sierpinski carpet (user can
    chose number of steps and perturbation level),
  * TODO: others

## CLion Configuration

Before running those files in CLion you have to configure it and install required
plugins.
* Make sure you use CLion with MinGW.
* Download required plugins:
  * [pkg-config](http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/pkg-config_0.26-1_win32.zip)
  * [glib](http://ftp.gnome.org/pub/gnome/binaries/win32/glib/2.28/glib_2.28.8-1_win32.zip)
  * [gettext-runtime](http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/gettext-runtime_0.18.1.1-2_win32.zip)
  * [freeglut](http://files.transmissionzero.co.uk/software/development/GLUT/freeglut-MinGW-3.0.0-1.mp.zip)
* Unpack them to MinGW folder (where MinGW is installed).
* Looks like it's all you have to do.

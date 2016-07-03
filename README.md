# rFactor2TimeTrial

rFactor2TimeTrial is a Qt-based extension for rFactor2 providing Gran-Turismo-like Time Trial functionality.

Basically the code in this repository is stable, but it lacks some functionality. Check out the TODO list for details.

If you have any questions, don't hesitate to contact me under florian(at)marchal(dot)de.

Florian Marchal (flomar), June 2016

## Motivation

You might wonder why someone would try to emulate a Gran-Turismo-like Time Trial functionality in a game like rFactor2.

Well, my friends and me always had the most fun in terms of racing games when we could battle each other while sitting in the same room, and I thought rFactor2 was lacking in that department.

I admit that the whole project is sort of a hack, but where's the fun in simple things, right? I'm not 100% satisfied with the result yet, but the core functionality is there.

Feel free to fork the project, submit a pull request, complain about the bugs or simply use it for your own fun.

Enjoy!

## Overview

rFactor2TimeTrial consists of two projects: **rF2TimeTrial** and **QTimeTrial**.

rF2TimeTrial provides a DLL which is integrated into rFactor2 as a plugin, and QTimeTrial provides the corresponding user interface. Both components, the DLL and the GUI, communicate through a one-way network connection where the DLL acts as client and the GUI acts as server.

## Build Instructions

Although it might be obvious to the rFactor2 users, the whole project is a Windows-only project.

I used Qt 5.7 and MINGW to build QTimeTrial, and MS Visual Studio 2015 Community Edition to build rF2TimeTrial.

I couldn't get Qt to work with Visual Studio for the life of me, but using two different compilers doesn't do any harm: The common code (the client/server protocol) is compiler-agnostic, and the only connection between the two components is implemented through the network, therefore it doesn't even matter if you compile 32bit or 64bit executables or DLLs, respectively.

## Run Instructions

Before doing anything else, make sure you're desktop resolution is a multiple of 1920x1080, either smaller or larger, and that you run rF2 in borderless window mode. If you ignore this advice, you might see a skewed user interface or nothing at all.

First you want to start QTimeTrial since it provides the server implementation. After you can see the QTimeTrial menu bar, you can safely start rFactor2.

**WARNING**: For now, QTimeTrial needs to be started from within its base directory (the one containing the QtCreator project file), otherwise the underlying database will not be found.

**WARNING**: Sometimes the QTimeTrial application does not stay on top of all other windows like it is intended to. If that happens, there's no other option but to shut down both, the QTimeTrial and the rF2 applications and try again. Clicking the QTimeTrial menu bar while rF2 starts up seems to help, but unfortunately not always.

You know you're good to go if you can still see the QTimeTrial menu bar hovering over the rFactor2 user interface in the main menu. Then simply deselect session settings (practice, qualifying, race) and push the race button.

As soon as you're in the box (or at the monitor), click the "Drivers" button and select the desired driver. Note: **Nothing will be tracked without a valid driver.**

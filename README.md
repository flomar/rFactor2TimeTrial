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

rFactor2TimeTrial consists of two projects: *rF2TimeTrial* and *QTimeTrial*.

rF2TimeTrial provides a DLL which is integrated into rFactor2 as a plugin, and QTimeTrial provides the corresponding user interface.

Both components, the DLL and the GUI, communicate through a one-way network connection where the DLL acts as client and the GUI acts as server.

## Build Instructions

Although it might be obvious to the rFactor2 users, the whole project is a Windows-only project.

I used Qt 5.7 and MINGW to build QTimeTrial, and MS Visual Studio 2015 Community Edition to build rF2TimeTrial.

I couldn't get Qt to work with Visual Studio for the life of me, but using two different compilers doesn't do any harm: The common code (the client/server protocol) is compiler-agnostic, and the only connection between the two components is implemented through the network, therefore it doesn't even matter if you compile 32bit or 64bit executables or DLLs, respectively.

## Run Instructions

First you want to start QTimeTrial since it provides the server implementation. After you can see the QTimeTrial menu bar, you can safely start rFactor2.

As for the performance of both projects: My rig is two years old, but it was fairly powerful back then (i7, 32GB RAM, 6GB VIDEO, SSD). I'm sorry if you run into performance issues, I didn't optimize in every possible corner. The network code shouldn't be a problem though, the constant updates require something like 500 bytes every 50ms, so that's really not a concern. I'd rather worry about the QML-based interface which gets updated at the same frequency.

*WARNING*: I already mentioned this in the TODO list, but here it goes again. Sometimes the QTimeTrial application does not stay on top of all other windows like it is intended to. If that happens, there's not other option but to shut down the rF2 application and try again. Clicking the QTimeTrial menu bar while rF2 starts up seems to help, but unfortunately not always.
# rFactor2TimeTrial TODO List

This document contains the most important TODOs for the project.

## Issues

- Sometimes, and I really found no way to reproduce it reliably, the QTimeTrial application does not stay on top of all other windows, and as a result you have to quit rF2 and go back to try again.
- The "Options" widget doesn't contain any functionality so far, all I added were some items for future ideas and implementations.
- The "Drivers" widget lacks functionality, drivers cannot be created or deleted yet. For now all you can do is access the SQLITE database directly to create or remove drivers.
- QTimeTrial is optimized for 1920x1080, so if you launch rF2 in different resolutions the whole thing looks ugly as hell and doesn't serve its purpose.

## Bugs

- The QTimeTrial application crashes upon shutdown unless the code in "ApplicationGui::~ApplicationGui" is disabled. Played around with it for a while, but got tired. Doesn't matter all that much since all memory is freed right after that destructor is called anyway.
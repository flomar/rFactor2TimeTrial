# rFactor2TimeTrial TODO List

This document contains the most important TODOs for the project.

## TODOs

- Fixed the bug with the "lst", "bst", and "rec" variables, but now the "LapInformationDisplay" is bugged, it always (!) shows a personal best and an absolute best time. FIX THIS ASAP!
- Find a better solution than explicitly calling "update()" before displaying a dialog in order for the dialogs to honor the application-wide font settings.

## Issues

- Sometimes, and I really found no way to reproduce it reliably, the QTimeTrial application does not stay on top of all other windows, and as a result you have to quit rF2 and go back to try again.
- The "Drivers" widget provides an "Edit Driver" button, but for now there's no functionality behind it.
- QTimeTrial is optimized for resolutions in multiples of 1920x1080, so if you're working with a different resolution both the menu and the HUD may look skewed.
- The "horizontal header" in the table widget of the "Records" widget doesn't apply its font type properly (it should look identical to all other elements).

## Bugs

- The QTimeTrial application crashes upon shutdown unless the code in "ApplicationGui::~ApplicationGui" is disabled. Played around with it for a while, but got tired. Doesn't matter all that much since all memory is freed right after that destructor is called anyway.

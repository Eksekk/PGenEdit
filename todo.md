# Testing
* Redo Asserter class to use own log sink and log messages instead of converting them to text and concatenating, reason: ability to click on each error in error message rather than big block of text
* wxChoice doesn't react to mouse clicks during testing

# Misc
* Very long loading time for editor windows

# GUI
* add item dialog is broken when inserting items dynamically in subclasses of main class
* Tooltips don't show - in wxDialog they do
* inventory control - handle item position

# Code
* Auto convert structure parameters in hookFunction and hookReplaceCall to their addresses
* Json persisting methods boolean return values should indicate actual error in all cases, not empty data or error
* Fetching item images is broken - weird colors

# Low level
* automatically store hook restore data to abstract unhooking (see hookRestoreDataMap variable)
* redoing asm compiling functions to two-pass system (compile, get size, alloc memory, compile again with origin at this memory), allowing to have "absolute" keyword as in MMExt

# Design
* simple "randomize item" dialog, where you would input item type, treasure level etc. and call vanilla function
* use event loop when opening main window to make editor/generator modal for easier programming and more intuitive design
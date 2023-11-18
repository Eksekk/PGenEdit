# Testing
* Redo Asserter class to use own log sink and log messages instead of converting them to text and concatenating, reason: ability to click on each error in error message rather than big block of text
* wxChoice doesn't react to mouse clicks during testing

# Misc
* Very long loading time for editor windows
* Exiting via alt-F4 while editor window is open (running event loop) crashes the game

# GUI
* add item dialog is broken when inserting items dynamically in subclasses of main class
* Tooltips don't show - in wxDialog they do
* inventory control - handle item position

# Code
* Auto convert structure parameters in hookFunction and hookReplaceCall to their addresses
* Json persisting methods boolean return values should indicate actual error in all cases, not empty data or error
* Fetching item images is broken - weird colors
* big one: should accessor "generic for" functions providing index to callback, provide the exact index that was used as first or 0-based index for iteration? Both have pros and cons:
    * first option allows you to index a table with exact provided index if you needed to, but doesn't let you know which iteration of the loop is running;
    * while second is inverse - you don't know how to index real data table, but know which iteration of the loop is currently running.
    * I think the first one is better, because you can always know current iteration by capturing counter variable, while you might not know the exact index that is used as first

# Low level
* automatically store hook restore data to abstract unhooking (see hookRestoreDataMap variable)
* redoing asm compiling functions to two-pass system (compile, get size, alloc memory, compile again with origin at this memory), allowing to have "absolute" keyword as in MMExt

# Design
* simple "randomize item" dialog, where you would input item type, treasure level etc. and call vanilla function
* use event loop when opening main window to make editor/generator modal for easier programming and more intuitive design
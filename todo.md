# Testing
* Redo Asserter class to use own log sink and log messages instead of converting them to text and concatenating, reason: ability to click on each error in error message rather than big block of text
* wxChoice doesn't react to mouse clicks during testing

# Misc
* Tooltips don't show
* Very long loading time for editor windows

# Code
* Auto convert structure parameters in hookFunction and hookReplaceCall to their addresses
* Json persisting methods boolean return values should indicate actual error in all cases, not empty data or error

# Low level
* automatically store hook restore data to abstract unhooking (see hookRestoreDataMap variable)
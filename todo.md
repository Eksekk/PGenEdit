# Testing
* Redo Asserter class to use own log sink and log messages instead of converting them to text and concatenating, reason: ability to click on each error in error message rather than big block of text
* When testing hook placing and size, don't use direct copy of code, but pass local vector so function stores code there? Would test storing as well
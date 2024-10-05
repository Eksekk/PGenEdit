# Testing
- Redo Asserter class to use own log sink and log messages instead of converting them to text and concatenating, reason: ability to click on each error in error message rather than big block of text
- more test functions in Asserter like assertTrue, assertFalse, assertAnyThrow (from googletest) etc.
- project parts requiring tests:
    - luaWrapper (in particular, vararg call functions)
    - LuaTypeInCpp/LuaValue
    - struct accessors
    - some low level functions
    - GUI classes
    - all classes in game data (PlayerSkill, PlayerStat etc.)
    - lua event system
    - debug console
    - all classes and most functions in utility!!! This is the basic stuff and should work flawlessly
    - GameTime

# Crucial functionality
- implement operating on all game maps in memory, not just current one

# Misc

# GUI

# Required improvements to avoid bugs before they happen
- somehow make a common class for all accessors which contains pointer to operate on (or use some template magic), then create RAII class which will set data pointer when created, and restore it when destroyed, so that any forPlayer(), forChest() etc. calls during the function or functions it calls won't have effect on player pointer when function is exited, and functions called by main function don't change the pointer for main function (currently it is assumed that setting forPlayer() etc. once at the beginning of the function will work, but it may not at any code change)

# Code
- Auto convert structure parameters in hookFunction and hookReplaceCall to their addresses
- Json persisting methods boolean return values should indicate actual error in all cases, not empty data or error
- big one: should accessor "generic for" functions providing index to callback, provide the exact index that was used as first or 0-based index for iteration? Both have pros and cons:
    - first option allows you to index a table with exact provided index if you needed to, but doesn't let you know which iteration of the loop is running;
    - while second is inverse - you don't know how to index real data table, but know which iteration of the loop is currently running.
    - I think the first one is better, because you can always know current iteration by capturing counter variable, while you might not know the exact index that is used as first
- move most lua-related code to "lua" namespace (I tried to do it the easy way, but didn't find anything else than Resharper's "move to namespace" refactoring, and I don't have Resharper)
- for all game data classes like PlayerSkill, PlayerStat etc., make them immutable as much as possible and initialize them in constructor, so there is no danger of incomplete initialization or changing them

# Low level
- automatically store hook restore data to abstract unhooking (see hookRestoreDataMap variable)
- redoing asm compiling functions to two-pass system (compile, get size, alloc memory, compile again with origin at this memory), allowing to have "absolute" keyword as in MMExt
- hook Windows "Heaven's Gate" to allow running 64-bit code from 32-bit process (see https://github.com/dadas190/Heavens-Gate-2.0); no real use case for this, but it would be cool to have

# Design
- simple "randomize item" dialog, where you would input item type, treasure level etc. and call vanilla function
- use event loop when opening main window to make editor/generator modal for easier programming and more intuitive design

# Lua
- big one: create a system for allowing getEventActivator for lua events with arbitrary number of arguments, using vector of LuaTypeInCpp as parameter and return value (for semantics as in lua, make so that lua events modifying tables passed by parameter in cpp, still modify the original table received)
- ANOTHER BIG ONE: since with LuaJIT definitions we can tinker with lua_State* we are passed, we can get global state from it, then explicitly create new thread for pgenedit and use this as our "global" state to not cause problems to Grayface's hook function state we are initially passed; ALSO: I now know why Grayface used his lua_State as registry key - 1) because it is unique, and more importantly, 2) because it probably causes it to not be garbage collected and thus state remains valid
- add all functions to lua wrapper, add method to pcall, using LuaTypeInCpp as return values and args
- make debug console fully functional (GUI class and ability to execute lua code)
- create a function, which calls a C++ std::function for each key/value pair in a lua table (can be also from stack) - some kind of iterator for lua tables
- for extra fun, do the above using C++ coroutines to implement a kind of "generator"
- better error handling in lua wrapper
- create lua scripts for getting all data from lua (for example, spell data is missing)
- overload appropriate LuaWrapper functions to accept LuaTypeInCpp as arguments
- Create "LuaFunction" class, using templates/reflection to call with variable arguments and return values (here is where RTTR and ability to use variable amount of arguments for parameters or return values, when interacting with lua, would be useful). Implementation tip - (https://stackoverflow.com/questions/16868129/how-to-implement-a-variadic-lua-function-in-c). Second implementation tip - store a real function somewhere in lua in a table, which should not be easily accessible to other code (registry subtable?), and instead of storing a function inside this class, store reference to this table (path for example).
- implement containers for debug api system
- complete fixing bugs for debug api system and add container tests/more static property tests
- go through all code and make sure stack is properly restored in case of errors
- finish LuaFunction class, add LuaUserdata and LuaThread classes

# Uncategorized
- better callbacks: add way to remove them, using probably some kind of tokenindicating if it was correct type
- test bytecode hooks (use asm tests for this, grab generated bytecode and compare it with expected from asm test)
- change all appropriate hook functions to call checkOverlap() before doing anything
- test codeMemoryAlloc family of functions
- create all struct accessors and their methods (generic for)
- use ArrayData in all places where it is appropriate (mainly in struct accessor methods)
- somehow handle differences in structs from elemental mod (and other mods, but this one has most)
- test all methods in wrappers for game data (PlayerSkill, PlayerStat etc.) and add missing ones
- use hook functions in real scenarios?
- analyze base classes for GUI classes (like PlayerPanelBase), to see, if their interface should be changed
- handle json serialization and deserialization for all classes (using RTTR when appropriate?)
- create some tests for the above
- test GameTime and TimeChooserCtrl classes
- document all classes and methods (using doxygen)
- find a way to make all classes in the project have the same interface for serialization and deserialization
- generate RTTR data for all classes
- put most stuff into namespaces (project is getting very big)

# Big ones
- use boost.PP for accessor structs' get/set methods
- extract code not depending much on generator/editor/game data itself (for example structs, utility functions, asserter, profiler etc.) to separate project, which would allow it to be easily used in other projects (like GUI EVT code editor)
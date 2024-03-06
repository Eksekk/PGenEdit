# Might and magic party generator and editor

Hello! This is my project to enable editing game state (player stats etc.), as well as generating completely new party
with wide range of settable settings. Intended use is:
* for generator: gameplay randomization, challenge runs, "just for fun" usages
* for editor: fine-tuning party statistics, correcting bugs, making yourself a very specific party for some kinds of challenge
runs, as well as making yourself "full peasant-like" (stats/skills at 0, no items etc.), or simply becoming as OP as game allows
:)

But of course you can use it any way you wish.

Currently only editor is developed (I started with generator, but saw most users want editor), and only for MM7.
I however plan to include not only MM6/7/8, but also mods like TCC, Merge or rev4 mod. I am designing/writing the code with
all-games-compatibility in mind as well as to adapt easily to most mods which change game mechanics like skills/spells/classes etc.
In addition, I plan to include some options requiring so-called "hooks" (like infinite HP/SP or 3 times lower global recovery).

The applications will have full graphical user interface (thanks to wxWidgets library!), so editing game should be as easy
as possible. That in fact is my main goal. You can do much more stuff with Lua if you know it, but having user interface for
most common tasks will be very beneficial.

For generator I plan to also include Lua api (the program is a DLL and so integrates perfectly with the game, including
MMExt's lua environment) to allow using it programmatically, and possibly randomizing randomization parameters :) And you'll be
able to edit some stuff in lua files, mainly to change the characteristics of specific
gameplay elements (say, how appropriate it is for knight to have high bodybuilding, or how valuable is Splitter in terms of
"item points").

Hope you will find the stuff useful once it is released!!

Eksekk
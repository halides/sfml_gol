# sfml_gol

Done on Ubuntu 20.04.1 Focal Fossa. You need libsfml-dev:

`sudo apt-get install libsfml-dev`

I did not try to re-invent the wheel: I looked at 3 different Game of Lifes implemented in C++, all of which were quite "C-style". I almost went with SDL2 but once I got a look at an SFML-project it seemed a lot cleaner to implement a GUI with it, at least at this scale.

I'll try to commit often and add some tags when those make sense so you can get a feel of how I build things.

v0.1:
A naive, C-style solution that gets 0 points for design, structure, language features, error checking, comments, testability or documentation. I however think the implementation is clear and usable. There's a bug though but I need to run off to work. About 3 hours of development time here.

v0.2:
Overhauled (most of) business logic to a class. However stepping to the next generation is still a stub. About 4.5 hours development in total here.

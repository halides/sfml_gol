# sfml_gol

Done on Ubuntu 20.04.1 Focal Fossa. You need libsfml-dev:

`sudo apt-get install libsfml-dev`

I did not try to re-invent the wheel: I looked at 3 different Game of Lifes implemented in C++, all of which were quite "C-style". I almost went with SDL2 but once I got a look at an SFML-project it seemed a lot cleaner to implement a GUI with it, at least at this scale. In the end, I really enjoyed SFML, propably the cleanest windowing-library I've worked with this far. I was planning to do a more optimized version (https://www.youtube.com/watch?v=ndAfWKmKF34) but in the end for me it was enought just to get it working right.

GoL is defined to be in and "infinite grid" which 

v0.1:
A naive, C-style solution that gets 0 points for design, structure, language features, error checking, comments, testability or documentation. I however think the implementation is clear and usable. There's a bug though but I need to run off to work. About 3 hours of development time here.

v0.2:
Overhauled (most of) business logic to a class. However stepping to the next generation is still a stub. About 4.5 hours development in total here.

v0.3:
Stepping works and decided to go with wrapping instead of an infinite grid. "Feature complete" from my point of view, needs refactoring and documentation. About 6 hours of development 'cos wrapping was such a mess of small bugs to get working :-p.

v0.9:
Refactoring, comments, documentation.

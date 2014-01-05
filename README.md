# sdl2-platformer

A simple platformer game attempting to test features of both
*SDL 2.0* and *C++11*.

The idea was to make a "template" project on which future SDL2
games could be built. The source code is _very_ well documented
(using Doxygen markup) and I encourage you to learn from it.
Also, _C++11 features, mate_!

This game is built on top of a simple and extensible Game Engine
I've been developing on the past year. It has a lot of helper
classes that may be useful to anyone. Do check them and the
`config.ini` file!

## Controls

| Key                 | Action                      |
| ------------------- | --------------------------- |
| Arrow Keys / `wasd` | Control the player and jump |
| `q` / ESC           | Quit the game               |

## Usage

That would build and run the game:

    $ make
	$ ./platformer

## Dependencies

You need to have *SDL 2.0* and it's child libraries
(*SDL GFX*, *SDL Image*, *SDL Mixer*, and *SDL TTF*).

In Arch Linux, the following should be enough:

    $ pacman -S sdl2 sdl2_gfx sdl2_image sdl2_mixer sdl2_ttf

Also, your C++ compiler should support *C++11*.
If something bad happens during compilation, try switching
the flag `-std=c++0x` to `-std=c++11`.

## Credits

Programmed by Alexandre Dantas.

* Mail: `eu @ alexdantas.net`
* Homepage: http://alexdantas.net

## License

Copyright (C) 2013  Alexandre Dantas

This program is free software: you can redistribute it and/or
modify it under the terms of the _GNU General Public License_
as published by the _Free Software Foundation_, either
*version 3* of the License, *or any later version*.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.
If not, see <http://www.gnu.org/licenses/>.


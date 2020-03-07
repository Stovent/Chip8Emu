# Chip8Emu

Chip8Emu is a simple CHIP-8 emulator with build possible on Windows and Linux.

## Controls

The controls are mapped on the numpad:

regular keyboard (K = enter key)

​       /	*	-

7	8	9	+

4	5	6	+

1	2	3	K

​      0	 .	K

Cosmac VIP keyboard

1	2	3	C

4	5	6	D

7	8	9	E

A	0	B	F



lines 7 8 9 and 1 2 3 are inverted to match the original keyboard.

A B C D E F are respectly mapped on . / * - + F

## Shortcuts and UI

A : pause/unpause emulation

E : execute a single instruction

Menu shortcuts are indicated on the right of the corresponding menu.

## Compiling Instructions

Chip8Emu depends on wxWidgets.

#### Windows

Use CMake-GUI

#### Linux

package dependency: `libwxgtk3.0-dev`

Install the dependency, then open a terminal in the root directory of the git and type:

```sh
cmake .
make -j$(nproc --all)
```
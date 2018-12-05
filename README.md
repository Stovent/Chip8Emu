# Chip8Emu
a simple Chip8 emulator

# Controls
The controls are mapped on the numpad : \
regular keyboard (E = enter)	Cosmac VIP keyboard \
	/	*	-					1	2	3	C \
7	8	9	+					4	5	6	D \
4	5	6	+					7	8	9	E \
1	2	3	E					A	0	B	F \
	0	.	E
	
lines 7	8 9 and 1 2 3 are inverted to match the original keyboard. \
A B C D E F are respectly mapped on / * - + E . \

# Shortcuts and UI
A : pause/unpause emulation \
E : execute a single instruction \

Reboot Core : Reset the internal state of the CPU \
Export Memory : export the complete memory to a file "memory.bin" \


# Compiling Intructions
Open the Makefile and changes a few variables to match your installation of wxWidgets (3.0.4) \
- wxLibPath : path to the libs (wxWidgets\lib\gcc_lib) \
- wxIPath : Include path of wxWidgets (wxWidgets\include) \
- wxIMSWU : path to mswu libs (wxWidgets\lib\gcc_lib\mswu) \

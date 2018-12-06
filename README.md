# Controls
The controls are mapped on the numpad : \
regular keyboard (K = enter key) \
&nbsp; &nbsp; /	*	- \
7	8	9	+ \
4	5	6	+ \
1	2	3	K \
&nbsp; &nbsp; 0	.	K
	
Cosmac VIP keyboard \
1	2	3	C \
4	5	6	D \
7	8	9	E \
A	0	B	F
	
lines 7	8 9 and 1 2 3 are inverted to match the original keyboard. \
A B C D E F are respectly mapped on / * - + K . 

# Shortcuts and UI
A : pause/unpause emulation \
E : execute a single instruction \
Menu shortcuts are indicated on the right of the corresponding menu

Reboot Core : Reset the internal state of the CPU \
Export Memory : export the complete memory to a file "memory.bin" 


# Compiling Intructions
Open the Makefile and changes a few variables to match your installation of wxWidgets (3.0.4) \
- wxLibPath : path to the libs (~wxWidgets\lib\gcc_lib)
- wxIPath : Include path of wxWidgets (~wxWidgets\include)
- wxIMSWU : path to mswu libs (~wxWidgets\lib\gcc_lib\mswu)

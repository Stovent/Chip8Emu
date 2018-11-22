CXX = g++
CXXFLAGS = -Wall -std=c++11 -pipe -mthreads
linkerFLAGS = -s -static-libstdc++ -static-libgcc -static -mthreads

defines = -D__GNUWIN32__ -D__WXMSW__ -DWXUSINGDLL -DwxUSE_UNICODE
wxLib = -lwxmsw30u_core -lwxbase30u -lwxpng -lwxzlib -lole32 -luuid -loleaut32 -lwinspool -lcomctl32 -mwindows

wxLibPath = C:\wxWidgets-3.0.4\lib\gcc_lib
wxIPath = C:\wxWidgets-3.0.4\include
wxIMSWU = C:\wxWidgets-3.0.4\lib\gcc_lib\mswu


obj = bin/obj/Main.o bin/obj/Chip8Emu.o bin/obj/MainFrame.o bin/obj/GamePanel.o bin/obj/Chip8.o


Chip8Emu :
	$(CXX) $(CXXFLAGS) -O3 -I$(wxIPath) -I$(wxIMSWU) $(defines) $(wxLib) -c src/Core/Chip8.cpp -o bin/obj/Chip8.o
	$(CXX) $(CXXFLAGS) -O3 -I$(wxIPath) -I$(wxIMSWU) $(defines) $(wxLib) -c src/GUI/GamePanel.cpp -o bin/obj/GamePanel.o
	$(CXX) $(CXXFLAGS) -O3 -I$(wxIPath) -I$(wxIMSWU) $(defines) $(wxLib) -c src/GUI/MainFrame.cpp -o bin/obj/MainFrame.o
	$(CXX) $(CXXFLAGS) -O3 -I$(wxIPath) -I$(wxIMSWU) $(defines) $(wxLib) -c src/Chip8Emu.cpp -o bin/obj/Chip8Emu.o
	$(CXX) $(CXXFLAGS) -O3 -I$(wxIPath) -I$(wxIMSWU) $(defines) $(wxLib) -c src/Main.cpp -o bin/obj/Main.o
	$(CXX) -L$(wxLibPath) -o bin/Chip8Emu.exe $(obj) $(linkerFLAGS) $(wxLib)

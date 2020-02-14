cmake_minimum_required(VERSION 3.0)

project(Chip8Emu)

set(SRC
		src/Chip8/Chip8.cpp
		src/Chip8/Interpreter.cpp
		src/GUI/MainFrame.cpp
		src/GUI/GamePanel.cpp
		src/Chip8Emu.cpp
		src/main.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(UNIX)
	set(CMAKE_GENERATOR "Unix Makefiles")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

add_executable(Chip8Emu ${SRC})

find_package(wxWidgets COMPONENTS adv core base REQUIRED)

if(wxWidgets_FOUND)
	include("${wxWidgets_USE_FILE}")
	target_compile_features(Chip8Emu PUBLIC cxx_std_11)
	target_include_directories(Chip8Emu PUBLIC ${wxWidgets_INCLUDE_DIRS})
	target_link_libraries(Chip8Emu ${wxWidgets_LIBRARIES})
	set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "-s -O3")
else()
	message(FATAL_ERROR "wxWidgets not found")
endif()

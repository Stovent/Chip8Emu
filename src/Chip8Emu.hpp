#ifndef CHIP8EMU_HPP
#define CHIP8EMU_HPP

class Chip8Emu;

#include <thread>

#include <wx/app.h>

#include "Chip8/Chip8.hpp"
#include "GUI/MainFrame.hpp"

class Chip8Emu : public wxApp
{
    std::thread* gameThread;

public:
    Chip8* chip8;
    MainFrame* mainFrame;

    virtual bool OnInit();
    virtual int OnExit();

    void StartGameThread();
    void StopGameThread();
};

#endif // CHIP8EMU_HPP

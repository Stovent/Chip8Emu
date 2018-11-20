#ifndef CHIP8EMU_HPP
#define CHIP8EMU_HPP

class Chip8Emu;

#include <thread>

#include <wx/wx.h>

#include "Core/Chip8.hpp"
#include "GUI/MainFrame.hpp"

void runGameThread(Chip8Emu* app);

class Chip8Emu : public wxApp
{
public:
    std::thread* gameThread = nullptr;

    Chip8* cpu;

    MainFrame* mainFrame;

    virtual bool OnInit();
    void StartGameThread();
    void StopGameThread();
};

DECLARE_APP(Chip8Emu);

#endif // CHIP8EMU_HPP

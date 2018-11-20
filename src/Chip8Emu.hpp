#ifndef CHIP8EMU_HPP
#define CHIP8EMU_HPP

class Chip8Emu;

#include <wx/wx.h>

#include "Core/Chip8.hpp"
#include "GUI/MainFrame.hpp"

class Chip8Emu : public wxApp
{
public:
    Chip8* cpu;

    MainFrame* mainFrame;

    virtual bool OnInit();
};

DECLARE_APP(Chip8Emu);

#endif // CHIP8EMU_HPP

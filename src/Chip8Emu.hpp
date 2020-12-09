#ifndef CHIP8EMU_HPP
#define CHIP8EMU_HPP

class Chip8Emu;

#include <wx/app.h>

#include "Chip8/Chip8.hpp"
#include "GUI/MainFrame.hpp"

class Chip8Emu : public wxApp
{
public:
    Chip8Emu();

    Chip8 chip8;
    MainFrame* mainFrame;

    virtual bool OnInit() override;
    virtual int OnExit() override;
};

#endif // CHIP8EMU_HPP

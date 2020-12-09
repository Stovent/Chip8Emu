#ifndef CHIP8EMU_HPP
#define CHIP8EMU_HPP

class Chip8Emu;

#include "Chip8/Chip8.hpp"
#include "GUI/MainFrame.hpp"

#include <wx/app.h>

class Chip8Emu : public wxApp
{
public:
    Chip8Emu();

    Chip8 chip8;

    virtual bool OnInit() override;
    virtual int OnExit() override;
};

#endif // CHIP8EMU_HPP

#ifndef CHIP8EMU_HPP
#define CHIP8EMU_HPP

class Chip8Emu;

#include "Chip8/Chip8.hpp"
#include "GUI/MainFrame.hpp"

#include <wx/app.h>

#define CHIP8_DEFAULT_SPEED (500)
#define CHIP8_MIN_SPEED (1)
#define CHIP8_MAX_SPEED (2000)

class Chip8Emu : public wxApp
{
public:
    Chip8Emu();

    Chip8 chip8;

    virtual bool OnInit() override;
    virtual int OnExit() override;
};

#endif // CHIP8EMU_HPP

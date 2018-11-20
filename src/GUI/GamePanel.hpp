#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

class GamePanel;

#include <wx/panel.h>
#include <wx/dcclient.h>

#include "MainFrame.hpp"
#include "../Chip8Emu.hpp"

class GamePanel : public wxPanel
{
    Chip8Emu* app;
    uint8_t screen[32][64];
    uint8_t scale;

public:
    GamePanel(Chip8Emu* app, MainFrame* parent);
    void Draw(uint8_t x, uint8_t y, uint8_t n);
    void ClearScreen();
    void Update();
};
#endif // GAMEPANEL_HPP

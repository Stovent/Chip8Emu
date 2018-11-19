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
    MainFrame* parent;
    uint8_t screen[32][64];

public:
    GamePanel(Chip8Emu* app, MainFrame* parent);
    void Update();
};
#endif // GAMEPANEL_HPP

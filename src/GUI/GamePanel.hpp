#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

class GamePanel;

#include <wx/panel.h>

#include "MainFrame.hpp"
#include "../Chip8Emu.hpp"

class GamePanel : public wxPanel
{
    Chip8Emu* app;
    MainFrame* parent;

public:
    GamePanel(Chip8Emu* app, MainFrame* parent);
};
#endif // GAMEPANEL_HPP

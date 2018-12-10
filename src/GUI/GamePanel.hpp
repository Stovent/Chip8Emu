#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

class GamePanel;

#include <wx/panel.h>
#include <wx/timer.h>
#include <wx/dcclient.h>

#include "MainFrame.hpp"
#include "../Chip8Emu.hpp"

#define WIDTH 64
#define HEIGHT 32

class GamePanel : public wxPanel
{
    unsigned char screen[WIDTH*HEIGHT*3];

public:
    Chip8Emu* app;

    GamePanel(Chip8Emu* app, MainFrame* parent);
    ~GamePanel();
    void Draw(uint8_t x, uint8_t y, uint8_t n);
    void ClearScreen();
    void SetRandom();
    void RefreshScreen();

    void OnWaitEvent(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnKeyDown(wxKeyEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum
{
    idOnTimer = wxID_LAST,
};

#endif // GAMEPANEL_HPP

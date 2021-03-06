#ifndef GAMEPANEL_HPP
#define GAMEPANEL_HPP

class GamePanel;

#include "MainFrame.hpp"
#include "../Chip8/Chip8.hpp"

#include <wx/dcclient.h>
#include <wx/panel.h>
#include <wx/timer.h>

class GamePanel : public wxPanel
{
    Chip8& chip8;
    MainFrame* mainFrame;
    wxTimer timer;
    wxImage screen;

public:
    GamePanel(MainFrame* parent, Chip8& cpu);

    void DrawScreen(wxDC& dc);
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnTimer(wxTimerEvent&);
    void OnPaintEvent(wxPaintEvent&);

    wxDECLARE_EVENT_TABLE();
};

#endif // GAMEPANEL_HPP

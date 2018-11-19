#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

class MainFrame;

#include <wx/frame.h>

#include "../Chip8Emu.hpp"
#include "GamePanel.hpp"

class MainFrame : public wxFrame
{
    Chip8Emu* app;

public:
    GamePanel* gamePanel;

    MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~MainFrame();

    void OnOpenROM(wxCommandEvent& event);
    void OnCloseROM(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum
{
    idOnOpenROM = wxID_HIGHEST + 1,
    idOnCloseROM,
    idOnExit,
};

#endif // MAINFRAME_HPP

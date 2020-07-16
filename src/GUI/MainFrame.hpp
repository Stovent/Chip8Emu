#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

class MainFrame;

#include <wx/frame.h>

#include "GamePanel.hpp"
#include "../Chip8Emu.hpp"

enum
{
    IDOnOpenROM = wxID_HIGHEST + 1,
    IDOnCloseROM,
    IDOnPause,
    IDOnQuit,
    IDOnTimer,
};

class MainFrame : public wxFrame
{
public:
    Chip8Emu* chip8Emu;
    GamePanel* gamePanel;
    wxMenuItem* pauseMenuItem;

    MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

    void OnOpenROM(wxCommandEvent&);
    void OnCloseROM(wxCommandEvent&);
    void OnPause(wxCommandEvent&);
    void OnQuit(wxCommandEvent&);

    void TooglePause();

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINFRAME_HPP

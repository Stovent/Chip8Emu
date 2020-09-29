#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

class MainFrame;

#include "GamePanel.hpp"
#include "../Chip8Emu.hpp"
#include "MemoryList.hpp"

#include <wx/frame.h>
#include <wx/aui/framemanager.h>

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
    void CreatePanels();
    void CreateMenuBar();

public:
    Chip8Emu* chip8Emu;
    GamePanel* gamePanel;
    wxMenuItem* pauseMenuItem;
    MemoryList* memoryViewer;
    wxListCtrl* chip8Status;
    wxAuiManager manager;

    MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~MainFrame();

    void OnOpenROM(wxCommandEvent&);
    void OnCloseROM(wxCommandEvent&);
    void OnPause(wxCommandEvent&);
    void OnQuit(wxCommandEvent&);

    void TooglePause();
    void RefreshListCtrl();

    wxDECLARE_EVENT_TABLE();
};

#endif // MAINFRAME_HPP

#include "MainFrame.hpp"

#include <wx/sizer.h>
#include <wx/menu.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(idOnOpenROM, MainFrame::OnOpenROM)
    EVT_MENU(idOnCloseROM, MainFrame::OnCloseROM)
    EVT_MENU(idOnExit, MainFrame::OnExit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    this->app = app;
    gamePanel = new GamePanel(app, this);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(gamePanel, 1, wxEXPAND);
    SetSizer(sizer);

    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(idOnOpenROM, "Open ROM\t Ctrl+O");
    fileMenu->Append(idOnCloseROM, "Close ROM");
    fileMenu->Append(idOnExit, "Quit\t Alt+f4");

    wxMenuBar* bar = new wxMenuBar();
    bar->Append(fileMenu, "File");

    SetMenuBar(bar);
    CreateStatusBar();
    SetAutoLayout(true);
    Show();
}

MainFrame::~MainFrame()
{
    delete gamePanel;
}

void MainFrame::OnOpenROM(wxCommandEvent& event)
{
    app->cpu->OpenROM("ROM/MAZE.ch8");
    app->StartGameThread();
}

void MainFrame::OnCloseROM(wxCommandEvent& event)
{
    app->cpu->CloseROM();
    app->StopGameThread();
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

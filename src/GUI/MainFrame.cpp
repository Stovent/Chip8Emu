#include "MainFrame.hpp"

MainFrame::MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    this->app = app;
    gamePanel = new GamePanel(app, this);

    CreateStatusBar();
}

MainFrame::~MainFrame()
{
    delete gamePanel;
}

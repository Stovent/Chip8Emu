#include "MainFrame.hpp"

#include <wx/sizer.h>
#include <wx/menu.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(idOnOpenROM, MainFrame::OnOpenROM)
    EVT_MENU(idOnReloadROM, MainFrame::OnReloadROM)
    EVT_MENU(idOnCloseROM, MainFrame::OnCloseROM)
    EVT_MENU(idOnExit, MainFrame::OnExit)
    EVT_MENU(idOnPause, MainFrame::OnPause)
    EVT_MENU(idOnRebootCore, MainFrame::OnRebootCore)
    EVT_MENU(idOnExportMemory, MainFrame::OnExportMemory)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    this->app = app;
    gamePanel = new GamePanel(app, this);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(gamePanel, 1, wxEXPAND);
    SetSizer(sizer);

    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(idOnOpenROM, "Open ROM\tCtrl+O");
    fileMenu->Append(idOnReloadROM, "Reload ROM\tCtrl+R");
    fileMenu->Append(idOnCloseROM, "Close ROM\tCtrl+Q");
    fileMenu->Append(idOnExit, "Quit\tAlt+f4");

    wxMenu* emuMenu = new wxMenu;
    pause = emuMenu->AppendCheckItem(idOnPause, "Pause");
    emuMenu->AppendSeparator();
    emuMenu->Append(idOnRebootCore, "Reboot Core\tCtrl+B");
    emuMenu->Append(idOnExportMemory, "Export Memory\tCtrl+M");

    wxMenuBar* bar = new wxMenuBar();
    bar->Append(fileMenu, "File");
    bar->Append(emuMenu, "Emulation");

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
    wxFileDialog openFileDialog(this, _("Open ROM"), "", "", "Chip 8 ROMs (*.ch8)|*.ch8", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    if(app->cpu->OpenROM(openFileDialog.GetPath().ToStdString().data()))
        app->StartGameThread();
    else
        wxMessageBox("Could not open ROM!");
}

void MainFrame::OnReloadROM(wxCommandEvent& event)
{
    app->cpu->Reset();
}

void MainFrame::OnCloseROM(wxCommandEvent& event)
{
    app->cpu->CloseROM();
    app->StopGameThread();
    gamePanel->ClearScreen();
    gamePanel->RefreshScreen();
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainFrame::OnPause(wxCommandEvent& event)
{
    OnPause();
}

void MainFrame::OnPause()
{
    if(pause->IsChecked())
        app->StopGameThread();
    else
        app->StartGameThread();
}

void MainFrame::OnRebootCore(wxCommandEvent& event)
{
    app->cpu->Init();
}

void MainFrame::OnExportMemory(wxCommandEvent& event)
{
    app->cpu->ExportMemory();
}

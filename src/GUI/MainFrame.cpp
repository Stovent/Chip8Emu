#include "MainFrame.hpp"

#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/msgdlg.h>
#include <wx/filedlg.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(IDOnOpenROM,  MainFrame::OnOpenROM)
    EVT_MENU(IDOnCloseROM, MainFrame::OnCloseROM)
    EVT_MENU(IDOnPause,    MainFrame::OnPause)
    EVT_MENU(IDOnQuit,     MainFrame::OnQuit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    chip8Emu = app;
    gamePanel = new GamePanel(this, chip8Emu->chip8);

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(gamePanel, 1, wxEXPAND);
    SetSizer(sizer);

    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(IDOnOpenROM, "Open ROM\tCtrl+O");
    fileMenu->Append(IDOnCloseROM, "Close ROM\tCtrl+C");
    fileMenu->Append(IDOnQuit, "Quit\tAlt+f4");

    wxMenu* emulationMenu = new wxMenu();
    pauseMenuItem = emulationMenu->AppendCheckItem(IDOnPause, "Pause");

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "File");
    menuBar->Append(emulationMenu, "Emulation");

    SetMenuBar(menuBar);
    Show();
}

void MainFrame::OnOpenROM(wxCommandEvent&)
{
    wxFileDialog openFileDialog(this, _("Open ROM"), "", "", "Chip 8 ROMs (*.ch8)|*.ch8", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    if(chip8Emu->chip8->OpenROM(openFileDialog.GetPath().ToStdString()))
    {
        if(!pauseMenuItem->IsChecked())
            chip8Emu->StartGameThread();
    }
    else
        wxMessageBox("Could not open ROM!");
}

void MainFrame::OnCloseROM(wxCommandEvent&)
{
    chip8Emu->chip8->CloseROM();
}

void MainFrame::OnPause(wxCommandEvent&)
{
    TooglePause();
}

void MainFrame::OnQuit(wxCommandEvent&)
{
    Close(true);
}

void MainFrame::TooglePause()
{
    if(chip8Emu->chip8->romOpened)
    {
        if(chip8Emu->chip8->IsRunning())
        {
            chip8Emu->StopGameThread();
            pauseMenuItem->Check();
        }
        else
        {
            chip8Emu->StartGameThread();
            pauseMenuItem->Check(false);
        }
    }
}

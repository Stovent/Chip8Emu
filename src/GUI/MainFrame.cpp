#include "MainFrame.hpp"

#include <wx/filedlg.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(IDOnOpenROM,  MainFrame::OnOpenROM)
    EVT_MENU(IDOnCloseROM, MainFrame::OnCloseROM)
    EVT_MENU(IDOnPause,    MainFrame::OnPause)
    EVT_MENU(IDOnQuit,     MainFrame::OnQuit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(Chip8Emu* app, const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size), manager(this)
{
    chip8Emu = app;
    memoryViewer = new MemoryList(this, chip8Emu->chip8->GetMemory());
    chip8Status = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    gamePanel = new GamePanel(this, chip8Emu->chip8);

    wxListItem regCol;
    regCol.SetId(0);
    regCol.SetText("Register");
    regCol.SetWidth(70);
    chip8Status->InsertColumn(0, regCol);

    wxListItem valueCol;
    valueCol.SetId(1);
    valueCol.SetText("Value");
    valueCol.SetWidth(60);
    chip8Status->InsertColumn(1, valueCol);

    wxListItem item;
    item.SetId(0);
    item.SetText("delay");
    chip8Status->InsertItem(item);

    item.SetId(1);
    item.SetText("sound");
    chip8Status->InsertItem(item);

    item.SetId(2);
    item.SetText("PC");
    chip8Status->InsertItem(item);

    item.SetId(3);
    item.SetText("I");
    chip8Status->InsertItem(item);

    item.SetId(4);
    item.SetText("SP");
    chip8Status->InsertItem(item);

    RefreshListCtrl();

    manager.AddPane(chip8Status, wxBOTTOM, "Chip8 status");
    manager.AddPane(memoryViewer, wxRIGHT, "Memory");
    manager.AddPane(gamePanel, wxCENTER);
    manager.Update();

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

MainFrame::~MainFrame()
{
    manager.UnInit();
}

void MainFrame::OnOpenROM(wxCommandEvent&)
{
    wxFileDialog openFileDialog(this, _("Open ROM"), "", "", "Chip 8 ROMs (*.ch8)|*.ch8", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    if(chip8Emu->chip8->OpenROM(openFileDialog.GetPath().ToStdString()))
    {
        if(!pauseMenuItem->IsChecked())
            chip8Emu->chip8->Run();
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
            chip8Emu->chip8->Stop();
            pauseMenuItem->Check();
        }
        else
        {
            chip8Emu->chip8->Run();
            pauseMenuItem->Check(false);
        }
    }
}

void MainFrame::RefreshListCtrl()
{
    Chip8State state = chip8Emu->chip8->GetState();
    chip8Status->SetItem(0, 1, std::to_string(state.delay));
    chip8Status->SetItem(1, 1, std::to_string(state.sound));
    chip8Status->SetItem(2, 1, std::to_string(state.PC));
    chip8Status->SetItem(3, 1, std::to_string(state.I));
    chip8Status->SetItem(4, 1, std::to_string(state.SP));
}

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

MainFrame::MainFrame(Chip8Emu* app) : wxFrame(NULL, wxID_ANY, "Chip8Emu", wxPoint(50, 50), wxSize(800, 600)), manager(this)
{
    chip8Emu = app;
    memoryViewer = new MemoryList(this, chip8Emu->chip8->GetMemory());
    chip8Status = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
    gamePanel = new GamePanel(this, chip8Emu->chip8);

    CreatePanels();
    CreateMenuBar();

    Show();
}

static void addItem(wxListCtrl* list, const long id, const wxString text)
{
    wxListItem item;
    item.SetId(id);
    item.SetText(text);
    list->InsertItem(item);
}

void MainFrame::CreatePanels()
{
    wxListItem col;
    col.SetId(0);
    col.SetText("Register");
    col.SetWidth(70);
    chip8Status->InsertColumn(0, col);

    col.SetId(1);
    col.SetText("Value");
    col.SetWidth(60);
    chip8Status->InsertColumn(1, col);

    addItem(chip8Status, 0, "delay");
    addItem(chip8Status, 1, "sound");
    addItem(chip8Status, 2, "PC");
    addItem(chip8Status, 3, "I");
    addItem(chip8Status, 4, "SP");

    manager.AddPane(chip8Status, wxBOTTOM, "Chip8 status");
    manager.AddPane(memoryViewer, wxRIGHT, "Memory");
    manager.AddPane(gamePanel, wxCENTER);
    manager.Update();
}

void MainFrame::CreateMenuBar()
{
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

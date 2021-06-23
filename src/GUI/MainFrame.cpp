#include "MainFrame.hpp"
#include "../utils.hpp"

#include <wx/filedlg.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(IDOnOpenROM,  MainFrame::OnOpenROM)
    EVT_MENU(IDOnCloseROM, MainFrame::OnCloseROM)
    EVT_MENU(IDOnPause,    MainFrame::OnPause)
    EVT_MENU(IDOnQuit,     MainFrame::OnQuit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(Chip8Emu* app) : wxFrame(NULL, wxID_ANY, "Chip8Emu", wxPoint(50, 50), wxSize(800, 600)), manager(this)
{
    chip8Emu = app;
    speedPanel = new wxPanel(this);
    memoryViewer = new MemoryList(this, chip8Emu->chip8.GetMemory());
    chip8Status = new wxPropertyGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxPG_LIMITED_EDITING);
    gamePanel = new GamePanel(this, chip8Emu->chip8);

    speedSpin = new wxSpinCtrl(speedPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, CHIP8_MIN_SPEED, CHIP8_MAX_SPEED, CHIP8_DEFAULT_SPEED);
    speedSpin->Bind(wxEVT_SPINCTRL, [=] (const wxSpinEvent&) -> void {
        this->speedSlider->SetValue(this->speedSpin->GetValue());
        this->chip8Emu->chip8.SetEmulationSpeed(this->speedSpin->GetValue());
    });

    speedSlider = new wxSlider(speedPanel, wxID_ANY, CHIP8_DEFAULT_SPEED, CHIP8_MIN_SPEED, CHIP8_MAX_SPEED);
    speedSlider->Bind(wxEVT_SLIDER, [=] (const wxCommandEvent&) {
        this->speedSpin->SetValue(this->speedSlider->GetValue());
        this->chip8Emu->chip8.SetEmulationSpeed(this->speedSlider->GetValue());
    });

    CreatePanels();
    CreateMenuBar();

    gamePanel->SetFocus();
    Show();
}

#define APPEND(label, name) chip8Status->Append(new wxIntProperty(label, name)); chip8Status->SetPropertyReadOnly(label);

void MainFrame::CreatePanels()
{
    chip8Status->SetDoubleBuffered(true);
    chip8Status->SetColumnCount(3);
    APPEND("delay", wxPG_LABEL)
    APPEND("sound", wxPG_LABEL)
    APPEND("PC", wxPG_LABEL)
    APPEND("I", wxPG_LABEL)
    APPEND("SP", wxPG_LABEL)

    auto stack = chip8Status->Append(new wxPropertyCategory("Stack"));
    auto V = chip8Status->Append(new wxPropertyCategory("V"));

    for(int i = 0; i < 16; i++)
    {
        chip8Status->AppendIn(stack, new wxIntProperty(toHex(i, "%X"), "stack" + toHex(i, "%X")));
        chip8Status->AppendIn(V, new wxIntProperty(toHex(i, "%X"), "V" + toHex(i, "%X")));
    }
    chip8Status->SetPropertyReadOnly("Stack");
    chip8Status->SetPropertyReadOnly("V");

    wxSizer* speedSizer = new wxBoxSizer(wxHORIZONTAL);
    speedSizer->Add(speedSpin, 0);
    speedSizer->Add(speedSlider, 1);
    speedPanel->SetSizer(speedSizer);

    manager.AddPane(speedPanel, wxAuiPaneInfo().Caption("Emulation speed").Top().Floatable(false));
    manager.AddPane(gamePanel, wxCENTER);
    manager.AddPane(chip8Status, wxAuiPaneInfo().Caption("Chip8 status").Bottom().BestSize(0, 100));
    manager.AddPane(memoryViewer, wxAuiPaneInfo().Caption("Memory").Right().BestSize(160, 0));
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

    if(chip8Emu->chip8.OpenROM(openFileDialog.GetPath().ToStdString()))
    {
        if(!pauseMenuItem->IsChecked())
            chip8Emu->chip8.Run();
    }
    else
        wxMessageBox("Could not open ROM!");
}

void MainFrame::OnCloseROM(wxCommandEvent&)
{
    chip8Emu->chip8.CloseROM();
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
    if(chip8Emu->chip8.romOpened)
    {
        if(chip8Emu->chip8.IsRunning())
        {
            chip8Emu->chip8.Stop();
            pauseMenuItem->Check();
        }
        else
        {
            chip8Emu->chip8.Run();
            pauseMenuItem->Check(false);
        }
    }
}

void MainFrame::RefreshListCtrl()
{
    const Chip8State state = chip8Emu->chip8.GetState();
    chip8Status->SetPropertyValue("delay", state.delay);
    chip8Status->SetPropertyCell("delay", 2, "0x" + toHex(state.delay));
    chip8Status->SetPropertyValue("sound", state.sound);
    chip8Status->SetPropertyCell("sound", 2, "0x" + toHex(state.sound));
    chip8Status->SetPropertyValue("PC", state.PC);
    chip8Status->SetPropertyCell("PC", 2, "0x" + toHex(state.PC));
    chip8Status->SetPropertyValue("I", state.I);
    chip8Status->SetPropertyCell("I", 2, "0x" + toHex(state.I));
    chip8Status->SetPropertyValue("SP", state.SP);
    chip8Status->SetPropertyCell("SP", 2, "0x" + toHex(state.SP));

    char s[7];
    char v[3];
    for(int i = 0; i < 16; i++)
    {
        sprintf(s, "stack%X", i);
        chip8Status->SetPropertyValue(s, (int)state.stack[i]);
        chip8Status->SetPropertyCell(s, 2, "0x" + toHex(state.stack[i]));
        sprintf(v, "V%X", i);
        chip8Status->SetPropertyValue(v, state.V[i]);
        chip8Status->SetPropertyCell(v, 2, "0x" + toHex(state.V[i]));
    }

    chip8Status->Refresh();
}

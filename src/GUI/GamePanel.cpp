#include "GamePanel.hpp"

wxBEGIN_EVENT_TABLE(GamePanel, wxPanel)
    EVT_KEY_DOWN(GamePanel::OnKeyDown)
    EVT_KEY_UP(GamePanel::OnKeyUp)
    EVT_TIMER(IDOnTimer, GamePanel::OnTimer)
    EVT_PAINT(GamePanel::OnPaintEvent)
wxEND_EVENT_TABLE()

GamePanel::GamePanel(MainFrame* parent, Chip8& cpu) : wxPanel(parent), chip8(cpu), timer(this, IDOnTimer)
{
    mainFrame = parent;
    timer.Start(16);
    screen.Create(WIDTH, HEIGHT, chip8.screen, true);
}

void GamePanel::DrawScreen(wxDC& dc)
{
    const wxSize size = GetSize();
    if(size.x > 0 && size.y > 0)
        dc.DrawBitmap(wxBitmap(screen.Scale(size.x, size.y, wxIMAGE_QUALITY_NEAREST)), 0, 0);
}

void GamePanel::OnKeyDown(wxKeyEvent& event)
{
    const int key = event.GetKeyCode();
    if(key == WXK_NUMPAD0)
    {
        chip8.lastKey = 0;
        chip8.keys[0] = 1;
    }
    else if(key == WXK_NUMPAD7)
    {
        chip8.lastKey = 1;
        chip8.keys[1] = 1;
    }
    else if(key == WXK_NUMPAD8)
    {
        chip8.lastKey = 2;
        chip8.keys[2] = 1;
    }
    else if(key == WXK_NUMPAD9)
    {
        chip8.lastKey = 3;
        chip8.keys[3] = 1;
    }
    else if(key == WXK_NUMPAD4)
    {
        chip8.lastKey = 4;
        chip8.keys[4] = 1;
    }
    else if(key == WXK_NUMPAD5)
    {
        chip8.lastKey = 5;
        chip8.keys[5] = 1;
    }
    else if(key == WXK_NUMPAD6)
    {
        chip8.lastKey = 6;
        chip8.keys[6] = 1;
    }
    else if(key == WXK_NUMPAD1)
    {
        chip8.lastKey = 7;
        chip8.keys[7] = 1;
    }
    else if(key == WXK_NUMPAD2)
    {
        chip8.lastKey = 8;
        chip8.keys[8] = 1;
    }
    else if(key == WXK_NUMPAD3)
    {
        chip8.lastKey = 9;
        chip8.keys[9] = 1;
    }
    else if(key == WXK_NUMPAD_DECIMAL)
    {
        chip8.lastKey = 10;
        chip8.keys[10] = 1;
    }
    else if(key == WXK_NUMPAD_DIVIDE)
    {
        chip8.lastKey = 11;
        chip8.keys[11] = 1;
    }
    else if(key == WXK_NUMPAD_MULTIPLY)
    {
        chip8.lastKey = 12;
        chip8.keys[12] = 1;
    }
    else if(key == WXK_NUMPAD_SUBTRACT)
    {
        chip8.lastKey = 13;
        chip8.keys[13] = 1;
    }
    else if(key == WXK_NUMPAD_ADD)
    {
        chip8.lastKey = 14;
        chip8.keys[14] = 1;
    }
    else if(key == 70)
    {
        chip8.lastKey = 15;
        chip8.keys[15] = 1;
    }
}

void GamePanel::OnKeyUp(wxKeyEvent& event)
{
    const int key = event.GetKeyCode();
    if(key == WXK_NUMPAD0)
    {
        chip8.keys[0] = 0;
    }
    else if(key == WXK_NUMPAD7)
    {
        chip8.keys[1] = 0;
    }
    else if(key == WXK_NUMPAD8)
    {
        chip8.keys[2] = 0;
    }
    else if(key == WXK_NUMPAD9)
    {
        chip8.keys[3] = 0;
    }
    else if(key == WXK_NUMPAD4)
    {
        chip8.keys[4] = 0;
    }
    else if(key == WXK_NUMPAD5)
    {
        chip8.keys[5] = 0;
    }
    else if(key == WXK_NUMPAD6)
    {
        chip8.keys[6] = 0;
    }
    else if(key == WXK_NUMPAD1)
    {
        chip8.keys[7] = 0;
    }
    else if(key == WXK_NUMPAD2)
    {
        chip8.keys[8] = 0;
    }
    else if(key == WXK_NUMPAD3)
    {
        chip8.keys[9] = 0;
    }
    else if(key == WXK_NUMPAD_DECIMAL)
    {
        chip8.keys[10] = 0;
    }
    else if(key == WXK_NUMPAD_DIVIDE)
    {
        chip8.keys[11] = 0;
    }
    else if(key == WXK_NUMPAD_MULTIPLY)
    {
        chip8.keys[12] = 0;
    }
    else if(key == WXK_NUMPAD_SUBTRACT)
    {
        chip8.keys[13] = 0;
    }
    else if(key == WXK_NUMPAD_ADD)
    {
        chip8.keys[14] = 0;
    }
    else if(key == 70)
    {
        chip8.keys[15] = 0;
    }
    else if(key == 'A')
    {
        mainFrame->TooglePause();
    }
    else if(key == 'E')
    {
        if(chip8.IsRunning())
            chip8.Stop();

        chip8.Run(false);
    }
}

void GamePanel::OnTimer(wxTimerEvent&)
{
    wxClientDC clientDC(this);
    DrawScreen(clientDC);
    mainFrame->memoryViewer->Refresh();
    mainFrame->RefreshListCtrl();
}

void GamePanel::OnPaintEvent(wxPaintEvent&)
{
    wxPaintDC paintDC(this);
    DrawScreen(paintDC);
}

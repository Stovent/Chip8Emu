#include "GamePanel.hpp"

wxBEGIN_EVENT_TABLE(GamePanel, wxPanel)
    EVT_KEY_UP(GamePanel::OnKeyUp)
    EVT_KEY_DOWN(GamePanel::OnKeyDown)
wxEND_EVENT_TABLE()

GamePanel::GamePanel(Chip8Emu* app, MainFrame* parent) : wxPanel(parent)
{
    this->app = app;
    memset(screen, 0, WIDTH*HEIGHT*3);
}

GamePanel::~GamePanel()
{

}

void GamePanel::SetRandom()
{
    srand(time(0));
    for(int i = 0; i < WIDTH*HEIGHT*3; i+=3)
        if(rand() % 2)
        {
            screen[i] = 255;
            screen[i+1] = 255;
            screen[i+2] = 255;
        }
        else
        {
            screen[i] = 0;
            screen[i+1] = 0;
            screen[i+2] = 0;
        }
}

void GamePanel::RefreshScreen()
{
    wxClientDC dc(this);
    wxBitmap bitmap(wxImage(WIDTH, HEIGHT, screen, true).Scale(app->mainFrame->GetClientSize().x, app->mainFrame->GetClientSize().y, wxIMAGE_QUALITY_NEAREST));
    dc.DrawBitmap(bitmap, 0, 0);
}

void GamePanel::Draw(uint8_t x, uint8_t y, uint8_t n)
{
    uint8_t ligne;

    for(int j = 0; j < n; j++)
    {
        ligne = app->cpu->memory[app->cpu->I + j];

        for(int i = 0; i < 8; i++)
        {
            if(ligne & (0x80 >> i))
            {
                if(screen[(app->cpu->V[y] + j) * 3 * WIDTH + (app->cpu->V[x] + i) * 3])
                {
                    screen[(app->cpu->V[y] + j) * 3 * WIDTH + (app->cpu->V[x] + i) * 3] = 0;
                    screen[(app->cpu->V[y] + j) * 3 * WIDTH + (app->cpu->V[x] + i) * 3 + 1] = 0;
                    screen[(app->cpu->V[y] + j) * 3 * WIDTH + (app->cpu->V[x] + i) * 3 + 2] = 0;
                    app->cpu->VF = 1;
                }
                else
                {
                    screen[(app->cpu->V[y] + j) * 3 * WIDTH + (app->cpu->V[x] + i) * 3] = 255;
                    screen[(app->cpu->V[y] + j) * 3 * WIDTH + (app->cpu->V[x] + i) * 3 + 1] = 255;
                    screen[(app->cpu->V[y] + j) * 3 * WIDTH + (app->cpu->V[x] + i) * 3 + 2] = 255;
                }
            }
        }
    }
}

void GamePanel::ClearScreen()
{
    memset(screen, 0, WIDTH * HEIGHT * 3);
}

void GamePanel::OnWaitEvent(wxKeyEvent& event)
{
    app->cpu->lastKey = -1;
    switch(event.GetKeyCode())
    {
    case WXK_NUMPAD0:
        app->cpu->lastKey = 0;
    break;

    case WXK_NUMPAD7:
        app->cpu->lastKey = 1;
    break;

    case WXK_NUMPAD8:
        app->cpu->lastKey = 2;
    break;

    case WXK_NUMPAD9:
        app->cpu->lastKey = 3;
    break;

    case WXK_NUMPAD4:
        app->cpu->lastKey = 4;
    break;

    case WXK_NUMPAD5:
        app->cpu->lastKey = 5;
    break;

    case WXK_NUMPAD6:
        app->cpu->lastKey = 6;
    break;

    case WXK_NUMPAD1:
        app->cpu->lastKey = 7;
    break;

    case WXK_NUMPAD2:
        app->cpu->lastKey = 8;
    break;

    case WXK_NUMPAD3:
        app->cpu->lastKey = 9;
    break;

    case WXK_NUMPAD_DIVIDE:
        app->cpu->lastKey = 10;
    break;

    case WXK_NUMPAD_MULTIPLY:
        app->cpu->lastKey = 11;
    break;

    case WXK_NUMPAD_SUBTRACT:
        app->cpu->lastKey = 12;
    break;

    case WXK_NUMPAD_ADD:
        app->cpu->lastKey = 13;
    break;

    case WXK_NUMPAD_ENTER:
        app->cpu->lastKey = 14;
    break;

    case WXK_NUMPAD_DECIMAL:
        app->cpu->lastKey = 15;
    break;
    }
}

void GamePanel::OnKeyUp(wxKeyEvent& event)
{
    switch(event.GetKeyCode())
    {
    case WXK_NUMPAD0:
        app->cpu->keys[0] = 0;
    break;

    case WXK_NUMPAD7:
        app->cpu->keys[1] = 0;
    break;

    case WXK_NUMPAD8:
        app->cpu->keys[2] = 0;
    break;

    case WXK_NUMPAD9:
        app->cpu->keys[3] = 0;
    break;

    case WXK_NUMPAD4:
        app->cpu->keys[4] = 0;
    break;

    case WXK_NUMPAD5:
        app->cpu->keys[5] = 0;
    break;

    case WXK_NUMPAD6:
        app->cpu->keys[6] = 0;
    break;

    case WXK_NUMPAD1:
        app->cpu->keys[7] = 0;
    break;

    case WXK_NUMPAD2:
        app->cpu->keys[8] = 0;
    break;

    case WXK_NUMPAD3:
        app->cpu->keys[9] = 0;
    break;

    case WXK_NUMPAD_DIVIDE:
        app->cpu->keys[10] = 0;
    break;

    case WXK_NUMPAD_MULTIPLY:
        app->cpu->keys[11] = 0;
    break;

    case WXK_NUMPAD_SUBTRACT:
        app->cpu->keys[12] = 0;
    break;

    case WXK_NUMPAD_ADD:
        app->cpu->keys[13] = 0;
    break;

    case WXK_NUMPAD_ENTER:
        app->cpu->keys[14] = 0;
    break;

    case WXK_NUMPAD_DECIMAL:
        app->cpu->keys[15] = 0;
    break;
    }
}

void GamePanel::OnKeyDown(wxKeyEvent& event)
{
    OnWaitEvent(event);
    switch(event.GetKeyCode())
    {
    case WXK_NUMPAD0:
        app->cpu->keys[0] = 1;
    break;

    case WXK_NUMPAD7:
        app->cpu->keys[1] = 1;
    break;

    case WXK_NUMPAD8:
        app->cpu->keys[2] = 1;
    break;

    case WXK_NUMPAD9:
        app->cpu->keys[3] = 1;
    break;

    case WXK_NUMPAD4:
        app->cpu->keys[4] = 1;
    break;

    case WXK_NUMPAD5:
        app->cpu->keys[5] = 1;
    break;

    case WXK_NUMPAD6:
        app->cpu->keys[6] = 1;
    break;

    case WXK_NUMPAD1:
        app->cpu->keys[7] = 1;
    break;

    case WXK_NUMPAD2:
        app->cpu->keys[8] = 1;
    break;

    case WXK_NUMPAD3:
        app->cpu->keys[9] = 1;
    break;

    case WXK_NUMPAD_DIVIDE:
        app->cpu->keys[10] = 1;
    break;

    case WXK_NUMPAD_MULTIPLY:
        app->cpu->keys[11] = 1;
    break;

    case WXK_NUMPAD_SUBTRACT:
        app->cpu->keys[12] = 1;
    break;

    case WXK_NUMPAD_ADD:
        app->cpu->keys[13] = 1;
    break;

    case WXK_NUMPAD_ENTER:
        app->cpu->keys[14] = 1;
    break;

    case WXK_NUMPAD_DECIMAL:
        app->cpu->keys[15] = 1;
    break;

    case 'A':
        if(app->mainFrame->pauseMenuItem->IsChecked())
        {
            app->mainFrame->pauseMenuItem->Check(false);
            app->mainFrame->SetStatusText("Running");
        }
        else
        {
            app->mainFrame->pauseMenuItem->Check(true);
            app->mainFrame->SetStatusText("Pause");
        }
        app->mainFrame->OnPause();
    break;

    case 'E':
        if(app->mainFrame->pauseMenuItem->IsChecked() && app->cpu->romOpened)
            app->cpu->Execute();
    break;
    }
}

#include "GamePanel.hpp"

#include <cstring>
#include <cstdio>

wxBEGIN_EVENT_TABLE(GamePanel, wxPanel)
    EVT_KEY_UP(GamePanel::OnKeyUp)
    EVT_KEY_DOWN(GamePanel::OnKeyDown)
wxEND_EVENT_TABLE()

GamePanel::GamePanel(Chip8Emu* app, MainFrame* parent) : wxPanel(parent)
{
    this->app = app;
    scale = 10;
    memset(screen, 0, 64 * 32);
}

GamePanel::~GamePanel()
{

}

void GamePanel::SetRandom()
{
    srand(time(0));
    for(int j = 0; j < 32; j++)
        for(int i = 0; i < 64; i++)
            screen[j][i] = (rand() % 2) ? true : false;
}

void GamePanel::Updatee()
{
    wxClientDC dc(this);
    for(int j = 0; j < 32; j++)
    {
        for(int i = 0; i < 64; i++)
        {
            if(screen[j][i])
            {
                dc.SetBrush(*wxWHITE_BRUSH);
                dc.SetPen(wxPen(wxColor(255, 255, 255), 1));
            }
            else
            {
                dc.SetBrush(*wxBLACK_BRUSH);
                dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
            }

            dc.DrawRectangle(i * scale, j * scale, scale, scale);
        }
    }
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
                if(screen[app->cpu->V[y] + j][app->cpu->V[x] + i])
                {
                    screen[app->cpu->V[y] + j][app->cpu->V[x] + i] = 0;
                    app->cpu->VF = 1;
                }
                else
                    screen[app->cpu->V[y] + j][app->cpu->V[x] + i] = 255;
            }
        }
    }
}

void GamePanel::ClearScreen()
{
    memset(screen, 0, 64 * 32);
}

void GamePanel::OnKeyUp(wxKeyEvent& event)
{
    switch(event.GetKeyCode())
    {
    case WXK_NUMPAD0:
        app->cpu->keys[0] = 0;
    break;

    case WXK_NUMPAD1:
        app->cpu->keys[1] = 0;
    break;

    case WXK_NUMPAD2:
        app->cpu->keys[2] = 0;
    break;

    case WXK_NUMPAD3:
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

    case WXK_NUMPAD7:
        app->cpu->keys[7] = 0;
    break;

    case WXK_NUMPAD8:
        app->cpu->keys[8] = 0;
    break;

    case WXK_NUMPAD9:
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
    switch(event.GetKeyCode())
    {
    case WXK_NUMPAD0:
        app->cpu->keys[0] = 1;
    break;

    case WXK_NUMPAD1:
        app->cpu->keys[1] = 1;
    break;

    case WXK_NUMPAD2:
        app->cpu->keys[2] = 1;
    break;

    case WXK_NUMPAD3:
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

    case WXK_NUMPAD7:
        app->cpu->keys[7] = 1;
    break;

    case WXK_NUMPAD8:
        app->cpu->keys[8] = 1;
    break;

    case WXK_NUMPAD9:
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
        if(!app->cpu->run)
            app->cpu->run = true;
        else
            app->cpu->run = false;
    break;

    case 'E':
        app->cpu->Execute();
    break;
    }
}

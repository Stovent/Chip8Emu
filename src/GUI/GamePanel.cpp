#include "GamePanel.hpp"

#include <cstring>
#include <cstdio>

GamePanel::GamePanel(Chip8Emu* app, MainFrame* parent) : wxPanel(parent)
{
    this->app = app;
    scale = 8;
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

void GamePanel::Updatee(wxSizeEvent& event)
{
    Update();
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
//    Update();
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
                    screen[app->cpu->V[y] + j][app->cpu->V[x] + i] = 0;
                else
                    screen[app->cpu->V[y] + j][app->cpu->V[x] + i] = 255;
            }
        }
    }
    Updatee();
}

void GamePanel::ClearScreen()
{
    memset(screen, 0, 64 * 32);
}

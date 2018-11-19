#include "GamePanel.hpp"

#include <cstring>
#include <cstdio>

GamePanel::GamePanel(Chip8Emu* app, MainFrame* parent) : wxPanel(parent)
{
    this->app = app;
    this->parent = parent;
//    memset(screen, 0, 64 * 32);
}

void GamePanel::Update()
{
    wxClientDC dc(this);
    for(int j = 0; j < 32; j++)
    {
        for(int i = 0; i < 64; i++)
        {
            if(screen[j][i])
            {
                dc.SetBrush(*wxWHITE_BRUSH);
//                dc.SetPen(wxPen(wxColor(255, 255, 255), 1));
            }
            else
            {
                dc.SetBrush(*wxBLACK_BRUSH);
//                dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
            }

            dc.DrawPoint(i, j);
        }
    }
}

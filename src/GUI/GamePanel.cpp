#include "GamePanel.hpp"

GamePanel::GamePanel(Chip8Emu* app, MainFrame* parent) : wxPanel(parent)
{
    this->app = app;
    this->parent = parent;
}

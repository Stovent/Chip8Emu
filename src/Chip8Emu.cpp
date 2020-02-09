#include "Chip8Emu.hpp"

bool Chip8Emu::OnInit()
{
    chip8 = new Chip8(500);
    mainFrame = new MainFrame(this, "Chip8Emu", wxPoint(50, 50), wxSize(400, 300));
    gameThread = nullptr;
    return true;
}

int Chip8Emu::OnExit()
{
    StopGameThread();
    return 1;
}

void Chip8Emu::StartGameThread()
{
    StopGameThread();
    if(chip8->romOpened)
    {
        chip8->run = true;
        gameThread = new std::thread(&Chip8::Run, chip8);
    }
}

void Chip8Emu::StopGameThread()
{
    if(gameThread == nullptr)
        return;
    chip8->run = false;
    if(gameThread->joinable())
        gameThread->join();
    delete gameThread;
    gameThread = nullptr;
}

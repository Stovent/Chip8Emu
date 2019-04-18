#include "Chip8Emu.hpp"

bool Chip8Emu::OnInit()
{
    gameThread = nullptr;
    mainFrame = new MainFrame(this, "Chip8Emu", wxPoint(50, 50), wxSize(660, 410));
    if(mainFrame == nullptr)
        return false;

    cpu = new Chip8(mainFrame->gamePanel, 1000);

    return true;
}

int Chip8Emu::OnExit()
{
    return 1;
}

void Chip8Emu::StartGameThread()
{
    if(gameThread == nullptr && cpu->romOpened)
    {
        cpu->run = true;
        gameThread = new std::thread(&Chip8::Run, cpu);
    }
}

void Chip8Emu::StopGameThread()
{
    if(gameThread == nullptr)
        return;
    cpu->run = false;
    if(gameThread->joinable())
        gameThread->join();
    delete gameThread;
    gameThread = nullptr;
}

#include "Chip8Emu.hpp"

void runGameThread(Chip8Emu* app)
{
    app->cpu->Run();
}

bool Chip8Emu::OnInit()
{
    mainFrame = new MainFrame(this, "Chip8Emu", wxPoint(50, 50), wxSize(660, 410));
    if(mainFrame == nullptr)
        return false;

    cpu = new Chip8(mainFrame->gamePanel);

    return true;
}

int Chip8Emu::OnExit()
{
    return 1;
}

void Chip8Emu::StartGameThread()
{
    cpu->stop = false;
    if(gameThread == nullptr)
        gameThread = new std::thread(runGameThread, this);
}

void Chip8Emu::StopGameThread()
{
    if(gameThread != nullptr)
    {
        cpu->stop = true;
        if(gameThread->joinable())
            gameThread->join();
        delete gameThread;
        gameThread = nullptr;
    }
}

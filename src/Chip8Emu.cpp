#include "Chip8Emu.hpp"

void runGameThread(Chip8Emu* app)
{
    app->cpu->Run();
}

bool Chip8Emu::OnInit()
{
    mainFrame = new MainFrame(this, "Chip8Emu");
    if(mainFrame == nullptr)
        return false;
    mainFrame->gamePanel->Update();

    cpu = new Chip8(mainFrame->gamePanel);

    return true;
}

void Chip8Emu::StartGameThread()
{
    if(gameThread == nullptr)
        gameThread = new std::thread(runGameThread, this);
}

void Chip8Emu::StopGameThread()
{
    if(gameThread != nullptr)
    {
        gameThread->join();
        delete gameThread;
        gameThread = nullptr;
    }
}

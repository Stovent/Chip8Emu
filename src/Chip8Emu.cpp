#include "Chip8Emu.hpp"

bool Chip8Emu::OnInit()
{
    mainFrame = new MainFrame(this, "Chip8Emu");
    if(mainFrame == nullptr)
        return false;
    mainFrame->gamePanel->Update();

    cpu = new Chip8(mainFrame->gamePanel);

    cpu->LoadROM("ROM/MAZE.ch8");

//    cpu.Run();

    return true;
}

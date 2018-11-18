#include "Chip8Emu.hpp"

bool Chip8Emu::OnInit()
{
    mainFrame = new MainFrame(this, "Chip8Emu");
    if(mainFrame == nullptr)
        return false;
    mainFrame->Show();

//    cpu.Run();

    return true;
}

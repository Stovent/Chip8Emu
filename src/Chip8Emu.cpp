#include "Chip8Emu.hpp"

bool Chip8Emu::OnInit()
{
    chip8 = new Chip8(500);
    mainFrame = new MainFrame(this, "Chip8Emu", wxPoint(50, 50), wxSize(640, 320));
    return true;
}

int Chip8Emu::OnExit()
{
    mainFrame->Close();
    chip8->Stop(false);
    delete chip8;
    return 1;
}

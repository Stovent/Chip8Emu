#include "Chip8.hpp"

#include <cstring>
#include <cstdlib>
#include <cstdio>

Chip8::Chip8(GamePanel* gp) : audio(76, beep)
{
    gamePanel = gp;
    stop = false;
    memory = new uint8_t[4096];
    lastKey = -1;

    gp->ClearScreen();
    gp->RefreshScreen();
    Init();

    instructions[CLS].opcode = 0x00E0;  instructions[CLS].mask = 0xFFFF;     /* 00E0 */
    instructions[RET].opcode = 0x00EE;  instructions[RET].mask = 0xFFFF;     /* 00EE */
    instructions[JPaddr].opcode = 0x1000;  instructions[JPaddr].mask = 0xF000;     /* 1NNN */
    instructions[CALL].opcode = 0x2000;  instructions[CALL].mask = 0xF000;     /* 2NNN */
    instructions[SEVxByte].opcode = 0x3000;  instructions[SEVxByte].mask = 0xF000;     /* 3XNN */
    instructions[SNEVxByte].opcode = 0x4000;  instructions[SNEVxByte].mask = 0xF000;     /* 4XNN */
    instructions[SEVxVy].opcode = 0x5000;  instructions[SEVxVy].mask = 0xF00F;     /* 5XY0 */
    instructions[LDVxByte].opcode = 0x6000;  instructions[LDVxByte].mask = 0xF000;     /* 6XNN */
    instructions[ADDVxByte].opcode = 0x7000;  instructions[ADDVxByte].mask = 0xF000;     /* 7XNN */
    instructions[LDVxVy].opcode = 0x8000; instructions[LDVxVy].mask = 0xF00F;    /* 8XY0 */
    instructions[OR].opcode = 0x8001; instructions[OR].mask = 0xF00F;    /* 8XY1 */
    instructions[AND].opcode = 0x8002; instructions[AND].mask = 0xF00F;    /* 8XY2 */
    instructions[XOR].opcode = 0x8003; instructions[XOR].mask = 0xF00F;    /* BXY3 */
    instructions[ADDVxVy].opcode = 0x8004; instructions[ADDVxVy].mask = 0xF00F;    /* 8XY4 */
    instructions[SUB].opcode = 0x8005; instructions[SUB].mask = 0xF00F;    /* 8XY5 */
    instructions[SHR].opcode = 0x8006; instructions[SHR].mask = 0xF00F;    /* 8XY6 */
    instructions[SUBN].opcode = 0x8007; instructions[SUBN].mask = 0xF00F;    /* 8XY7 */
    instructions[SHL].opcode = 0x800E; instructions[SHL].mask = 0xF00F;    /* 8XYE */
    instructions[SNEVxVy].opcode = 0x9000; instructions[SNEVxVy].mask = 0xF00F;    /* 9XY0 */
    instructions[LDIaddr].opcode = 0xA000; instructions[LDIaddr].mask = 0xF000;    /* ANNN */
    instructions[JPV0addr].opcode = 0xB000; instructions[JPV0addr].mask = 0xF000;    /* BNNN */
    instructions[RND].opcode = 0xC000; instructions[RND].mask = 0xF000;    /* CXNN */
    instructions[DRW].opcode = 0xD000; instructions[DRW].mask = 0xF000;    /* DXYN */
    instructions[SKP].opcode = 0xE09E; instructions[SKP].mask = 0xF0FF;    /* EX9E */
    instructions[SKNP].opcode = 0xE0A1; instructions[SKNP].mask = 0xF0FF;    /* EXA1 */
    instructions[LDVxDT].opcode = 0xF007; instructions[LDVxDT].mask = 0xF0FF;    /* FX07 */
    instructions[LDVxK].opcode = 0xF00A; instructions[LDVxK].mask = 0xF0FF;    /* FX0A */
    instructions[LDDTVx].opcode = 0xF015; instructions[LDDTVx].mask = 0xF0FF;    /* FX15 */
    instructions[LDSTVx].opcode = 0xF018; instructions[LDSTVx].mask = 0xF0FF;    /* FX18 */
    instructions[ADDIVx].opcode = 0xF01E; instructions[ADDIVx].mask = 0xF0FF;    /* FX1E */
    instructions[LDFVx].opcode = 0xF029; instructions[LDFVx].mask = 0xF0FF;    /* FX29 */
    instructions[LDBVx].opcode = 0xF033; instructions[LDBVx].mask = 0xF0FF;    /* FX33 */
    instructions[LDIVx].opcode = 0xF055; instructions[LDIVx].mask = 0xF0FF;    /* FX55 */
    instructions[LDVxI].opcode = 0xF065; instructions[LDVxI].mask = 0xF0FF;    /* FX65 */
}

Chip8::~Chip8()
{
    delete[] memory;
}

bool Chip8::Init()
{
    if(memory == nullptr)
        return false;
    memset(memory, 0, 4096);
    LoadFont();
    Reset();

    return true;
}

void Chip8::ExportMemory()
{
    FILE* f = fopen("memory.bin", "wb");
    if(f == NULL)
        return;
    fwrite(memory, 1, 4096, f);
    fclose(f);
}

void Chip8::Run()
{
    while(true)
    {
        if(stop)
            break;

        Execute();
    }
}

void Chip8::LoadFont()
{
    memory[0] = 0xF0; memory[1] = 0x90; memory[2] = 0x90; memory[3] = 0x90; memory[4] = 0xF0; // O
    memory[5] = 0x20; memory[6] = 0x60; memory[7] = 0x20; memory[8] = 0x20; memory[9] = 0x70; // 1
    memory[10] = 0xF0; memory[11] = 0x10; memory[12] = 0xF0;memory[13] = 0x80; memory[14] = 0xF0; // 2
    memory[15] = 0xF0; memory[16] = 0x10; memory[17] = 0xF0;memory[18] = 0x10; memory[19] = 0xF0; // 3
    memory[20] = 0x90; memory[21] = 0x90; memory[22] = 0xF0;memory[23] = 0x10; memory[24] = 0x10; // 4
    memory[25] = 0xF0; memory[26] = 0x80; memory[27] = 0xF0;memory[28] = 0x10; memory[29] = 0xF0; // 5
    memory[30] = 0xF0; memory[31] = 0x80; memory[32] = 0xF0;memory[33] = 0x90; memory[34] = 0xF0; // 6
    memory[35] = 0xF0; memory[36] = 0x10; memory[37] = 0x20;memory[38] = 0x40; memory[39] = 0x40; // 7
    memory[40] = 0xF0; memory[41] = 0x90; memory[42] = 0xF0;memory[43] = 0x90; memory[44] = 0xF0; // 8
    memory[45] = 0xF0; memory[46] = 0x90; memory[47] = 0xF0;memory[48] = 0x10; memory[49] = 0xF0; // 9
    memory[50] = 0xF0; memory[51] = 0x90; memory[52] = 0xF0;memory[53] = 0x90; memory[54] = 0x90; // A
    memory[55] = 0xE0; memory[56] = 0x90; memory[57] = 0xE0;memory[58] = 0x90; memory[59] = 0xE0; // B
    memory[60] = 0xF0; memory[61] = 0x80; memory[62] = 0x80;memory[63] = 0x80; memory[64] = 0xF0; // C
    memory[65] = 0xE0; memory[66] = 0x90; memory[67] = 0x90;memory[68] = 0x90; memory[69] = 0xE0; // D
    memory[70] = 0xF0; memory[71] = 0x80; memory[72] = 0xF0;memory[73] = 0x80; memory[74] = 0xF0; // E
    memory[75] = 0xF0; memory[76] = 0x80; memory[77] = 0xF0;memory[78] = 0x80; memory[79] = 0x80; // F
}

bool Chip8::OpenROM(const char* file)
{
    FILE* f = fopen(file, "rb");
    if(f == NULL)
        return false;

    Init();

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* c = new char[size];
    fread(c, 1, size, f);
    memcpy(&memory[512], c, size);

    fclose(f);
    stop = false;
    return true;
}

void Chip8::Reset()
{
    last = wxGetLocalTimeMillis();
    gamePanel->ClearScreen();

    sound = 0;
    delay = 0;
    PC = 512;
    SP = 0;
    I = 0;

    for(int i = 0; i < 16; i++)
    {
        V[i] = 0;
        stack[i] = 0;
        keys[i] = 0;
    }
}

void Chip8::CloseROM()
{
    stop = true;
    memset(memory + 512, 0, 3584);
}

uint16_t Chip8::GetNextOpcode()
{
    return (memory[PC] << 8) | memory[PC+1];
}

int8_t Chip8::GetInstruction(uint16_t opcode) const
{
    for(uint8_t i = 0; i < 34; i++)
    {
        if((opcode & instructions[i].mask) == instructions[i].opcode)
            return i;
    }
    return -1;
}

void Chip8::Execute()
{
    if(PC > 4096)
        return;

    uint16_t opcode = GetNextOpcode(); PC += 2;
    uint16_t nnn = opcode & 0x0FFF;
    uint8_t nn = opcode & 0x00FF;
    uint8_t n = opcode & 0x000F;
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;

    switch(GetInstruction(opcode))
    {

    case CLS:
        gamePanel->ClearScreen();
    break;

    case RET:
        PC = stack[--SP];
    break;

    case JPaddr:
        PC = nnn;
    break;

    case CALL:
        stack[SP++] = PC;
        PC = nnn;
    break;

    case SEVxByte:
        if(V[x] == nn)
            PC += 2;
    break;

    case SNEVxByte:
        if(V[x] != nn)
            PC += 2;
    break;

    case SEVxVy:
        if(V[x] == V[y])
            PC += 2;
    break;

    case LDVxByte:
        V[x] = nn;
    break;

    case ADDVxByte:
        V[x] += nn;
    break;

    case LDVxVy:
        V[x] = V[y];
    break;

    case OR:
        V[x] |= V[y];
    break;

    case AND:
        V[x] &= V[y];
    break;

    case XOR:
        V[x] ^= V[y];
    break;

    case ADDVxVy:
        if(V[x] + V[y] > 255) VF = 1; else VF = 0;
        V[x] += V[y];
    break;

    case SUB:
        if(V[x] > V[y]) VF = 1; else VF = 0; // NOT Borrow
        V[x] -= V[y];
    break;

    case SHR:
        if(V[x] & 1) VF = 1; else VF = 0;
        V[x] >>= 1;
    break;

    case SUBN:
        if(V[y] > V[x]) VF = 1; else VF = 0; // NOT Borrow
        V[x] = V[y] - V[x];
    break;

    case SHL:
        if(V[x] & 0x8000) VF = 1; else VF = 0;
        V[x] <<= 1;
    break;

    case SNEVxVy:
        if(V[x] != V[y])
            PC += 2;
    break;

    case LDIaddr:
        I = nnn;
    break;

    case JPV0addr:
        PC = V[0] + nnn;
    break;

    case RND:
        srand(time(0));
        V[x] = (rand() % 256) & nn;
    break;

    case DRW:
        gamePanel->Draw(x, y, n);
    break;

    case SKP:
        if(keys[V[x]])
            PC += 2;
    break;

    case SKNP:
        if(!keys[V[x]])
            PC += 2;
    break;

    case LDVxDT:
        V[x] = delay;
    break;

    case LDVxK:
        while(lastKey < 0);
        V[x] = lastKey;
        lastKey = -1;
    break;

    case LDDTVx:
        delay = V[x];
    break;

    case LDSTVx:
        sound = V[x];
    break;

    case ADDIVx:
        I += V[x];
    break;

    case LDFVx:
        I = V[x] * 5;
    break;

    case LDBVx:
        memory[I] = V[x] / 100;
        memory[I+1] = (V[x] - memory[I] * 100) / 10;
        memory[I+2] = (V[x] - memory[I] * 100) - memory[I+1] * 10;
    break;

    case LDIVx:
        for(uint8_t i = 0; i <= x; i++)
            memory[I + i] = V[i];
    break;

    case LDVxI:
        for(uint8_t i = 0; i <= x; i++)
            V[i] = memory[I + i];
    break;
    }

    if(wxGetLocalTimeMillis() - last > 16)
    {
        last = wxGetLocalTimeMillis();
        if(delay)
            delay--;
        if(sound)
        {
            sound--;
            audio.Play();
        }

        gamePanel->RefreshScreen();
    }

    wxMicroSleep(1000);
}

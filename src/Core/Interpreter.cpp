#include "Chip8.hpp"

void Chip8::Interpreter()
{
    if(!romOpened)
        return;

    timePoint = std::chrono::steady_clock::now();
    while(run)
    {
        const uint16_t opcode = GetNextWord();
        switch(GetInstruction(opcode))
        {
        case CLS: // 00E0
            ClearScreen();
            break;

        case RET: // 00EE
            if(SP >= 0)
                PC = stack[SP--];
            else
                wxMessageBox("Stack empty (RET)");
            break;

        case JPaddr: // 1nnn
            PC = opcode & 0x0FFF;
            break;

        case CALL: // 2nnn
            if(SP < 15)
            {
                stack[++SP] = PC;
                PC = opcode & 0x0FFF;
            }
            else
                wxMessageBox("Stack full (CALL)");
            break;

        case SEVxByte: // 3xkk
        {
            uint8_t x  = (opcode & 0x0F00) >> 8;
            uint8_t kk = (opcode & 0x00FF);
            if(V[x] == kk)
                PC += 2;
            break;
        }

        case SNEVxByte: // 4xkk
        {
            uint8_t x  = (opcode & 0x0F00) >> 8;
            uint8_t kk = (opcode & 0x00FF);
            if(V[x] != kk)
                PC += 2;
            break;
        }

        case SEVxVy: // 5xy0
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            if(V[x] == V[y])
                PC += 2;
            break;
        }

        case LDVxByte: // 6xkk
        {
            uint8_t x  = (opcode & 0x0F00) >> 8;
            uint8_t kk = (opcode & 0x00FF);
            V[x] = kk;
            break;
        }

        case ADDVxByte: // 7xkk
        {
            uint8_t x  = (opcode & 0x0F00) >> 8;
            uint8_t kk = (opcode & 0x00FF);
            V[x] += kk;
            break;
        }

        case LDVxVy: // 8xy0
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            V[x] = V[y];
            break;
        }

        case ORVxVy: // 8xy1
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            V[x] |= V[y];
            break;
        }

        case ANDVxVy: // 8xy2
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            V[x] &= V[y];
            break;
        }

        case XORVxVy: // 8xy3
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            V[x] |= V[y];
            break;
        }

        case ADDVxVy: // 8xy4
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            VF = (V[x] + V[y]) > 255;
            V[x] += V[y];
            break;
        }

        case SUBVxVy: // 8xy5
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            VF = (V[x] > V[y]);
            V[x] -= V[y];
            break;
        }

        case SHRVxVy: // 8xy6
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            VF = V[x] & 1;
            V[x] >>= 1;
            break;
        }

        case SUBNVxVy: // 8xy7
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            VF = (V[y] > V[x]);
            V[x] = V[y] - V[x];
            break;
        }

        case SHLVxVy: // 8xyE
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            VF = (V[x] >> 7);
            V[x] <<= 1;
            break;
        }

        case SNEVxVy: // 9xy0
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            if(V[x] != V[y])
                PC += 2;
            break;
        }

        case LDIaddr: // Annn
            I = opcode & 0x0FFF;
            break;

        case JPV0addr: // Bnnn
            PC = (opcode & 0x0FFF) + V[0];
            break;

        case RND: // Cxkk
        {
            uint8_t x  = (opcode & 0x0F00) >> 8;
            uint8_t kk = (opcode & 0x00FF);
            srand(time(0));
            V[x] = (rand() % 256) & kk;
            break;
        }

        case DRW: // Dxyn
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            uint8_t y = (opcode & 0x00F0) >> 4;
            uint8_t n = (opcode & 0x000F);
            Draw(x, y, n);
            break;
        }

        case SKP: // Ex9E
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            if(keys[V[x]])
                PC += 2;
            break;
        }

        case SKNP: // ExA1
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            if(!keys[V[x]])
                PC += 2;
            break;
        }

        case LDVxDT: // Fx07
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            V[x] = delay;
            break;
        }

        case LDVxK: // Fx0A
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            WaitKey(x);
            break;
        }

        case LDDTVx: // Fx15
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            delay = V[x];
            break;
        }

        case LDSTVx: // Fx18
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            sound = V[x];
            break;
        }

        case ADDIVx: // Fx1E
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            I += V[x];
            break;
        }

        case LDFVx: // Fx29
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            I = 5*V[x];
            break;
        }

        case LDBVx: // Fx33
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            memory[I] = V[x] / 100;
            memory[I+1] = (V[x] - memory[I] * 100) / 10;
            memory[I+2] = (V[x] - memory[I] * 100) - memory[I+1] * 10;
            break;
        }

        case LDIVx: // Fx55
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            for(uint8_t i = 0; i <= x; i++)
                memory[I + i] = V[i];
            break;
        }

        case LDVxI: // Fx65
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            for(uint8_t i = 0; i <= x; i++)
                V[i] = memory[I + i];
            break;
        }

        default:
            wxMessageBox("Unknown opcode: " + std::to_string(opcode) + " at location " + std::to_string(PC-2));
        }

        std::chrono::nanoseconds t = std::chrono::steady_clock::now() - timePoint; // time to execute this instruction

        if(t.count() < clockInterval)
            std::this_thread::sleep_for(std::chrono::nanoseconds(clockInterval-t.count()));

        if(t.count() >= 16'666'666) // 16.666666 ms
        {
            if(delay)
                delay--;

            if(sound)
            {
                sound--;
                audio.Play();
            }

            timePoint = std::chrono::steady_clock::now();
        }
    }
}

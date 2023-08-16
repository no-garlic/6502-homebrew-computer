#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <iostream>

typedef uint16_t address_t;
typedef uint8_t  byte_t;

namespace MOS6502
{
    class InstructionSet;
    class CPU;

    static constexpr address_t PowerOnProgramCounterAddress = 0xFFFC;
    static constexpr byte_t    PowerOnStackPointer          = 0xFD;

    struct Registers
    {
        byte_t Accumulator          = 0x00;     // accumulator
        byte_t X                    = 0x00;     // x register
        byte_t Y                    = 0x00;     // y register
        byte_t StackPointer         = 0x00;     // stack pointer
        byte_t StatusRegister       = 0x00;     // status flags
        address_t ProgramCounter    = 0x0000;   // program counter
    };

    enum CPUFlags
    {
        CPUFlags_None               = 0x0,

        CPUFlags_CarryBit           = (0x1 << 0), // C
        CPUFlags_Zero               = (0x1 << 1), // Z
        CPUFlags_InterruptDisable   = (0x1 << 2), // I
        CPUFlags_DecimalMode        = (0x1 << 3), // D
        CPUFlags_Break              = (0x1 << 4), // B
        CPUFlags_Unused             = (0x1 << 5), // _
        CPUFlags_Overflow           = (0x1 << 6), // V
        CPUFlags_Negative           = (0x1 << 7)  // N
    };

    enum AddressMode
    {
        AddressMode_Unset,

        AddressMode_Implied,
        AddressMode_Immediate,
        AddressMode_ZeroPage,
        AddressMode_ZeroPageWithXOffset,
        AddressMode_ZeroPageWithYOffset,
        AddressMode_Relative,
        AddressMode_Absolute,
        AddressMode_AbsoluteWithXOffset,
        AddressMode_AbsoluteWithYOffset,
        AddressMode_Indirect,
        AddressMode_IndirectX,
        AddressMode_IndirectY
    };

    struct Instruction
    {
        char            Name[4];
        byte_t          (InstructionSet::*Func)(CPU&, AddressMode) const = nullptr;
        AddressMode     Mode = AddressMode_Unset;
        byte_t          OpCode = 0x00;
        byte_t          CPUCycles = 0;
    };

}


#include "InstructionSet.h"

namespace MOS6502
{
    InstructionSet::InstructionSet()
    {
        BuildOpCodeMatrix();
    }


    byte_t InstructionSet::Execute(CPU &cpu, byte_t opCode) const
    {
        Instruction instruction = m_OpCodeMatrix[opCode];
        byte_t cpuCycles = (this->*instruction.Func)(cpu, instruction.Mode);

        cpuCycles += instruction.CPUCycles;
        return cpuCycles;
    }


    byte_t InstructionSet::BRK(CPU &cpu, AddressMode addressMode) const
    {
        return 0;
    }


    byte_t InstructionSet::ORA(CPU &cpu, AddressMode addressMode) const
    {
        return 0;
    }


    void InstructionSet::BuildOpCodeMatrix()
    {
        using _ = InstructionSet;

        constexpr AddressMode IMM = AddressMode_Immediate;
        constexpr AddressMode IZX = AddressMode_IndirectX;

        m_OpCodeMatrix =
        {
            { "BRK", &_::BRK, IMM, 0x00, 7 },
            { "ORA", &_::ORA, IZX, 0x01, 6 }
        };
    }


}
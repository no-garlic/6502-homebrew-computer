#pragma once

#include "MOS6502.h"

namespace MOS6502
{
    class InstructionSet
    {
    public:
        InstructionSet();

        byte_t Execute(CPU &cpu, byte_t opCode) const;

        byte_t BRK(CPU &cpu, AddressMode addressMode) const;
        byte_t ORA(CPU &cpu, AddressMode addressMode) const;

    private:
        void BuildOpCodeMatrix();

        std::vector<Instruction> m_OpCodeMatrix;

    };

}

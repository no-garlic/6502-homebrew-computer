#pragma once

#include "MOS6502.h"
#include "InstructionSet.h"
#include "Bus.h"

namespace MOS6502
{
    class CPU
    {
    public:
        CPU();
        ~CPU();

        void PowerOn();
        void Reset();
        void Clock();

        byte_t Read(address_t address) const;
        void Write(address_t address, byte_t data);

        byte_t GetFlag(CPUFlags flag);
        void SetFlag(CPUFlags flag, bool set = true);
        void ResetFlag(CPUFlags flag);
        void ResetFlags();

        const Registers &GetRegisters() const { return m_Registers; }

        std::shared_ptr<InstructionSet> GetInstructionSet() const { return m_InstructionSet; }
        std::shared_ptr<Bus> GetAddressBus() const { return m_AddressBus; }

    private:
        address_t ReadSequentialAddress(address_t startAddress) const;

        Registers                       m_Registers;
        CPUFlags                        m_Flags;
        std::shared_ptr<InstructionSet> m_InstructionSet;
        std::shared_ptr<Bus>            m_AddressBus;

        uint32_t                        m_TotalCyclesSincePowerOn;
        uint32_t                        m_CpuCyclesToWait;
        bool                            m_PoweredOn;

    };

}

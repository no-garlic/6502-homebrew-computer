
#include "CPU.h"

namespace MOS6502
{
    CPU::CPU()
    : m_Flags(CPUFlags_None)
    , m_TotalCyclesSincePowerOn(0)
    , m_CpuCyclesToWait(0)
    , m_PoweredOn(false)
    {
        m_AddressBus = std::make_shared<Bus>();
        m_InstructionSet = std::make_shared<InstructionSet>();

        memset(&m_Registers, 0, sizeof(m_Registers));
    }


    CPU::~CPU()
    {
    }


    void CPU::PowerOn()
    {
        m_PoweredOn = true;
        Reset();
    }


    void CPU::Reset()
    {
        if (!m_PoweredOn)
            return;

        // reset the program counter
        address_t programCounterAddress = ReadSequentialAddress(PowerOnProgramCounterAddress);
        m_Registers.ProgramCounter = programCounterAddress;

        // reset the stack pointer
        m_Registers.StackPointer = PowerOnStackPointer;

        // reset the flags
        ResetFlags();

        // reset the internal register values
        m_Registers.Accumulator = 0x00;
        m_Registers.X = 0x00;
        m_Registers.Y = 0x00;

        // after a reset it takes 7 cpu cycles before the 6502 reads the program counter
        // address, and that takes a further 2 cycles.
        m_CpuCyclesToWait = 9;
        m_TotalCyclesSincePowerOn = 0;

        // reset all devices on the address bus
        m_AddressBus->Reset();
    }


    void CPU::Clock()
    {
        if (!m_PoweredOn)
            return;

        if (m_CpuCyclesToWait == 0)
        {
            // reset the flags
            ResetFlags();

            // get the next op code from the program counter address and then increment the program counter
            byte_t instructionOpCode = Read(m_Registers.ProgramCounter);
            m_Registers.ProgramCounter++;

            // execute the op code and set the number of cycles it took as our new cycles to wait
            m_CpuCyclesToWait = m_InstructionSet->Execute(*this, instructionOpCode);

            // reset the flags
            ResetFlags();
        }

        m_CpuCyclesToWait--;
        m_TotalCyclesSincePowerOn++;
    }


    byte_t CPU::Read(address_t address) const
    {
        return m_AddressBus->Read(address);
    }


    address_t CPU::ReadSequentialAddress(address_t startAddress) const
    {
        uint16_t lowByte  = Read(startAddress);
        uint16_t highByte = Read(startAddress + 1);

        address_t address = (highByte << 8) | lowByte;
        return address;
    }


    void CPU::Write(address_t address, byte_t data)
    {
        m_AddressBus->Write(address, data);
    }


    byte_t CPU::GetFlag(CPUFlags flag)
    {
        byte_t result = (m_Registers.StatusRegister & flag);
        return (result > 0) ? 1 : 0;
    }


    void CPU::SetFlag(CPUFlags flag, bool set)
    {
        if (set)
        {
            m_Registers.StatusRegister |= flag;
        }
        else
        {
            ResetFlag(flag);
        }
    }


    void CPU::ResetFlag(CPUFlags flag)
    {
        m_Registers.StatusRegister &= (~flag);
    }


    void CPU::ResetFlags()
    {
        // reset all flags to 0, except the unused bit is always set high
        m_Registers.StatusRegister = CPUFlags_Unused;
    }


}
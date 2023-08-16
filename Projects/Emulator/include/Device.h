#pragma once

#include "MOS6502.h"

namespace MOS6502
{
    class Device
    {
    public:
        Device();
        virtual ~Device();

        virtual void SetAddressRange(address_t startAddress, address_t endAddress);

        address_t GetStartAddress() const { return m_StartAddress; }
        address_t GetEndAddress() const { return m_EndAddress; }

        virtual void Reset();

        virtual byte_t Read(address_t address) const;
        virtual void Write(address_t address, byte_t data);

    private:
        address_t m_StartAddress;
        address_t m_EndAddress;

    };

}

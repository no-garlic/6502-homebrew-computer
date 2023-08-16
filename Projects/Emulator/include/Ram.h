#pragma once

#include "MOS6502.h"
#include "Device.h"

namespace MOS6502
{
    class Ram : public Device
    {
    public:
        Ram();
        virtual ~Ram();

        virtual void SetAddressRange(address_t startAddress, address_t endAddress) override;

        virtual void Reset() override;

        virtual byte_t Read(address_t address) const override;
        virtual void Write(address_t address, byte_t data) override;

    private:
        std::shared_ptr<std::vector<byte_t>> m_Memory;

    };

}

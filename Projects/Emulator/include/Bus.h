#pragma once

#include "MOS6502.h"
#include "Device.h"

namespace MOS6502
{
    class Bus
    {
    public:
        Bus();
        ~Bus();

        void AddDevice(std::shared_ptr<Device> device);

        void Reset();

        byte_t Read(address_t address) const;
        void Write(address_t address, byte_t data);

    private:
        std::vector<std::shared_ptr<Device>> m_Devices;

    };

}

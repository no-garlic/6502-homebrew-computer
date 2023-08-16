
#include "Bus.h"

namespace MOS6502
{
    Bus::Bus()
    {
    }


    Bus::~Bus()
    {
    }


    void Bus::AddDevice(std::shared_ptr<Device> device)
    {
        m_Devices.push_back(device);
    }


    void Bus::Reset()
    {
        for (auto device : m_Devices)
        {
            device->Reset();
        }
    }


    byte_t Bus::Read(address_t address) const
    {
        for (auto device : m_Devices)
        {
            if (address >= device->GetStartAddress() && address <= device->GetEndAddress())
            {
                return device->Read(address);
            }
        }

        return 0x00;
    }


    void Bus::Write(address_t address, byte_t data)
    {
        for (auto device : m_Devices)
        {
            if (address >= device->GetStartAddress() && address <= device->GetEndAddress())
            {
                return device->Write(address, data);
            }
        }
    }

}
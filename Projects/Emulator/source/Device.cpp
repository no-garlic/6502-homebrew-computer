
#include "Device.h"

namespace MOS6502
{
    Device::Device()
    : m_StartAddress(0x0000)
    , m_EndAddress(0x0000)
    {
    }


    Device::~Device()
    {
    }


    void Device::SetAddressRange(address_t startAddress, address_t endAddress)
    {
        m_StartAddress = startAddress;
        m_EndAddress = endAddress;
    }


    void Device::Reset()
    {
    }


    byte_t Device::Read(address_t address) const
    {
        return 0x00;
    }


    void Device::Write(address_t address, byte_t data)
    {
    }


}
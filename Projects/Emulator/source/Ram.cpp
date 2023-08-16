
#include "Ram.h"

namespace MOS6502
{
    Ram::Ram()
    : Device()
    {
        m_Memory = std::make_shared<std::vector<byte_t>>(0x00);
    }


    Ram::~Ram()
    {
    }


    void Ram::SetAddressRange(address_t startAddress, address_t endAddress)
    {
        Device::SetAddressRange(startAddress, endAddress);

        assert(endAddress > startAddress);
        address_t size = endAddress - startAddress;

        m_Memory->resize(size, 0x00);
        Reset();
    }


    void Ram::Reset()
    {
        Device::Reset();

        memset(&(m_Memory->at(0)), 0x00, m_Memory->size() * sizeof(byte_t));
    }


    byte_t Ram::Read(address_t address) const
    {
        size_t index = address - GetStartAddress();
        return m_Memory->at(index);
    }


    void Ram::Write(address_t address, byte_t data)
    {
        size_t index = address - GetStartAddress();
        m_Memory->at(index) = data;
    }



}

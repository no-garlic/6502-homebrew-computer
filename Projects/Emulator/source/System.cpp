
#include "System.h"

namespace MOS6502
{
    System::System()
    {
        m_CPU = std::make_shared<CPU>();
        m_AddressBus = m_CPU->GetAddressBus();

        m_Memory = std::make_shared<Ram>();
        m_Memory->SetAddressRange(0x0000, 0xFFFF);
        m_AddressBus->AddDevice(m_Memory);

        m_CPU->PowerOn();
    }


    System::~System()
    {
    }


    void System::Reset()
    {
        m_CPU->Reset();
    }


    void System::Clock()
    {
        m_CPU->Clock();
    }

}

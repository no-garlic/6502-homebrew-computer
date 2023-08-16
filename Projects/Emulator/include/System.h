#pragma once

#include "MOS6502.h"
#include "CPU.h"
#include "Bus.h"
#include "Ram.h"

namespace MOS6502
{
    class System
    {
    public:
        System();
        ~System();

        void Reset();
        void Clock();

    private:
        std::shared_ptr<CPU> m_CPU;
        std::shared_ptr<Bus> m_AddressBus;
        std::shared_ptr<Ram> m_Memory;

    };
}
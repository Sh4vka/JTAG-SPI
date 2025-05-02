#include "Signal.h"
#pragma once

class JTAG {
protected:
        std::deque<uint8_t> dq_TCK;
        std::deque<uint8_t> dq_TMS;
        std::deque<uint8_t> dq_TDI;
        std::deque<uint8_t> dq_TDO;

        Signal TCK;
        Signal TMS;
        Signal TDI;
        Signal TDO;

public:
        JTAG();
        void pulse_TCK();
        void shift_byte(uint8_t byte);
        void log_all();
        void print_log();

        void mv_idle_shift_dr();
        void mv_shift_dr_update_idle();
};

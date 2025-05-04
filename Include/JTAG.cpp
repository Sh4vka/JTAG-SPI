#include <iostream>
#include <cstdint>
#include <string>
#include <deque>

#include "Signal.h"
#include "JTAG.h"

JTAG::JTAG() : 
        TCK("TCK", 0, dq_TCK),
        TMS("TMS", 2, dq_TMS),
        TDI("TDI", 2, dq_TDI),
        TDO("TDO", 2, dq_TDO) {}

void JTAG::pulse_TCK() {
        TCK.set(0); log_all();
        TCK.set(1); log_all();
}

void JTAG::shift_byte(uint8_t byte) {
        for (int i = 0; i < 8; ++i) {
                TDI.set((byte >> i) & 1);
                pulse_TCK();
        }
        TDI.set(2);
}

void JTAG::log_all() {
        TCK.push_log();
        TMS.push_log();
        TDI.push_log();
        TDO.push_log();
}

void JTAG::print_log() {
        TCK.print_signal();
        TMS.print_signal();
        TDI.print_signal();
        TDO.print_signal();
}

void JTAG::mv_idle_shift_dr() {
        TCK.set(1); log_all();
        TMS.set(1); pulse_TCK(); //SELECT_DR_SCAN
        TMS.set(0); pulse_TCK(); //CAPTURE_DR
}

void JTAG::mv_shift_dr_update_idle() {
        TMS.set(1); pulse_TCK(); //EXIT_DR
        pulse_TCK(); //UPDATE_DR
        TMS.set(0); pulse_TCK(); //IDLE
}

#include <Signal.h>

#pragma once

class SPI {
protected:
        std::deque<uint8_t> dq_CS;
        std::deque<uint8_t> dq_SCK;
        std::deque<uint8_t> dq_MISO;
        std::deque<uint8_t> dq_MOSI;

        Signal CS;
        Signal SCK;
        Signal MISO;
        Signal MOSI;

public:
        SPI();
//        void pulse_CK();
        void shift_byte(uint8_t byte);
        void log_all();
        void print_log();
};

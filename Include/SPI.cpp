#include <iostream>
#include <deque>
#include <string>
#include <deque>

#include "Signal.h"
#include "SPI.h"

SPI::SPI() :
        CS("CS", 1, dq_CS),
        SCK("SCK", 0, dq_SCK),
        MISO("MISO", 2, dq_MISO),
        MOSI("MOSI", 2, dq_MOSI) {}

void SPI::shift_byte(uint8_t byte) {
        log_all();
        CS.set(0);
        for (int i = 7; i >= 0; --i) {
                MOSI.set((byte >> i) & 1);
                SCK.set(1); log_all();
                /////
                SCK.set(0); log_all();
        }
        CS.set(1);
        SCK.set(1);
        MOSI.set(2);
        log_all();
}

void SPI::log_all() {
        CS.push_log();
        SCK.push_log();
        MISO.push_log();
        MOSI.push_log();
}

void SPI::print_log() {
        CS.print_signal();
        SCK.print_signal();
        MISO.print_signal();
        MOSI.print_signal();
}

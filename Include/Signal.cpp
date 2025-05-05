#include <iostream>
#include <deque>
#include <cstdint>
#include <string>
#include "Signal.h"

Signal::Signal(std::string n_name, 
                uint8_t n_value, 
                std::deque<uint8_t> n_log) : 
                name(n_name), value(n_value), log(n_log) {}

void Signal::set(uint8_t v) {
        value = v;
}

uint8_t Signal::get() {
        return value;
}

void Signal::push_log() {
        log.push_back(value);
}

std::deque<uint8_t> Signal::get_log() {
        return log;
}

std::string Signal::get_name() {
        return name;
}

void Signal::print_signal() {
        std::cout << name << ": ";
        for (int i = 0; i < log.size(); i++){
                switch ((int)log[i]) {
                        case 0:
                                std::cout << u8"\u2581";
                                break;
                        case 1:
                                std::cout << u8"\u2588";
                                break;
                        case 2:
                                std::cout << u8"\u2584";
                                 break;
                }
        }
        std::cout << std::endl<< std::endl;
}

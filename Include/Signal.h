#include <iostream>
#include <deque>
#include <cstdint>
#include <string>

#pragma once

class Signal {
private:
        std::string name;
        uint8_t value;
        std::deque<uint8_t> log;
public:
        Signal(std::string n_name,
                uint8_t n_value,
                std::deque<uint8_t> n_log);

        void set(uint8_t v);
        uint8_t get();

        void push_log();
        std::deque<uint8_t> get_log();
        std::string get_name();
        void print_signal();
};

#include <iostream>
#include <cstdint>
#include <deque>

std::deque<uint8_t> dq_TCK;
std::deque<uint8_t> dq_TMS;
std::deque<uint8_t> dq_TDI;
std::deque<uint8_t> dq_TDO;

// 0 - false; 1 - true; 2 - unknown/Z
uint8_t TCK = 0;
uint8_t TMS = 2; 
uint8_t TDI = 2;
uint8_t TDO = 2;

void set_TCK(uint8_t stat) {
    TCK = stat;
    dq_TCK.push_back(TCK);
    dq_TMS.push_back(TMS);
    dq_TDI.push_back(TDI);
    dq_TDO.push_back(TDO);
}

void full_pulse() {
    set_TCK(0);
    set_TCK(1);
}

void move_idle_shift_dr() {
    // Автомат в IDLE
    TMS = 1; full_pulse(); //SELECT_DR_SCAN
    TMS = 0; full_pulse(); //CAPTURE_DR
    TMS = 0; full_pulse(); //SHIFT_DR
}

void move_shift_dr_update_idle() {
    TMS = 1; full_pulse(); //EXIT_DR
    full_pulse(); //UPDATE_DR
    TMS = 0; full_pulse(); //IDLE
}

uint8_t shift_byte(uint8_t byte) {
    uint8_t out = 0;
    for (int i = 0; i <= 7; i++) {
        TDI = (byte >> i) & 1;
        set_TCK(0);
        if (TDO == 1) {
            out |= (1 << i);
        }
        set_TCK(1);
    }
    TDI = 2;
    TDO = 2;
    return out;
}

void print_diagram(std::deque<uint8_t> dq) {
    for (int i = 0; i < dq.size(); i++){
        switch ((int)dq[i]) {
            case 0:
                std::cout << "_";
                break;
            case 1:
                std::cout << "‾";
                break;
            case 2:
                std::cout << "-";
                break;
        }
    }
    std::cout << std::endl << std::endl;
}

int main() {
    set_TCK(1);
    move_idle_shift_dr();
    uint8_t num = 0x55;
    uint8_t received = shift_byte(num);
    move_shift_dr_update_idle();
    std::cout << "TCK: ";  print_diagram(dq_TCK);
    std::cout << "TMS: "; print_diagram(dq_TMS);
    std::cout << "TDI: "; print_diagram(dq_TDI);
    std::cout << "TDO: "; print_diagram(dq_TDO);
    return 0;
}

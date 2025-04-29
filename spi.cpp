#include <iostream>
#include <cstdint>
#include <deque>

std::deque<bool> dq_CS;
std::deque<bool> dq_SCK;
std::deque<bool> dq_MISO;
std::deque<bool> dq_MOSI;

bool MOSI = false;
bool MISO = false;
bool SCK = false;
bool CS = true;

void append_stat() {
    dq_CS.push_back(CS);
    dq_SCK.push_back(SCK);
    dq_MOSI.push_back(MOSI);
    dq_MISO.push_back(MISO);
}

void set_SCK(bool stat) {
    SCK = stat;
    append_stat();
}

uint8_t transfer(uint8_t data_in) {
    uint8_t data_out = 0;
    append_stat();
    CS = false; //Выбрали устройство
    for (int i = 7; i >= 0; --i) {
        MOSI = (data_in >> i) & 1;
        set_SCK(true);
        data_out <<= 1;
        if (MISO) {
            data_out |= 1;
        }
        set_SCK(false);
    }
    CS = true;
    set_SCK(true);
    return data_out;
}

void print_diagram(std::deque<bool> dq) {
    for (int i = 0; i < dq.size(); i++){
        switch (dq[i]) {
            case false:
                std::cout << "_";
                break;
            case true:
                std::cout << "‾";
                break;
        }
    }
    std::cout << std::endl << std::endl;
}

int main() {
    uint8_t data_send = 0x55;
    uint8_t data_out = transfer(data_send);
    std::cout << "SCK:  "; print_diagram(dq_SCK);
    std::cout << "CS:   "; print_diagram(dq_CS);
    std::cout << "MOSI: "; print_diagram(dq_MOSI);
    std::cout << "MISO: "; print_diagram(dq_MISO);
    return 0;
}

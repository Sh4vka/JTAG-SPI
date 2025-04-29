#include <iostream>
#include <cstdint>
#include <deque>

std::deque<uint8_t> dq_CS;
std::deque<uint8_t> dq_SCK;
std::deque<uint8_t> dq_MISO;
std::deque<uint8_t> dq_MOSI;

uint8_t MOSI = 2;
uint8_t MISO = 2;
uint8_t SCK = 0;
uint8_t CS = 1;

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
    CS = 0; //Выбрали устройство
    for (int i = 7; i >= 0; --i) {
        MOSI = (data_in >> i) & 1;
        set_SCK(true);
        data_out <<= 1;
        if (MISO) {
            data_out |= 1;
        }
        set_SCK(false);
    }
    CS = 1;
    set_SCK(true);
    return data_out;
}

void print_diagram(std::deque<uint8_t>dq) {
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
    uint8_t data_send = 0x55;
    uint8_t data_out = transfer(data_send);
    std::cout << "SCK:  "; print_diagram(dq_SCK);
    std::cout << "CS:   "; print_diagram(dq_CS);
    std::cout << "MOSI: "; print_diagram(dq_MOSI);
    std::cout << "MISO: "; print_diagram(dq_MISO);
    return 0;
}

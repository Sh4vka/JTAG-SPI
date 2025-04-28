#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool TCK = 0;
bool TMS = 0;
bool TDI = 0;
bool TDO = 0;

void set_TCK(bool n) {
    TCK = n;
    printf("TCK: %d\n", n);
}

void full_pulse(){
    set_TCK(1);
    set_TCK(0);
}

void set_TMS(bool n) {
    TMS = n;
    printf("TMS: %d\n", n);
}

void move_to_shift_dr() {
    //Допустим он на Test_Logic/Reset
    set_TMS(0); full_pulse();
    set_TMS(1); full_pulse();
    set_TMS(0); full_pulse();
    set_TMS(0); full_pulse();
}

uint8_t shift_byte(uint8_t sent) {
    uint8_t out = 0;
    for (int i = 0; i <= 7; i++) {
        set_TCK(1);
        TDI = (sent >> i) & 1;//данные задвигаются по переднему фронту
        printf("TDI: %d\n", TDI);
        set_TCK(0);//выдвигаются по заднему фронту
        if (TDO) {
            out |= (1 << i);
        }
    }
    return out;
}

int main() {
    move_to_shift_dr();
    uint8_t sent = 0x55;
    uint8_t out = shift_byte(sent);
    return 0;
}



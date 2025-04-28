#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool MOSI = 0; //Master out
bool MISO = 0; //Master in
bool SCK = 0; //фронты
bool CS = 1; //активный ноль

uint8_t transfer (uint8_t data_out) { // функция отправки
    uint8_t data_in = 0;
    CS = 0; //выбираем устройство
    for (int i = 7; i >= 0; i--) { 
        MOSI = (data_out >> i) & 1; //сдвигаем вправо на i и берем младший
        SCK = 1; //типо фронт
        data_in <<= 1; //текущие принятые сдвигаем
        if (MISO) {
            data_in |= 1; //если на MISO 1 то устанавливаем младший бит
        }
        SCK = 0; //задний фронт
    }
    CS = 1; //прекратили коннект
    return data_in;
}

int main() {
    uint8_t data_send = 0x55;
    uint8_t data_out;
    data_out = transfer(data_send);
    return 0;
}

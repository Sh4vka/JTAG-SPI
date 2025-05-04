#include "JTAG.h"
#include "SPI.h"
#include "Signal.h"

int main() {
        JTAG jtag;
        jtag.shift_byte(0x55);
        jtag.print_log();

        SPI spi;
        spi.shift_byte(0x55);
        spi.print_log();
        return 0;
}


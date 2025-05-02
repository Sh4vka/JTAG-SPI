#include "JTAG.h"
#include "Signal.h"

int main() {
        JTAG jtag;
        jtag.mv_idle_shift_dr();
        jtag.shift_byte(0x55);
        jtag.mv_shift_dr_update_idle();
        jtag.print_log();
        return 0;
}


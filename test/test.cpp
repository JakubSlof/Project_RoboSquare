#include <Arduino.h>
#include "SmartServoBus.hpp"

using namespace lx16a;

static SmartServoBus servoBus;

void setup() {
    // Servos on the bus must have sequential IDs, starting from 0 (not 1)!
    // The '1' below is count of servos on the bus, not servo ID.
    servoBus.begin(1, UART_NUM_1, GPIO_NUM_27);

    /*
    // Set servo Id (must be only one servo connected to the bus)
    servoBus.setId(0);
    while (true) {
        printf("GetId: %d\n", servoBus.getId());
        delay(1000);
    }
    */

    printf("Current pos: %f\n", servoBus.pos(0).deg());
    servoBus.set(0, 180_deg);
}

void loop() {
}
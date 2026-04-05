#include "oled.h"

// void setup() {
//   oled_setup();
//   pinMode(LED_BUILTIN, OUTPUT);
// }

// uint8_t enabled=0;

// void loop() {
//   oled_print("23.456.789", "^        *");
//   delay(1000);

//   digitalWrite(LED_BUILTIN, enabled);
//   enabled = enabled >0? 0:1;
//   oled_invert(enabled);
// }

/*
 ./bin/avrdude -C ./etc/avrdude.conf -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -v
 */

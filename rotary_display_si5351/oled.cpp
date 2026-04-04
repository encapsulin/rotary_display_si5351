#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "oled.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

// #define oled_char_size 2

// String line1="23.456.789";
// String line2="^        *";

// void testdrawchar(void) {
//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setTextColor(WHITE);
//   display.setCursor(0, 0);

//   for (uint8_t i = 0; i < 168; i++) {
//     if (i == '\n') continue;
//     display.write(i);
//     if ((i > 0) && (i % 21 == 0))
//       display.println();
//   }
//   display.display();
//   delay(1);
// }

void oled_print(String str, uint8_t col, uint8_t row) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(1, row * 15);
  display.print(str);
  display.display();
}
void oled_print(String str, String str2) {
  display.clearDisplay();
  oled_print(str,0,0);
  oled_print(str2,0,1);
}
void oled_print(String str) {
  display.clearDisplay();
  oled_print(str,0,0);
}

void oled_setup() {
  bool i2c_found;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(200);
  display.display();
  delay(200);
  oled_print("ASDF", 1, 1);
  display.clearDisplay();
}
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "oled.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

uint8_t oled_char_size = 1;
uint8_t oled_screen_shift_x = 30;
uint8_t oled_screen_shift_y = 16;

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
  display.setTextSize(oled_char_size);
  display.setTextColor(WHITE);
  display.setCursor(oled_screen_shift_x, row * oled_char_size * 8 + oled_screen_shift_y);
  display.print(str);
  display.display();
}
void oled_print(String str, String str2) {
  display.clearDisplay();
  oled_print(str, 0, 0);
  oled_print(str2, 0, 1);
}
void oled_print(String str) {
  display.clearDisplay();
  oled_print(str, 0, 0);
}

void oled_setup() {
   oled_setup(2, 0, 0);
  //oled_setup(1,30,16);
}

void oled_setup(uint8_t char_size, uint8_t shift_x, uint8_t shift_y) {
  oled_char_size = char_size;
  oled_screen_shift_x = shift_x;
  oled_screen_shift_y = shift_y;

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(200);
  display.display();
  delay(200);
  oled_print("ASDF", 0, 0);
  delay(1000);
  display.clearDisplay();
}

void oled_invert(uint8_t onoff){
  display.invertDisplay(onoff);
}

// uint8_t enabled=0;
// void oled_invert(){
//   enabled = enabled >0? 0:1;
//   display.invertDisplay(enabled);
// }
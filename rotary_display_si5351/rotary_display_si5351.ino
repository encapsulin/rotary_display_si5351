#include "rotary.h"
// #include "disp.h"
#include "oled.h"
#include "synth.h"
#include "utils.h"

int cursor_position = 0;
char cursor_mode = '^';  // * or ^
String line1 = "";
String line2 = "";

void this_cursor_show() {
  // disp_print(utils_draw_char_at(cursor_mode, cursor_position), 0, 1);
  line2 = utils_draw_char_at(cursor_mode, cursor_position);
  oled_print(line1, line2);
}

void setup() {
  Serial.begin(9600);

  // disp_setup();
  oled_setup();
  rotary_setup();
  synth_setup();
  this_cursor_show();
  pinMode(LED_BUILTIN, OUTPUT);
}

void this_cursor_move() {
  cursor_position += rotary_get_direction();
  if (cursor_position > 9)
    cursor_position = 9;
  if (cursor_position < 0)
    cursor_position = 0;

  this_cursor_show();
}

void this_adjust_frequency() {
  Serial.println("this_adjust_frequency()");
  synth_adjust(rotary_get_direction(), cursor_position);
  this_show_synth_freq();
}

void this_show_synth_freq() {
  //disp_show(synth_get());
  if (line1 == synth_get())
    return;
  line1 = synth_get();
  oled_print(line1, line2);
}

void this_switch_cursor() {
  Serial.print(cursor_mode);
  if (cursor_mode == '^')
    cursor_mode = '*';
  else if (cursor_mode == '*') {
    cursor_mode = '^';
    synth_save();
  }
  Serial.println(cursor_mode);
  this_cursor_show();
}

static unsigned long lastPressTime = 0;
uint8_t blink = 0;
void this_blink() {
  unsigned long now = millis();
  if (now - lastPressTime > 4000) {
    lastPressTime = now;
    digitalWrite(LED_BUILTIN, blink);
    blink = blink > 0 ? 0 : 1;
  }
}
/////////////
void loop() {
  if (rotary_rotated() > 0) {
    //this_cursor_show();
    if (cursor_mode == '^') {
      this_cursor_move();
    }

    if (cursor_mode == '*')
      this_adjust_frequency();
  }

  if (rotary_pressed() > 0) {
    this_switch_cursor();
  }

  // Здесь может быть любой ваш код, даже delay(1000)
  // Прерывание все равно сработает в фоне!
  this_show_synth_freq();

  //delay(100);
  this_blink();
}
#include "synth.h"
#include "utils.h"
#include "eeprom.h"

int f_M = 1;
int f_K = 1;
int f_H = 1;
int f_pos = 0;
int f_step = 0;  // 0: select M/K/H; 1:change selected freq;


#include "si5351.h"
Si5351 si5351;

void si5351_adjustF(int fM, int fK, int fH) {

  uint64_t freq = 0ULL;
  if (fM > 0)
    freq += fM * 100000000ULL;
  if (fK > 0)
    freq += fK * 100000;
  if (fH > 0)
    freq += fH * 100;
  int32_t correction = 321000;  //27.11


  si5351.set_freq(freq, SI5351_CLK1);
  si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_8MA);
  si5351.set_correction(correction, SI5351_PLL_INPUT_XO);
  si5351.update_status();

  pinMode(LED_BUILTIN, OUTPUT);
}

void si5351_setup() {
  bool i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_0PF, 0, 0);
  Serial.println("si5351_setup()");
  if (!i2c_found) {
    Serial.println("not found on I2C");
  } else {
    Serial.println("ok");
    si5351_adjustF(f_M, f_K, f_H);
  }
}

void synth_setup() {
  Serial.println("synth_setup()");
  f_M = eeprom_read_int(0);
  f_K = eeprom_read_int(2);
  f_H = eeprom_read_int(4);

  if (f_M < 1 || f_M > 99)
    f_M = 1;
  if (f_K < 1 || f_K > 999)
    f_K = 1;
  if (f_H < 1 || f_H > 999)
    f_H = 1;

  Serial.println(f_M);
  Serial.println(f_K);
  Serial.println(f_H);

  si5351_setup();
}

String _format_int_to_str(int data, int len) {
  String result = String(data);
  while (result.length() < len) {
    result = "0" + result;
  }
  return result;
}


String synth_get() {
  String f_M_s = _format_int_to_str(f_M, 2);
  String f_K_s = _format_int_to_str(f_K, 3);
  String f_H_s = _format_int_to_str(f_H, 3);
  String result = f_M_s + "." + f_K_s + "." + f_H_s;
  return result;
}

void synth_save() {
  eeprom_write(0, f_M);
  eeprom_write(2, f_K);
  eeprom_write(4, f_H);
}

void synth_adjust(int incdec, int cursor_position) {
  switch (cursor_position) {
    // case 0: f_M += 100 * incdec; break;
    case 0: f_M += 10 * incdec; break;
    case 1: f_M += incdec; break;
    case 3: f_K += 100 * incdec; break;
    case 4: f_K += 10 * incdec; break;
    case 5: f_K += incdec; break;
    case 7: f_H += 100 * incdec; break;
    case 8: f_H += 10 * incdec; break;
    case 9: f_H += incdec; break;
  }

  if (f_M > 99) {
    f_M = 99;
  }
  if (f_M < 0)
    f_M = 0;

  if (f_K > 999) {
    f_K = 0;
    f_M++;
  }
  if (f_K < 0) {
    f_K = 0;
    f_M--;
  }
  if (f_H > 999) {
    f_H = 0;
    f_K++;
  }
  if (f_H < 0) {
    f_H = 0;
    f_K--;
  }

  si5351_adjustF(f_M, f_K, f_H);
}

void synth_enable(char enable) {
  si5351.output_enable(SI5351_CLK1, enable != '0');
}
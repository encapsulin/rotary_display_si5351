#include "rotary.h"
#include <Arduino.h>
// Определяем пины
const int pinCLK = 2;
const int pinDT = 3;
const int pinKey = 4;

// Переменные для счета (volatile обязателен для переменных в прерываниях)
volatile int vi_counter = 0;
int lastCounterValue = 0;

int rotary_direction = 0;
int rotary_position = 0;

// Функция-обработчик прерывания
void intUpdateEncoder1() {
  // Считываем текущие состояния
  int clkState = digitalRead(pinCLK);
  int dtState = digitalRead(pinDT);

  // Алгоритм определения направления
  if (clkState != dtState) {
    vi_counter++;
  } else {
    vi_counter--;
  }
}
void intUpdateEncoder() {
  static int lastCLK = LOW;
  int currentCLK = digitalRead(pinCLK);

  if (currentCLK == HIGH && lastCLK == LOW) {
    if (digitalRead(pinDT) != currentCLK) {
      vi_counter++;
    } else {
      vi_counter--;
    }
  }

  lastCLK = currentCLK;
}

// volatile int vi_rotary_key_press = 0;
// void intKeyPress() {
//   vi_rotary_key_press = 1;
// }

// int rotary_pressed1() {
//   static unsigned long lastPressTime = 0;
//   unsigned long now = millis();

//   if (vi_rotary_key_press && (now - lastPressTime > 500)) {
//     vi_rotary_key_press = 0;
//     lastPressTime = now;
//     return 1;
//   }

//   vi_rotary_key_press = 0;
//   return 0;
// }

int rotary_pressed() {
  uint8_t click = 0;
  while (digitalRead(pinKey) == LOW) {
    delay(100);
    click = 1;
  }

  return click;
}

int rotary_rotated() {
  // Выводим данные только если значение изменилось
  // int counter = vi_counter / 2;
  if (vi_counter != lastCounterValue) {

    rotary_direction = (vi_counter - lastCounterValue) > 0 ? -1 : 1;

    lastCounterValue = vi_counter;
    return 1;
  }
  return 0;
}

void rotary_setup() {
  pinMode(pinCLK, INPUT_PULLUP);
  pinMode(pinDT, INPUT_PULLUP);
  // Настраиваем прерывание: при изменении сигнала (CHANGE) на пине CLK
  // вызывается функция updateEncoder
  attachInterrupt(digitalPinToInterrupt(pinCLK), intUpdateEncoder, CHANGE);

  pinMode(pinKey, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(pinKey), intKeyPress, FALLING);
}

int rotary_get_direction() {
  //Serial.print("rotary_get_direction()");
  Serial.println(rotary_direction);
  return rotary_direction;
}
int rotary_get_position() {
  // Serial.print("rotary_get_position()");
  Serial.print(rotary_position);
  return rotary_position;
}

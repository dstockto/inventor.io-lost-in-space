#include <Arduino.h>

// Define input and output pins
int inputPins[] = {4, 3, 2};
int outputPins[] = {13, 12, 11, 10, 9, 8, 7};
int delayTime = 25; // Delay in milliseconds
int mode = 0;

void setup() {
  // Initialize input pins
  for (int i = 0; i < sizeof(inputPins) / sizeof(inputPins[0]); i++) {
    pinMode(inputPins[i], INPUT);
  }

  // Initialize output pins
  for (int i = 0; i < sizeof(outputPins) / sizeof(outputPins[0]); i++) {
    pinMode(outputPins[i], OUTPUT);
  }
}

int calcPins() {
  int pinVal = 1;
  int total = 0;
  for (int i = 0; i < sizeof(inputPins) / sizeof(inputPins[0]); i++) {
    if (digitalRead(inputPins[i]) == HIGH) {
      total += pinVal;
    }
    pinVal *= 2;
  }
  return total;
}

void loop() {
  
  int loops = 0;

  // Main loop
  while (true) {
    int value = calcPins();
    if (value != 0) {
      switch (mode) {
        case 0:
          animatePins(value);
          break;
        case 1:
          bounce(value);
          break;
        case 2:
          backBounce(value);
          break;
        case 3:
          outIn(value);
          break;
        case 4:
          inOut(value);
          break;
      }
    } else {
      delay(100);
    }

    loops++;
    if (loops % 10 == 0) {
      mode = (mode + 1) % 5;
      Serial.print("Mode: ");
      Serial.println(mode);
    }
    delay(8 * delayTime);
  }
}

void animatePins(int value) {
  for (int i = 0; i < value; i++) {
    digitalWrite(outputPins[i], HIGH);
    delay(delayTime);
  }

  for (int i = 0; i < value; i++) {
    digitalWrite(outputPins[i], LOW);
    delay(delayTime);
  }
}

void bounce(int value) {
  for (int i = 0; i < value; i++) {
    digitalWrite(outputPins[i], HIGH);
    delay(delayTime / 2);
  }

  for (int i = value - 1; i >= 0; i--) {
    digitalWrite(outputPins[i], LOW);
    delay(delayTime / 2);
  }
}

void backBounce(int value) {
  for (int i = value - 1; i >= 0; i--) {
    digitalWrite(outputPins[i], HIGH);
    delay(delayTime / 2);
  }
  
  for (int i = 0; i < value; i++) {
    digitalWrite(outputPins[i], LOW);
    delay(delayTime / 2);
  }
}

void outIn(int value) {
  for (int i = 0; i < value / 2 + 1; i++) {
    int left = i;
    int right = value - i - 1;
    digitalWrite(outputPins[left], HIGH);
    digitalWrite(outputPins[right], HIGH);
    delay(2 * delayTime);
  }

  for (int i = 0; i < value / 2 + 1; i++) {
    int left = i;
    int right = value - i - 1;
    digitalWrite(outputPins[left], LOW);
    digitalWrite(outputPins[right], LOW);
    delay(delayTime);
  }
}

void inOut(int value) {
  for (int i = 0; i <= (value - 1) / 2; i++) {
    int left = (value - 1) / 2 - i;
    int right = value / 2 + i;
    digitalWrite(outputPins[left], HIGH);
    digitalWrite(outputPins[right], HIGH);
    delay(delayTime);
  }

  for (int i = 0; i <= (value - 1) / 2; i++) {
    int left = (value - 1) / 2 - i;
    int right = value / 2 + i;
    digitalWrite(outputPins[left], LOW);
    digitalWrite(outputPins[right], LOW);
    delay(delayTime);
  }
}
const byte SWITCH_PIN_1 = 4;
const byte SWITCH_PIN_2 = 3;
const byte SWITCH_PIN_3 = 2;

const byte LED_1_PIN = 13;
const byte LED_2_PIN = 12;
const byte LED_3_PIN = 11;
const byte LED_4_PIN = 10;
const byte LED_5_PIN = 9;
const byte LED_6_PIN = 8;
const byte LED_7_PIN = 7;

const byte IN_PINS[] = { SWITCH_PIN_1, SWITCH_PIN_2, SWITCH_PIN_3 };
const byte OUT_PINS[] = { LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN, LED_5_PIN, LED_6_PIN, LED_7_PIN };
const int DELAY_TIME = 50;


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < sizeof(IN_PINS); i++) {
    pinMode(IN_PINS[i], INPUT);
  }
  for (int i = 0; i < sizeof(OUT_PINS); i++) {
    pinMode(OUT_PINS[i], OUTPUT);
  }

  Serial.begin(115200);
}

void animateLEDs(int count) {
  // Light up LEDs in sequence
  for (int i = 0; i < count; i++) {
    digitalWrite(OUT_PINS[i], HIGH);
    delay(DELAY_TIME);
  }

  // Turn off LEDs in the same order
  for (int i = 0; i < count; i++) {
    digitalWrite(OUT_PINS[i], LOW);
    delay(DELAY_TIME);
  }
}


int calcPins() {
  int total = 0;
  int switchVal = 1;
  for (int i = 0; i < sizeof(IN_PINS) / sizeof(IN_PINS[0]); i++) {
    if (digitalRead(IN_PINS[i]) == HIGH) {
      total += switchVal;
    }
    switchVal *= 2;
  }

  return total;  // Return the total directly
}

void loop() {
  int switchVal = calcPins();
  animateLEDs(switchVal);

  delay(DELAY_TIME * 2);
}
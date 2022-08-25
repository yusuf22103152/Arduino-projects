#include <IRremote.h> //include the library
uint32_t Previous,
         trigCode = 0xA90,
         blinkCode = 0,
         onCode = 0x2F0,
         offCode = 0xAF0,
         rightCode = 0xCD0,
         leftCode = 0x2D0;

const int sensor = 2,
          buzzer = 3,
          indicator = 4,
          relay = 5,
          IR = 6;

String mode = "underControl";

IRrecv receiver(IR);
decode_results results;

int stayOnDelay = 15000,
    stayOffDelay = 1000,
    buzBreak = 150,
    blinkDelay = 1000,
    motion;

boolean RCmode = false,
        ligthIsOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(indicator, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(indicator, HIGH);
  receiver.enableIRIn(); //start the receiver


}

void motionDetector() {
  motion = digitalRead(sensor);
  if (motion == HIGH) {
    digitalWrite(relay, HIGH);
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 5; j++) {
        buzzerEffect();
      }
      motion = digitalRead(sensor);
      if (motion == HIGH) {
        i = 0;
      }
      delay(stayOnDelay / 10);
      process();
      if (mode != "motion") {
        break;
      }
    }
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
  }
}

void RC() {
  if (receiver.results.value == onCode) {
    digitalWrite(relay, HIGH);
  }
  else if (receiver.results.value == offCode) {
    digitalWrite(relay, LOW);
  }

}

void blinkMode() {
  digitalWrite(relay, HIGH);
  delay(blinkDelay);
  digitalWrite(relay, LOW);
  delay(blinkDelay);
}

void buzzerEffect() {
  digitalWrite(indicator, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(buzBreak);
  digitalWrite(buzzer, LOW);
  delay(buzBreak);

}

void process() {
  if (mode == "motion") {
    digitalWrite(indicator, LOW);
    motionDetector();
  }
  else if (mode == "blinker") {
    blinkMode();
  }

  if (receiver.decode(&results)) {
    if (receiver.results.value == 0xFFFFFFFF) {
      receiver.results.value = Previous;
    }
    if (receiver.results.value == rightCode) {
      if (blinkDelay <= 5000) {
        blinkDelay += 200;
      }
    }
    else if (receiver.results.value == leftCode) {
      if (blinkDelay >= 500) {
        blinkDelay -= 200;
      }
    }
    if (receiver.results.value == trigCode) {
      if (mode == "motion") {
        digitalWrite(sensor, LOW);
        digitalWrite(indicator, HIGH);
        mode = "underControl";
      }
      else if (mode == "underControl") {
        digitalWrite(sensor, LOW);
        for (int i = 0; i < 10; i++) {
          digitalWrite(indicator, HIGH);
          delay(200);
          digitalWrite(indicator, LOW);
          delay(200);
        }
        mode = "blinker";
      }
      else if (mode == "blinker") {
        digitalWrite(indicator, LOW);
        mode = "motion";
      }
      delay(500);
    }
    if (mode == "underControl") {
      RC();
    }
    receiver.resume(); //next value
    Previous = receiver.results.value;

    Serial.println (receiver.results.value, HEX); //display HEX results
    Serial.println(mode);


  }


}

void loop() {
  process();

}
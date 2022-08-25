#include <IRremote.h>
uint32_t Previous,
         trigCode = 0xA90,
         onCode = 0x2F0,
         offCode = 0xAF0;

const int sensor = 2,
          buzzer = 3,
          indicator = 4,
          relay = 5,
          IR = 6
          stayOnDelay = 15000,
          stayOffDelay = 1000,
          buzBreak = 150,
          blinkDelay = 1000;

IRrecv receiver(IR);
decode_results results;

int motion;

boolean RCmode = false;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(indicator, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(indicator, HIGH);
  receiver.enableIRIn();

}

void motionDetector() {
  motion = digitalRead(sensor);
  if (motion == HIGH) {
    digitalWrite(relay, HIGH);
    for (int i = 0; i < 10; i++) {
      buzzerEffect();
      motion = digitalRead(sensor);
      if (motion == HIGH) {
        i = 0;
      }
      delay(stayOnDelay / 10);
      process();
      if (RCmode == true) {
        break;
      }
    }
  }
  else {
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
  }
}

void buzzerEffect() {
  digitalWrite(indicator, HIGH);
  for (int j=0;j<5;j++) {
  digitalWrite(buzzer, HIGH);
  delay(buzBreak);
  digitalWrite(buzzer, LOW);
  delay(buzBreak);}

}
  

void loop() {
  if (RCmode == false) {
    digitalWrite(indicator, LOW);
    motionDetector();
  }
  

  if (receiver.decode(&results)) {
    if (receiver.results.value == 0xFFFFFFFF) {
      receiver.results.value = Previous;
    }
    if (receiver.results.value == trigCode) {
      if (RCmode==false) {
        digitalWrite(sensor, LOW);
        digitalWrite(indicator, HIGH);
        RCmode=true;
      }

      else {
        digitalWrite(indicator, LOW);
        RCmode = true;
      }
      delay(500);
    }
    else if (receiver.results.value == onCode) {
    digitalWrite(relay, HIGH);
  }
  else if (receiver.results.value == offCode) {
    digitalWrite(relay, LOW);
  }
receiver.resume(); //next value
    Previous = receiver.results.value;
    
    }
    

    Serial.println (receiver.results.value, HEX); //display HEX results
    Serial.println(mode);


  }


}


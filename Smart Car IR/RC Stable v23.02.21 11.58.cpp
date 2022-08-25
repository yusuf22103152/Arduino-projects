#include <IRremote.h>
uint32_t Previous,
         trigCode = 0xA90,
         rightCode = 0xCD0,
         leftCode = 0x2D0,
         upCode = 0x2F0,
         downCode = 0xAF0,
         spinCodeC = 0x610,
         nutralCode = 0xA70,
         blinkerCode = 0x410,
         zzCode = 0x10,
         spinCodeCC = 0x110,
         increment = 0x810,
         decrement = 0xE10;

uint8_t RLed = A0,
        GLed = A1,
        BLed = A2,
        YLed = A3;

const int wRfor = 2,
          wRrev = 3,
          wLfor = 5,
          wLrev = 4,

          IRSensor = 8,
          indicator = 9,
          IR = 12,

          zigDelay = 500,
          restFor = 300,
          safeDis = 12;


IRrecv receiver(IR);
decode_results results;

int sensorAct,
    holdFor = 160,
    animSD = 120; // anim Switch Delay


boolean RCmode = true, senSt = false, batterySaver = false, zzMode = false, blinkerMode = false;

void setup() {
  //Motors
  pinMode(wRfor, OUTPUT);
  pinMode(wRrev, OUTPUT);
  pinMode(wLfor, OUTPUT);
  pinMode(wLrev, OUTPUT);

  //IR sensor
  pinMode (IRSensor, INPUT); // sensor pin INPUT
  Serial.begin(9600);
  receiver.enableIRIn(); //start the receiver

  //Instructions
  launchAnim();
  analogWrite(YLed, 255);
}

void blinker() {
  for (int l = 0; l < 5; l++) {
    launchAnim();
  }
  for (int m = 0; m < 5; m++) {
    anim1();
  }
  for (int n = 0; n < 5; n++) {
    anim2();
  }
}

void falseEach() {
  zzMode = false;
  blinkerMode = false;
}

void ZigZag() {
  accelerate();
  delay(zigDelay);
  nutral();
  rot90c();
  accelerate();
  delay(zigDelay);
  nutral();
  rot90cc();
}

void flash() {
  for (int k = 0; k < 2; k++) {
    analogWrite(BLed, 255);
    delay(animSD);
    digitalWrite(BLed, LOW);
    delay(animSD);
  }
}

void defStats() {
  sensorAct = digitalRead (IRSensor);
  if (sensorAct == 0) {
    senSt = true;
  }
  else
  {
    senSt = false;
  }

}

void lightsOff() {
  digitalWrite(RLed, LOW);
  digitalWrite(GLed, LOW);
  digitalWrite(BLed, LOW);
  digitalWrite(YLed, LOW);
}

void anim1() {
  analogWrite(RLed, 255);
  analogWrite(BLed, 255);
  delay(animSD);
  digitalWrite(RLed, LOW);
  digitalWrite(BLed, LOW);
  analogWrite(GLed, 255);
  analogWrite(YLed, 255);
  delay(animSD);
  digitalWrite(GLed, LOW);
  digitalWrite(YLed, LOW);
}

void anim2() {
  analogWrite(RLed, 255);
  delay(animSD);
  digitalWrite(RLed, LOW);
  analogWrite(GLed, 255);
  delay(animSD);
  digitalWrite(GLed, LOW);
  analogWrite(BLed, 255);
  delay(animSD);
  digitalWrite(BLed, LOW);
  analogWrite(YLed, 255);
  delay(animSD);
  digitalWrite(YLed, LOW);

}

void launchAnim() {
  analogWrite(RLed, 255);
  delay(animSD);
  digitalWrite(RLed, LOW);
  analogWrite(GLed, 255);
  delay(animSD);
  digitalWrite(GLed, LOW);
  analogWrite(BLed, 255);
  delay(animSD);
  digitalWrite(BLed, LOW);
  analogWrite(YLed, 255);
  delay(animSD);
  digitalWrite(YLed, LOW);
  analogWrite(BLed, 255);
  delay(animSD);
  digitalWrite(BLed, LOW);
  analogWrite(GLed, 255);
  delay(animSD);
  digitalWrite(GLed, LOW);
}

void nutral() {
  lightsOff();
  analogWrite(YLed, 255);
  digitalWrite(wRfor, LOW);
  digitalWrite(wLfor, LOW);
  digitalWrite(wRrev, LOW);
  digitalWrite(wLrev, LOW);
  delay(restFor);
}

void accelerate() {
  lightsOff();
  analogWrite(GLed, 255);
  digitalWrite(wRfor, HIGH);
  digitalWrite(wLfor, HIGH);
}

void reverse() {
  lightsOff();
  analogWrite(RLed, 255);
  analogWrite(wRrev, 255);
  analogWrite(wLrev, 255);
}

void rot90c() {
  lightsOff();
  analogWrite(BLed, 255);
  digitalWrite(wRrev, HIGH);
  digitalWrite(wLfor, HIGH);
  delay(holdFor);
  nutral();
}

void rot90cc() {
  lightsOff();
  analogWrite(BLed, 255);
  digitalWrite(wRfor, HIGH);
  digitalWrite(wLrev, HIGH);
  delay(holdFor);
  nutral();
}

void spinc() {
  digitalWrite(wRrev, HIGH);
  digitalWrite(wLfor, HIGH);
}

void spincc() {
  digitalWrite(wLrev, HIGH);
  digitalWrite(wRfor, HIGH);
}

void underControl() {
  if (Previous == increment) {
    flash();
    if (holdFor <= 500) {
      holdFor += 20;
    }
    if (blinkerMode == true && animSD <= 500) {
      animSD += 20;
    }
  }

  else if (Previous == decrement) {
    flash();
    if (holdFor >= 60) {
      holdFor -= 20;
    }
    if (blinkerMode == true && animSD >= 60) {
      animSD -= 20;
    }
  }

  else if (Previous == rightCode) {
    rot90c();
  }
  else if (Previous == leftCode) {
    rot90cc();
  }
  else if (Previous == upCode) {
    accelerate();
  }
  else if (Previous == downCode) {
    reverse();
  }
  else if (Previous == nutralCode) {
    falseEach();
    nutral();
  }
  else if (Previous == spinCodeC) {
    nutral();
    falseEach();
    flash();
    spinc();
  }
  else if (Previous == spinCodeCC) {
    nutral();
    falseEach();
    flash();
    spincc();
  }
  else if (Previous == zzCode) {
    nutral();
    falseEach();
    flash();
    zzMode = true;
  }
  else if (Previous == blinkerCode) {
    nutral();
    falseEach();
    flash();
    blinkerMode = true;
  }

}

void loop() {

  if (RCmode == false) {
    defStats();
    if (senSt == true) {
      nutral();
      flash();
      reverse();
      delay(250);
      nutral();
      rot90c();
    }
    else {
      accelerate();
    }
  }

  else if (zzMode == true) {
    ZigZag();
  }
  else if (blinkerMode == true) {
    blinker();

  }

  if (receiver.decode(&results)) {
    if (receiver.results.value == 0xFFFFFFFF) {
      receiver.results.value = Previous;
    }
    Previous = receiver.results.value;
    if (Previous == trigCode) {
      if (RCmode == false) {
        lightsOff();
        analogWrite(YLed, 255);
        RCmode = true;
      }
      else {
        RCmode = false;
      }
      nutral();
      falseEach();
      animSD=120;
      for (int i = 0; i < 4; i++) {
        launchAnim();
      }
    }
    if (RCmode == true) {
      underControl();
    }

    receiver.resume(); //next value
    Previous = receiver.results.value;

    Serial.println (receiver.results.value, HEX); //display HEX results
    Serial.println(RCmode);

    delay(200);

  }
}
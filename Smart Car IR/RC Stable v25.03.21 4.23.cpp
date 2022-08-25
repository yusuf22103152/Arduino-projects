#include <IRremote.h>
uint32_t Previous,
         trigCode = 0xA90,
         trigCodeS = 0x40BFA05F,

         rightCode = 0xCD0,
         rightCodeS = 0x40BF20DF,

         leftCode = 0x2D0,
         leftCodeS = 0x40BFE21D,

         upCode = 0x2F0,
         upCodeS = 0x40BF12ED,

         downCode = 0xAF0,
         downCodeS = 0x40BF02FD,

         spinCodeC = 0x610,
         spinCodeCS = 0x40BF58A7,

         nutralCode = 0xA70,
         nutralCodeS = 0xA70,

         blinkerCode = 0x410,
         blinkerCodeS = 0x40BF7887,

         zzCode = 0x10,
         zzCodeS = 0x40BF50AF,

         spinCodeCC = 0x110,
         spinCodeCCS = 0x40BF5AA5,

         increment = 0x810,
         incrementS = 0x40BFBA45,

         decrement = 0xE10,
         decrementS = 0x40BF9A65;

long duration;

uint8_t RLed = A0,
        GLed = A1,
        BLed = A2,
        YLed = A3;

const int wRfor = 2,
          wRrev = 3,
          wLfor = 5,
          wLrev = 4,

          trig = 8,
          echo = 9,
          IR = 12,
          LWval = 230, //Left wheel analog value

          zigDelay = 500,
          restFor = 300;


IRrecv receiver(IR);
decode_results results;

int sensorAct,
    objDis,
    check365 = 0,
    holdFor = 180,
    animSD = 120; // anim Switch Delay


boolean RCmode = true, senSt = false, batterySaver = false, zzMode = false, blinkerMode = false;

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
void throwSignal() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
}

void convert() {
  //It will convert the signal duration into inches
  objDis = (duration / 2) / (29.1 * 2.54);
}

void defStats() {
  //Define status - It will define if the car have to stop or run
  throwSignal();
  convert();
  if (objDis <= 10 || check365 > 30) {
    senSt = 1;
    check365 = 0;
  }
  else if (objDis == 365) {
    senSt = 0;
    check365 += 1;
  }
  else if (objDis > 10) {
    senSt = 0;
    check365 = 0;
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
  analogWrite(wLfor, LWval);
}

void reverse() {
  lightsOff();
  analogWrite(RLed, 255);
  analogWrite(wRrev, 255);
  analogWrite(wLrev, LWval);
}

void rot90c() {
  lightsOff();
  analogWrite(BLed, 255);
  digitalWrite(wRrev, HIGH);
  analogWrite(wLfor, LWval);
  delay(holdFor);
  nutral();
}

void rot90cc() {
  lightsOff();
  analogWrite(BLed, 255);
  digitalWrite(wRfor, HIGH);
  analogWrite(wLrev, LWval);
  delay(holdFor);
  nutral();
}

void spinc() {
  digitalWrite(wRrev, HIGH);
  analogWrite(wLfor, LWval);
}

void spincc() {
  digitalWrite(wLrev, HIGH);
  analogWrite(wRfor, LWval);
}


void blinker() {
  for (int l = 0; l < 4; l++) {
    launchAnim();
  }
  for (int m = 0; m < 4; m++) {
    anim1();
  }
  for (int n = 0; n < 4; n++) {
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



void underControl() {
  if (Previous == increment || Previous == incrementS) {
    flash();
    if (holdFor <= 500) {
      holdFor += 20;
    }
    if (blinkerMode == true && animSD <= 500) {
      animSD += 20;
    }
  }

  else if (Previous == decrement || Previous == decrementS) {
    flash();
    if (holdFor >= 60) {
      holdFor -= 20;
    }
    if (blinkerMode == true && animSD >= 60) {
      animSD -= 20;
    }
  }

  else if (Previous == rightCode || Previous == rightCodeS) {
    rot90c();
  }
  else if (Previous == leftCode || Previous == leftCodeS
          ) {
    rot90cc();
  }
  else if (Previous == upCode || Previous == upCodeS) {
    accelerate();
  }
  else if (Previous == downCode || Previous == downCodeS) {
    reverse();
  }
  else if (Previous == nutralCode || Previous == nutralCodeS) {
    falseEach();
    nutral();
  }
  else if (Previous == spinCodeC || Previous == spinCodeCS) {
    nutral();
    falseEach();
    flash();
    spinc();
  }
  else if (Previous == spinCodeCC || Previous == spinCodeCCS) {
    nutral();
    falseEach();
    flash();
    spincc();
  }
  else if (Previous == zzCode || Previous == zzCodeS) {
    nutral();
    falseEach();
    flash();
    zzMode = true;
  }
  else if (Previous == blinkerCode || Previous == blinkerCodeS) {
    nutral();
    falseEach();
    flash();
    blinkerMode = true;
  }

}




void setup() {
  //Motors
  pinMode(wRfor, OUTPUT);
  pinMode(wRrev, OUTPUT);
  pinMode(wLfor, OUTPUT);
  pinMode(wLrev, OUTPUT);

  //IR sensor
  pinMode (echo, INPUT);
  pinMode (trig, OUTPUT);
  Serial.begin(9600);
  receiver.enableIRIn(); //start the receiver

  //Instructions
  for (int o = 0; o < 5; o++) {
    launchAnim();
  }
  analogWrite(YLed, 255);
}


void loop() {

  if (RCmode == false) {
    defStats();
    if (senSt == true) {
      nutral();
      flash();
      reverse();
      delay(350);
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
    if (Previous == trigCode || Previous == trigCodeS) {
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
      animSD = 120;
      for (int i = 0; i < 3; i++) {
        launchAnim();
      }
    }
    if (RCmode == true) {
      underControl();
    }

    receiver.resume(); //next value
    Previous = receiver.results.value;

    Serial.println (receiver.results.value, HEX); //display HEX results
    delay(200);
  }
  Serial.println(objDis);

}
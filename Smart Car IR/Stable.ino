#include <IRremote.h>

uint32_t Previous,

//no extra letter = Mi8SE, M= mini remote,S=Siam's phone


         //Power button
         trigCode = 0xA90,
         trigCodeM = 0xFFA25D,
         trigCodeS = 0x40BFA05F,

         rightCode = 0xCD0,
         rightCodeM = 0xFFA857,
         rightCodeS = 0x40BF20DF,

         leftCode = 0x2D0,
         leftCodeM = 0xFFE01F,
         leftCodeS = 0x40BFE21D,

         upCode = 0x2F0,
         upCodeM = 0xFF906F,
         upCodeS = 0x40BF12ED,

         downCode = 0xAF0,
         downCodeM = 0xFF02FD,
         downCodeS = 0x40BF02FD,

         //Seven
         spinCodeC = 0x610,
         spinCodeCM = 0xFF42BD,
         spinCodeCS = 0x40BF58A7,

         //Ok
         nutralCode = 0xA70,
         nutralCodeM = 0xFF38C7,
         nutralCodeS = 0xA70,

         //Three
         blinkerCode = 0x410,
         blinkerCodeM = 0xFF7A85,
         blinkerCodeS = 0x40BF7887,

         //One
         zzCode = 0x10,
         zzCodeM = 0xFF30CF,
         zzCodeS = 0x40BF50AF,

         //Nine
         spinCodeCC = 0x110,
         spinCodeCCM = 0xFF52AD,
         spinCodeCCS = 0x40BF5AA5,

         //Vol+
         increment = 0x490,
         incrementM = 0xFF9867,
         incrementS = 0x40BFBA45,

         //Vol-
         decrement = 0xC90,
         decrementM = 0xFF6897,
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
          RwVal = 200,  //Right wheel analog value - ex value 225

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
  digitalWrite(RLed, HIGH);
  delay(animSD);
  digitalWrite(RLed, LOW);
  digitalWrite(GLed, HIGH);
  delay(animSD);
  digitalWrite(GLed, LOW);
  digitalWrite(BLed, HIGH);
  delay(animSD);
  digitalWrite(BLed, LOW);
  digitalWrite(YLed, HIGH);
  delay(animSD);
  digitalWrite(YLed, LOW);
  digitalWrite(BLed, HIGH);
  delay(animSD);
  digitalWrite(BLed, LOW);
  digitalWrite(GLed, HIGH);
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
bool gotCode(uint32_t code1=0, uint32_t code2=0,uint32_t code3=0) {
  if (Previous == code1 || Previous == code2 || Previous == code3) {
    return true;
  }
  else {
    return false;
  }
}

void convert() {
  //It will convert the signal duration into inches
  objDis = (duration / 2) / (29.1 * 2.54);
}

void defStats() {
  //Define status - It will define if the car have to stop or run
  throwSignal();
  convert();
  if (objDis <= 6 || check365 > 30) {
    senSt = 1;
    check365 = 0;
  }
  else if (objDis == 365) {
    senSt = 0;
    check365 += 1;
  }
  else if (objDis > 6) {
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
  digitalWrite(RLed, HIGH);
  digitalWrite(BLed, HIGH);
  delay(animSD);
  digitalWrite(RLed, LOW);
  digitalWrite(BLed, LOW);
  digitalWrite(GLed, HIGH);
  digitalWrite(YLed, HIGH);
  delay(animSD);
  digitalWrite(GLed, LOW);
  digitalWrite(YLed, LOW);
}

void anim2() {
  digitalWrite(RLed, HIGH);
  delay(animSD);
  digitalWrite(RLed, LOW);
  digitalWrite(GLed, HIGH);
  delay(animSD);
  digitalWrite(GLed, LOW);
  digitalWrite(BLed, HIGH);
  delay(animSD);
  digitalWrite(BLed, LOW);
  digitalWrite(YLed, HIGH);
  delay(animSD);
  digitalWrite(YLed, LOW);

}

void nutral() {
  lightsOff();
  digitalWrite(YLed, HIGH);
  digitalWrite(wRfor, LOW);
  digitalWrite(wLfor, LOW);
  digitalWrite(wRrev, LOW);
  digitalWrite(wLrev, LOW);
  delay(restFor);
}

void accelerate() {
  lightsOff();
  digitalWrite(GLed, HIGH);
  digitalWrite(wRfor, HIGH);
  digitalWrite(wLfor, HIGH);

}

void reverse() {
  lightsOff();
  digitalWrite(RLed, HIGH);
  digitalWrite(wRrev, HIGH);
  digitalWrite(wLrev, HIGH);
}

void rot90c() {
  lightsOff();
  digitalWrite(BLed, HIGH);
  digitalWrite(wRrev, HIGH);
  digitalWrite(wLfor, HIGH);
  delay(holdFor);
  nutral();
}

void rot90cc() {
  lightsOff();
  digitalWrite(BLed, HIGH);
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

void flash(int led) {
  for (int k = 0; k < 2; k++) {
    digitalWrite(led, HIGH);
    delay(animSD);
    digitalWrite(led, LOW);
    delay(animSD);
  }
}
void flashAll() {
  digitalWrite(YLed, HIGH);
  digitalWrite(BLed, HIGH);
  digitalWrite(GLed, HIGH);
  digitalWrite(RLed, HIGH);
  delay(250);
  digitalWrite(YLed, LOW);
  digitalWrite(BLed, LOW);
  digitalWrite(GLed, LOW);
  digitalWrite(RLed, LOW);
  delay(250);
}


void underControl() {
  if (gotCode(increment,incrementM,incrementS)) {
    flash(GLed);
    if (blinkerMode == true && animSD <= 500) {
      animSD += 20;
    }
    else if (holdFor <= 500) {
      holdFor += 20;
    }
  }

  else if (gotCode(decrement,decrementM,decrementS)) {
    flash(RLed);
    if (blinkerMode == true && animSD >= 60) {
      animSD -= 20;
    }
    else if (holdFor >= 60) {
      holdFor -= 20;
    }
  }
  else if (gotCode(rightCode,rightCodeM,rightCodeS)) {
    rot90c();
  }
  else if (gotCode(leftCode,leftCodeM,leftCodeS)) {
    rot90cc();
  }
  else if (gotCode(upCode,upCodeM,upCodeS)) {
    accelerate();
  }
  else if (gotCode(downCode,downCodeM,downCodeS)) {
    reverse();
  }
  else if (gotCode(nutralCode,nutralCodeM,nutralCodeS)) {
    falseEach();
    nutral();
  }
  else if (gotCode(spinCodeC,spinCodeCM,spinCodeCS)) {
    nutral();
    falseEach();
    flash(BLed);
    spinc();
  }
  else if (gotCode(spinCodeCC,spinCodeCCM,spinCodeCCS)) {
    nutral();
    falseEach();
    flash(BLed);
    spincc();
  }
  else if (gotCode(zzCode,zzCodeM,zzCodeS)) {
    nutral();
    falseEach();
    flash(BLed);
    zzMode = true;
  }
  else if (gotCode(blinkerCode,blinkerCodeM,blinkerCodeS)) {
    nutral();
    falseEach();
    flash(BLed);
    blinkerMode = true;
  }

}

void setup() {
  //Motors
  pinMode(wRfor, OUTPUT);
  pinMode(wRrev, OUTPUT);
  pinMode(wLfor, OUTPUT);
  pinMode(wLrev, OUTPUT);
  pinMode(RLed, OUTPUT);
  pinMode(GLed, OUTPUT);
  pinMode(BLed, OUTPUT);
  pinMode(YLed, OUTPUT);

  //IR sensor
  pinMode (echo, INPUT);
  pinMode (trig, OUTPUT);
  Serial.begin(9600);
  receiver.enableIRIn(); //start the receiver

  //Instructions
  for (int o = 0; o < 5; o++) {
    flashAll();
  }
  analogWrite(YLed, 255);
}


void loop() {

  if (RCmode == false) {
    defStats();
    if (senSt == true) {
      nutral();
      flash(BLed);
      reverse();
      delay(120);
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
    if (gotCode(trigCode,trigCodeM,trigCodeS)) {
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
      for (int i = 0; i < 2; i++) {
        flashAll();
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

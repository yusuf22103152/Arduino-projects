#include <IRremote.h>
const int RECV_PIN = 11;
uint32_t sentCode;

IRrecv irrecv(RECV_PIN);
decode_results results;

boolean rightIndic = false, leftIndic = false,allIsOn=false;
String mode = "aeroplane";

const int delayIntro = 100,
          delayTime = 100,
          whiteR = 3,
          whiteL = 8,
          blue = 4,
          green = 5,
          yellow = 6,
          red = 7,

          rearGreen = 9,
          rearRed = 10,
          buzzer = 12;

uint32_t powerCode = 0xFFA25D,
         stopCode = 0xFF629D,
         muteCode = 0xFFE21D,
         modeCode = 0xFF22DD,
         homeCode = 0xFF02FD,
         eqCode = 0xFFC23D,
         prevCode = 0xFFE01F,
         nextCode = 0xFFA857,
         forwardCode = 0xFF906F,
         leftCode = 0xFF6897,
         rightCode = 0xFF9867,
         zeroCode = 0xFFB04F,
         oneCode = 0xFF30CF,
         twoCode = 0xFF18E7,
         threeCode = 0xFF7A85,
         fourCode = 0xFF10EF,
         fiveCode = 0xFF38C7,
         sixCode = 0xFF5AA5,
         sevenCode = 0xFF42BD,
         eightCode = 0xFF4AB5,
         nineCode = 0xFF52AD;

void setup() {
  pinMode(whiteR, OUTPUT);
  pinMode(whiteL, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(rearGreen, OUTPUT);
  pinMode(rearRed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  irrecv.enableIRIn(); // Start the receiver
}

void on(int pin) {
  digitalWrite(pin, HIGH);
}

void off(int pin) {
  digitalWrite(pin, LOW);
}

void flash(int pin) {
  allOff();
  on(pin);
  delay(delayTime);
  off(pin);
  delay(delayTime);
  on(pin);
  delay(delayTime);
  off(pin);
  delay(delayTime);
}

void allOn() {
  on(whiteR);
  on(whiteL);
  on(blue);
  on(green);
  on(yellow);
  on(red);
  on(rearGreen);
  on(rearRed);
}
void allOff() {
  off(whiteR);
  off(whiteL);
  off(blue);
  off(green);
  off(yellow);
  off(red);
  off(rearGreen);
  off(rearRed);
}
void indicate(int pin1, int pin2, int pin3, int pin4) {
  for (int i = 0; i < 12; i++) {
    on(pin1);
    on(pin2);
    on(pin3);
    on(pin4);
    on(buzzer);
    delay(100);
    off(pin1);
    off(pin2);
    off(pin3);
    off(pin4);
    off(buzzer);
    delay(100);
  }
  rightIndic = false;
  leftIndic = false;
}


void easeIO() {
  on(whiteL);
  on(whiteR);
  delay(delayTime);
  on(red);
  on(blue);
  delay(delayTime);
  on(yellow);
  on(green);
  delay(delayTime);
  off(whiteL);
  off(whiteR);
  delay(delayTime);
  off(red);
  off(blue);
  delay(delayTime);
  off(yellow);
  off(green);
  delay(delayTime);
  on(green);
  on(yellow);
  delay(delayTime);
  on(blue);
  on(red);
  delay(delayTime);
  on(whiteR);
  on(whiteL);
  delay(delayTime);
  off(green);
  off(yellow);
  delay(delayTime);
  off(blue);
  off(red);
  delay(delayTime);
  off(whiteR);
  off(whiteL);
  delay(delayTime);
}

void startAnim() {
  on(whiteL);
  delay(delayIntro);
  on(red);
  delay(delayIntro);
  on(yellow);
  delay(delayIntro);
  on(green);
  delay(delayIntro);
  on(blue);
  delay(delayIntro);
  on(whiteR);
  delay(delayIntro);

  off(whiteL);
  delay(delayIntro);
  off(red);
  delay(delayIntro);
  off(yellow);
  delay(delayIntro);
  off(green);
  delay(delayIntro);
  off(blue);
  delay(delayIntro);
  off(whiteR);
  delay(delayIntro);

  on(whiteR);
  delay(delayIntro);
  on(blue);
  delay(delayIntro);
  on(green);
  delay(delayIntro);
  on(yellow);
  delay(delayIntro);
  on(red);
  delay(delayIntro);
  on(whiteL);
  delay(delayIntro);


  off(whiteR);
  delay(delayIntro);
  off(blue);
  delay(delayIntro);
  off(green);
  delay(delayIntro);
  off(yellow);
  delay(delayIntro);
  off(red);
  delay(delayIntro);
  off(whiteL);
  delay(delayIntro);
}

void aeroplane() {
  on(red);
  on(green);
  on(whiteL);
  on(whiteR);
  delay(100);
  off(whiteL);
  off(whiteR);
  delay(1000);
  on(yellow);
  delay(100);
  off(yellow);
  delay(200);
}
void cop() {
  on(red);
  delay(200);
  off(red);
  on(blue);
  delay(200);
  off(blue);
}
void copTorch() {
  on(whiteL);
  on(whiteR);
  cop();
}


void loop() {

  //Code receive section
  if (irrecv.decode(&results)) {
    Serial.println(irrecv.results.value, HEX);
    irrecv.resume();

    sentCode = irrecv.results.value;
    if (sentCode == rightCode) {
      rightIndic = true;
    }
    else if (sentCode == leftCode) {
      leftIndic = true;
    }
    else if (sentCode == oneCode) {
      flash(blue);
      mode = "aeroplane";
    }
    else if (sentCode == twoCode) {
      flash(blue);
      mode = "cop";
    }
    else if (sentCode == threeCode) {
      flash(blue);
      mode = "copTorch";
    }
    else if (sentCode == fourCode) {
      flash(blue);
      mode = "startAnim";
    }
    else if (sentCode == fiveCode) {
      flash(blue);
      mode = "easeIO";
    }
    else if (sentCode == powerCode) {
      flash(green);
      if (allIsOn) {
        mode = "allOn";
        allIsOn = false;
      }
      else {
        mode = "allOff";
        allIsOn=true;
      }
    }
  }

  // The task
  if (rightIndic) {
    indicate(whiteR, blue, green, rearGreen);
  }
  else if (leftIndic) {
    indicate(whiteL, yellow, red, rearRed);
  }


  if (mode == "aeroplane") {
    allOff();
    aeroplane();
  }
  else if (mode == "cop") {
    allOff();
    cop();
  }
  else if (mode == "copTorch") {
    allOff();
    copTorch();
  }
  else if (mode == "startAnim") {
    startAnim();
  }
  else if (mode == "easeIO") {
    allOff();
    easeIO();
  }
  else if (mode == "allOn") {
    allOn();
  }




}
#include <IRremote.h>
const int RECV_PIN = 11;
uint32_t sentCode;

IRrecv irrecv(RECV_PIN);
decode_results results;

boolean rightIndic = false, leftIndic = false,
        allIsOn = false,
        muted = false,
        whiteRIsOn = false, blueIsOn = false, greenIsOn = false, yellowIsOn = false, redIsOn = false, whiteLIsOn = false, rearGreenIsOn = false, rearRedIsOn = false;
String mode = "aeroplane";

/*            Tasks left
  Nahids mode - Complete
  Reset - Complete
  Include MI8SE - Complete
  Buzzer feature
  Increment decrement delay time
  Stop in a sudden
*/
const int
whiteR = 3,
whiteL = 8,
blue = 4,
green = 5,
yellow = 6,
red = 7,

rearGreen = 9,
rearRed = 10;

int delayTime = 100, buzzer = 12;

//Mini remote
uint32_t powerCode = 0xFFA25D,
         stopCode = 0xFF629D,
         muteCode = 0xFFE21D,
         modeCode = 0xFF22DD,
         resetCode = 0xFF02FD,
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


//Mi8SE remote
uint32_t powerCode8SE = 0xA90,
         homeCode8SE = 0x70,
         oneCode8SE = 0x10,
         twoCode8SE = 0x810,
         threeCode8SE = 0x410,
         fourCode8SE = 0xC10,
         fiveCode8SE = 0x210,
         sixCode8SE = 0xA10,
         sevenCode8SE = 0x610,
         eightCode8SE = 0xE10,
         nineCode8SE = 0x110,
         tenCode8SE = 0x910,

         okayCode8SE = 0xA70,
         topCode8SE = 0x2F0,
         rightCode8SE = 0xCD0,
         bottomCode8SE = 0xAF0,
         leftCode8SE = 0x2D0,

         volUpCode8SE = 0x490,
         VolDownCode8SE = 0xC90,

         ChUpCode8SE = 0x90,
         ChDownCode8SE = 0x890,

         muteCode8SE = 0x290,
         menuCode8SE = 0x70,
         resetCode8SE = 0x62E9,
         optOutCode8SE = 0xA50;

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
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void on(int pin) {
  digitalWrite(pin, HIGH);
}

void off(int pin) {
  digitalWrite(pin, LOW);
}

void flashReps(int pin1, int pin2, int reps) {
  for (int i = 0; i < reps; i++) {
    on(pin1);
    on(pin2);
    delay(delayTime);
    off(pin1);
    off(pin2);
    delay(delayTime);
  }
}
void flash(int pin) {
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
  off(buzzer);
}
void indicate(int pin1, int pin2, int pin3, int pin4) {
  for (int i = 0; i < 8; i++) {
    on(pin1);
    on(pin2);
    on(pin3);
    on(pin4);
    on(buzzer);
    delay(delayTime);
    off(pin1);
    off(pin2);
    off(pin3);
    off(pin4);
    off(buzzer);
    delay(delayTime);
  }
  rightIndic = false;
  leftIndic = false;
}
void aeroplane() {
  on(red);
  on(green);
  on(whiteL);
  on(whiteR);
  delay(delayTime);
  off(whiteL);
  off(whiteR);
  //Need a thousand milis gap. So lets use the time
  flashReps(rearGreen, rearRed, 5);
  //End of thousand milis gap.
  on(rearGreen);
  on(rearRed);
  on(yellow);
  delay(delayTime);
  off(yellow);
  delay(delayTime * 2);
}
void cop() {
  on(red);
  flashReps(rearGreen, rearRed, 1);
  off(red);
  on(blue);
  flashReps(rearGreen, rearRed, 1);
  off(blue);
}
void copTorch() {
  on(whiteL);
  on(whiteR);
  cop();
}

void startAnim() {
  on(whiteL);
  delay(delayTime);
  on(red);
  delay(delayTime);
  on(yellow);
  delay(delayTime);
  on(rearRed);
  delay(delayTime);
  on(rearGreen);
  delay(delayTime);
  on(green);
  delay(delayTime);
  on(blue);
  delay(delayTime);
  on(whiteR);
  delay(delayTime);

  off(whiteL);
  delay(delayTime);
  off(red);
  delay(delayTime);
  off(yellow);
  delay(delayTime);
  off(rearRed);
  delay(delayTime);
  off(rearGreen);
  delay(delayTime);
  off(green);
  delay(delayTime);
  off(blue);
  delay(delayTime);
  off(whiteR);
  delay(delayTime);

  on(whiteR);
  delay(delayTime);
  on(blue);
  delay(delayTime);
  on(green);
  delay(delayTime);
  on(rearGreen);
  delay(delayTime);
  on(rearRed);
  delay(delayTime);
  on(yellow);
  delay(delayTime);
  on(red);
  delay(delayTime);
  on(whiteL);
  delay(delayTime);


  off(whiteR);
  delay(delayTime);
  off(blue);
  delay(delayTime);
  off(green);
  delay(delayTime);
  off(rearGreen);
  delay(delayTime);
  off(rearRed);
  delay(delayTime);
  off(yellow);
  delay(delayTime);
  off(red);
  delay(delayTime);
  off(whiteL);
  delay(delayTime);
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
  on(rearRed);
  on(rearGreen);
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
  off(rearRed);
  off(rearGreen);
  delay(delayTime);
  on(rearRed);
  on(rearGreen);
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

void justBlink() {
  allOn();
  delay(delayTime);
  allOff();
  delay(delayTime);
}
void reset() {
  allOff();
  mode = "aeroplane";
  muted = "false";
  rightIndic = false;
  leftIndic = false;
  allIsOn = false;
  muted = false;
  whiteRIsOn = false;
  blueIsOn = false;
  greenIsOn = false;
  yellowIsOn = false;
  redIsOn = false;
  whiteLIsOn = false;
  rearGreenIsOn = false;
  rearRedIsOn = false;
}

bool gotCode(uint32_t remoteCode, uint32_t MI8SEcode) {
  if (sentCode == remoteCode || sentCode == MI8SEcode) {
    return true;
  }
  else {
    return false;
  }
}
void loop() {

  //Code receive section
  if (irrecv.decode(&results)) {
    sentCode = irrecv.results.value;
    if (gotCode(rightCode,rightCode8SE)) {
      rightIndic = true;
    }
    else if (gotCode(leftCode,leftCode8SE)) {
      leftIndic = true;
    }
    else if (gotCode(resetCode,resetCode8SE)) {
      reset();
    }
    else if (gotCode(muteCode,muteCode8SE)) {
      if (muted) {
        buzzer = 12;
        flash(green);
        flash(buzzer);
        muted = false;
      }
      else {
        flash(red);
        buzzer = 0;
        muted = true;
      }
    }


    else if (gotCode(nextCode,topCode8SE)) {
      allOff();
      flash(blue);
      if (mode == "aeroplane") {
        mode = "cop";
      }
      else if (mode == "cop") {
        mode = "copTorch";
      }
      else if (mode == "copTorch") {
        mode = "startAnim";
      }
      else if (mode == "startAnim") {
        mode = "easeIO";
      }
      else if (mode == "easeIO") {
        mode = "justBlink";
      }
      else if (mode == "justBlink") {
        mode = "aeroplane";
      }
      else {
        mode = "aeroplane";
      }
    }

    else if (gotCode(prevCode,bottomCode8SE)) {
      allOff();
      flash(red);
      if (mode == "aeroplane") {
        mode = "justBlink";
      }
      else if (mode == "justBlink") {
        mode = "easeIO";
      }
      else if (mode == "easeIO") {
        mode = "startAnim";
      }
      else if (mode == "startAnim") {
        mode = "copTorch";
      }
      else if (mode == "copTorch") {
        mode = "cop";
      }
      else if (mode == "cop") {
        mode = "aeroplane";
      }
      else {
        mode = "aeroplane";
      }
    }

    else if (gotCode(oneCode,oneCode8SE)) {
      flash(whiteR);
      mode = "null";
      if (whiteRIsOn) {
        off(whiteR);
        whiteRIsOn = false;
      }
      else {
        on(whiteR);
        whiteRIsOn = true;
      }
    }
    else if (gotCode(twoCode,twoCode8SE)) {
      flash(blue);
      mode = "null";
      if (blueIsOn) {
        off(blue);
        blueIsOn = false;
      }
      else {
        on(blue);
        blueIsOn = true;
      }
    }
    else if (gotCode(threeCode,threeCode8SE)) {
      flash(green);
      mode = "null";
      if (greenIsOn) {
        off(green);
        greenIsOn = false;
      }
      else {
        on(green);
        greenIsOn = true;
      }
    }
    else if (gotCode(fourCode,fourCode8SE)) {
      flash(yellow);
      mode = "null";
      if (yellowIsOn) {
        off(yellow);
        yellowIsOn = false;
      }
      else {
        on(yellow);
        yellowIsOn = true;
      }
    }
    else if (gotCode(fiveCode,fiveCode8SE)) {
      flash(red);
      mode = "null";
      if (redIsOn) {
        off(red);
        redIsOn = false;
      }
      else {
        on(red);
        redIsOn = true;
      }
    }
    else if (gotCode(sixCode,sixCode8SE)) {
      flash(whiteL);
      mode = "null";
      if (whiteLIsOn) {
        off(whiteL);
        whiteLIsOn = false;
      }
      else {
        on(whiteL);
        whiteLIsOn = true;
      }
    }
    else if (gotCode(sevenCode,sevenCode8SE)) {
      flash(rearGreen);
      mode = "null";
      if (rearGreenIsOn) {
        off(rearGreen);
        rearGreenIsOn = false;
      }
      else {
        on(rearGreen);
        rearGreenIsOn = true;
      }
    }
    else if (gotCode(eightCode,eightCode8SE)) {
      flash(rearRed);
      mode = "null";
      if (rearRedIsOn) {
        off(rearRed);
        rearRedIsOn = false;
      }
      else {
        on(rearRed);
        rearRedIsOn = true;
      }
    }
    else if (gotCode(powerCode,powerCode8SE)) {
      allOff();
      if (allIsOn) {
        flash(green);
        mode = "allOn";
        allIsOn = false;
      }
      else {
        flash(red);
        mode = "allOff";
        allIsOn = true;
      }
    }
    irrecv.resume();
    Serial.println(sentCode,HEX);
  }

  // The task
  if (rightIndic) {
    allOff();
    indicate(whiteR, blue, green, rearGreen);
  }
  else if (leftIndic) {
    allOff();
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
  else if (mode == "justBlink") {
    justBlink();
  }
  else if (mode == "allOn") {
    allOn();
  }
  else if (mode == "allOff") {
    allOff();
  }



}
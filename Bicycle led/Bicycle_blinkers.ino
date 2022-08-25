#include <IRremote.h>
const int RECV_PIN = 12;
uint32_t sentCode;

IRrecv irrecv(RECV_PIN);
decode_results results;

/*Highlights
  1. The maximum value of delayTime you can reach is 100 x 1.5^8 = 2562.890625 miliseconds
  2. The minimun value of delayTime you can reach is 100 ÷ 1.5^5 = 13.1687242798 miliseconds


*/


boolean allIsOn = false,
        muted = false,
        buzzerIsOn = false,
        whiteRIsOn = false, blueIsOn = false, greenIsOn = false, yellowIsOn = false, redIsOn = false, whiteLIsOn = false, rearGreenIsOn = false, rearRedIsOn = false;
String mode = "aeroplane";

/*            Tasks left
  Nahids mode - Complete
  Reset - Complete
  Include MI8SE - Complete
  Buzzer feature - Complete
  Increment decrement delay time - Complete
  Fuze mode - Complete
  Disable mini remote - Complete
  Shortcut mode by numbers - Complete
  Rename slide to slide- Complete

  Include 3 new modes (optional) - 1 left
  Stop/Ok code random flash mode
  Final testing -

*/

/*
   #Manual
   Power  - Turns on all led or off all pins
   Stop - Disables leds mode
   Mute - disables or enables the buzzer
   Mode - Selects next mode
   Return - Selects previous mode
   EQ - Turn on or off specific leds
   Prev - Left indicator
   Next - Right indicator
   Forward - Reverse indicator
   Volume down - Decreases delay time
   Volume up - Increases delay time
   Return - Resets all values
   Numerical values 1 to 8 - Shortcut for modes

*/
int whiteR = 3,
    blue = 4,
    green = 5,
    relay = 6,
    yellow = 8,
    red = 9,
    whiteL = 10,
    buzzer = 11,
    delayTime = 100;

//Mini remote
uint32_t powerCode = 0xFFA25D,
         stopCode = 0xFF629D,
         muteCode = 0xFFE21D,
         modeCode = 0xFF22DD,
         returnCode = 0xFF02FD,
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
         zeroCode8SE = 0x910,

         okCode8SE = 0xA70,
         topCode8SE = 0x2F0,
         rightCode8SE = 0xCD0,
         bottomCode8SE = 0xAF0,
         leftCode8SE = 0x2D0,

         volUpCode8SE = 0x490,
         volDownCode8SE = 0xC90,

         ChUpCode8SE = 0x90,
         ChDownCode8SE = 0x890,

         muteCode8SE = 0x290,
         menuCode8SE = 0x70,
         returnCode8SE = 0x62E9,
         forwardCode8SE = 0xA50;

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

  for (int i = 0; i < 8; i++) {
    justBlink();
  }
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
void on(int pin1, int pin2 = 0, int pin3 = 0, int pin4 = 0, int pin5 = 0, int pin6 = 0, int pin7 = 0, int pin8 = 0, int pin9 = 0) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, HIGH);
  digitalWrite(pin7, HIGH);
  digitalWrite(pin8, HIGH);
  digitalWrite(pin9, HIGH);
}

void off(int pin1, int pin2 = 0, int pin3 = 0, int pin4 = 0, int pin5 = 0, int pin6 = 0, int pin7 = 0, int pin8 = 0, int pin9 = 0) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, LOW);
  digitalWrite(pin9, LOW);
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
void flash(int pin1, int pin2 = 0) {
  on(pin1);
  on(pin2);
  delay(100);
  off(pin1);
  off(pin2);
  delay(100);
  on(pin1);
  on(pin2);
  delay(100);
  off(pin1);
  off(pin2);
  delay(100);
}
void reverse() {
  on(rearGreen, rearRed, green, red, buzzer);
  delay(delayTime * 4);
  off(rearGreen, rearRed, green, red, buzzer);
  delay(delayTime * 4);
}

void allOn() {
  on(whiteR, whiteL, blue, green, yellow, red, rearGreen, rearRed);
}
void allOff() {
  off(whiteR, whiteL, blue, green, yellow, red, rearGreen, rearRed, buzzer);
}
void indicate(int pin1, int pin2, int pin3, int pin4) {
  for (int i = 0; i < 8; i++) {
    on(pin1, pin2, pin3, pin4, buzzer);
    delay(delayTime * 2);
    off(pin1, pin2, pin3, pin4, buzzer);
    delay(delayTime * 2);
  }
}
void aeroplane() {
  on(red, green, whiteL, whiteR);
  delay(delayTime);
  off(whiteL, whiteR);
  //Need a thousand milis gap. So lets use the time
  flashReps(rearGreen, rearRed, 5);
  //End of thousand milis gap.
  on(rearGreen, rearRed, yellow);
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
  on(whiteL, whiteR);
  cop();
}
void slideOff() {
  flashReps(whiteR, 0, 1);
  flashReps(blue, 0, 1);
  flashReps(green, 0, 1);
  flashReps(rearGreen, 0, 1);
  flashReps(rearRed, 0, 1);
  flashReps(yellow, 0, 1);
  flashReps(red, 0, 1);
  flashReps(whiteL, 0, 1);
  flashReps(red, 0, 1);
  flashReps(yellow, 0, 1);
  flashReps(rearRed, 0, 1);
  flashReps(rearGreen, 0, 1);
  flashReps(green, 0, 1);
  flashReps(blue, 0, 1);
}

void slide() {
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
  on(whiteL, whiteR);
  delay(delayTime);
  on(red, blue);
  delay(delayTime);
  on(yellow, green);
  delay(delayTime);
  on(rearRed, rearGreen);
  delay(delayTime);
  off(whiteL, whiteR);
  delay(delayTime);
  off(red, blue);
  delay(delayTime);
  off(yellow);
  off(green);
  delay(delayTime);
  off(rearRed, rearGreen);
  delay(delayTime);
  on(rearRed, rearGreen);
  delay(delayTime);
  on(green, yellow);
  delay(delayTime);
  on(blue, red);
  delay(delayTime);
  on(whiteR, whiteL);
  delay(delayTime);
  off(green, yellow);
  delay(delayTime);
  off(blue, red);
  delay(delayTime);
  off(whiteR, whiteL);
  delay(delayTime);
}

void justBlink() {
  allOn();
  on(buzzer);
  delay(delayTime);
  allOff();
  delay(delayTime);
}

void madFlash() {
  int thePin = 3 + (rand() % 9);
  int reps = 1 + (rand() % 3);
  flashReps(thePin, 0, reps);
}
void reset() {
  allOff();

  delayTime = 100;

  whiteR = 3;
  blue = 4;
  green = 5;
  rearGreen = 6;
  rearRed = 7;
  yellow = 8;
  red = 9;
  whiteL = 10;
  buzzer = 11;

  mode = "aeroplane";

  
  buzzerIsOn=false;
  muted = false;
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

  uint32_t
  powerCode = 0xFFA25D;
  stopCode = 0xFF629D;
  muteCode = 0xFFE21D;
  modeCode = 0xFF22DD;
  returnCode = 0xFF02FD;
  eqCode = 0xFFC23D;
  prevCode = 0xFFE01F;
  nextCode = 0xFFA857;
  forwardCode = 0xFF906F;
  leftCode = 0xFF6897;
  rightCode = 0xFF9867;
  zeroCode = 0xFFB04F;
  oneCode = 0xFF30CF;
  twoCode = 0xFF18E7;
  threeCode = 0xFF7A85;
  fourCode = 0xFF10EF;
  fiveCode = 0xFF38C7;
  sixCode = 0xFF5AA5;
  sevenCode = 0xFF42BD;
  eightCode = 0xFF4AB5;
  nineCode = 0xFF52AD;
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
    if (gotCode(powerCode, powerCode8SE)) {
      allOff();
      if (allIsOn) {
        flash(green, rearGreen);
        mode = "allOn";
        allIsOn = false;
      }
      else {
        flash(red, rearRed);
        mode = "allOff";
        allIsOn = true;
      }
    }
    else if (gotCode(nextCode, rightCode8SE)) {
      allOff();
      indicate(whiteR, blue, green, rearGreen);
    }
    else if (gotCode(prevCode, leftCode8SE)) {
      allOff();
      indicate(whiteL, red, yellow, rearRed);
    }
    else if (gotCode(0xF42, homeCode8SE)) {
      allOff();
      powerCode = 0;
      stopCode = 0;
      muteCode = 0;
      modeCode = 0;
      returnCode = 0;
      eqCode = 0;
      prevCode = 0;
      nextCode = 0;
      forwardCode = 0;
      leftCode = 0;
      rightCode = 0;
      zeroCode = 0;
      oneCode = 0;
      twoCode = 0;
      threeCode = 0;
      fourCode = 0;
      fiveCode = 0;
      sixCode = 0;
      sevenCode = 0;
      eightCode = 0;
      nineCode = 0;
      flash(red, rearRed);

    }
    else if (gotCode(forwardCode, forwardCode8SE)) {
      for (int i = 0; i < 6; i++) {
        reverse();
      }
    }
    else if (gotCode(returnCode, returnCode8SE)) {
      reset();
    }
    else if (gotCode(rightCode, volUpCode8SE)) {
      if (delayTime < 2000) {
        flash(blue);
        delayTime *= 1.5;
      }
      else {
        flash(green, rearGreen);
      }
    }
    else if (gotCode(leftCode, volDownCode8SE)) {
      if (delayTime > 18) {
        flash(yellow);
        delayTime /= 1.5;

      }
      else {
        flash(red, rearRed);
      }
    }
    else if (gotCode(muteCode, muteCode8SE)) {
      if (muted) {
        buzzer = 11;
        flash(green, rearGreen);
        flash(buzzer);
        muted = false;
      }
      else {
        flash(red, rearRed);
        buzzer = 0;
        muted = true;
      }
    }
    else if (gotCode(modeCode, menuCode8SE)) {
      //Task : Left to programm for later
      if (mode == "manual") {
        mode = "fuze";
      }
      else if (mode == "fuze") {
        mode = "aeroplane";
      }
      else {
        allOff();
        whiteRIsOn = false;
        blueIsOn = false;
        greenIsOn = false;
        rearGreenIsOn = false;
        rearRedIsOn = false;
        yellowIsOn = false;
        redIsOn = false;
        whiteLIsOn = false;
        buzzerIsOn = false;

        flash(green, rearGreen);
        mode = "manual";
      }
    }
    else if (gotCode(nineCode, nineCode8SE)) {
      if (mode == "manual") {
        flash(buzzer);
        if (buzzerIsOn) {
          off(buzzer);
          buzzerIsOn = false;
        }
        else {
          on(buzzer);
          buzzerIsOn = true;
        }
      }
    }
    else if (gotCode(oneCode, oneCode8SE)) {
      if (mode == "manual") {
        flash(whiteR);
        if (whiteRIsOn) {
          off(whiteR);
          whiteRIsOn = false;
        }
        else {
          on(whiteR);
          whiteRIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(whiteR);
        whiteR = 0;
      }
      else {
        flash(blue);
        mode = "aeroplane";
      }
    }
    else if (gotCode(twoCode, twoCode8SE)) {
      if (mode == "manual") {
        flash(blue);
        if (blueIsOn) {
          off(blue);
          blueIsOn = false;
        }
        else {
          on(blue);
          blueIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(blue);
        blue = 0;
      }
      else {
        flash(blue);
        mode = "cop";
      }
    }
    else if (gotCode(threeCode, threeCode8SE)) {
      if (mode == "manual") {
        flash(green);
        if (greenIsOn) {
          off(green);
          greenIsOn = false;
        }
        else {
          on(green);
          greenIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(green);
        green = 0;
      }
      else {
        flash(blue);
        mode = "copTorch";
      }
    }
    else if (gotCode(fourCode, fourCode8SE)) {
      if (mode == "manual") {
        flash(rearGreen);
        if (rearGreenIsOn) {
          off(rearGreen);
          rearGreenIsOn = false;
        }
        else {
          on(rearGreen);
          rearGreenIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(rearGreen);
        rearGreen = 0;
      }
      else {
        flash(blue);
        mode = "slide";
      }
    }
    else if (gotCode(fiveCode, fiveCode8SE)) {
      if (mode == "manual") {
        flash(rearRed);
        if (rearRedIsOn) {
          off(rearRed);
          rearRedIsOn = false;
        }
        else {
          on(rearRed);
          rearRedIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(rearRed);
        rearRed = 0;
      }
      else {
        flash(blue);
        mode = "easeIO";
      }
    }
    else if (gotCode(sixCode, sixCode8SE)) {
      if (mode == "manual") {
        flash(yellow);
        if (yellowIsOn) {
          off(yellow);
          yellowIsOn = false;
        }
        else {
          on(yellow);
          yellowIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(yellow);
        yellow = 0;
      }
      else {
        flash(blue);
        mode = "justBlink";
      }
    }
    else if (gotCode(sevenCode, sevenCode8SE)) {
      if (mode == "manual") {
        flash(red);
        if (redIsOn) {
          off(red);
          redIsOn = false;
        }
        else {
          on(red);
          redIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(red);
        red = 0;
      }
      else {
        flash(blue);
        mode = "slideOff";
      }
    }
    else if (gotCode(eightCode, eightCode8SE)) {
      if (mode == "manual") {
        flash(whiteL);
        if (whiteLIsOn) {
          off(whiteL);
          whiteLIsOn = false;
        }
        else {
          on(whiteL);
          whiteLIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(whiteL);
        whiteL = 0;
      }
      else {
        allOff();
        mode = "madFlash";
      }
    }
    irrecv.resume();
    Serial.println(mode);
  }

  // The task
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
  else if (mode == "slide") {
    allOff();
    slide();
  }
  else if (mode == "easeIO") {
    allOff();
    easeIO();
  }
  else if (mode == "justBlink") {
    allOff();
    justBlink();
  }
  else if (mode == "slideOff") {
    allOff();
    slideOff();
  }
  else if (mode == "madFlash") {
    madFlash();
  }
  else if (mode == "allOn") {
    allOff();
    allOn();
  }
  else if (mode == "allOff") {
    allOff();
  }
  else if (mode == "fuze") {
    allOn();
    flash(red, rearRed);
  }
  Serial.println(3 + (rand() % 9));


}

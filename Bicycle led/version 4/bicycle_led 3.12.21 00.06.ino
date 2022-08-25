#include <IRremote.h>
const int RECV_PIN = 12;
uint32_t sentCode;

IRrecv irrecv(RECV_PIN);
decode_results results;

/*Highlights
  1. The maximum value of ms100 you can reach is 100 x 1.5^8 = 2562.890625 miliseconds
  2. The minimun value of ms100 you can reach is 100 ÷ 1.5^5 = 13.1687242798 miliseconds


*/


boolean allIsOn = false,
        relayIncluded = false,
        muted = false,
        buzzerIsOn = false,
        whiteRIsOn = false, blueIsOn = false, greenIsOn = false, relayIsOn = false, torchIsOn = false, yellowIsOn = false, redIsOn = false, whiteLIsOn = false;
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

  Include Torch, Relay and fix bugs-Complete


  Final testing -

*/

/*
   #Manual
   
   Power  - Turns on all led or off all pins(except relay) 
   home - disables mini remote
   Mute - disables or enables the buzzer
   Mode/Ok - If mode is null, turns mode into manual,if mode is manual,turns mode into fuze, if mode is fuze, turns mode into null
   EQ - Include/exclude relay
   Prev - Left indicator
   Next - Right indicator
   Forward - Reverse indicator
   Volume down - Decreases delay time
   Volume up - Increases delay time
   Return - Resets all values
   Numerical values 1 to 8 - Shortcut for modes or can turn on/off pins in manual mode
   Numerical value 9 - Turns on/off relay if not in fuze mode

*/
int whiteR = 3,
    blue = 4,
    green = 5,
    relay = 6,
    torch = 7,
    yellow = 8,
    red = 9,
    whiteL = 10,
    buzzer = 11,
    ms100 = 100;

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
    delay(ms100);
    off(pin1);
    off(pin2);
    delay(ms100);
  }
}
void setup() {
  pinMode(whiteR, OUTPUT);
  pinMode(whiteL, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(torch, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  flashReps(yellow, green, 1);
  delay(ms100);
  flashReps(red, blue, 1);
  delay(ms100);
  flashReps(whiteR, whiteL, 1);
  delay(ms100);
  flashReps(relay, 0, 1);
  delay(ms100);
  flashReps(buzzer, 0, 1);
  on(torch);

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
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
  on(relay, green, red, buzzer);
  delay(ms100 * 4);
  off(relay, green, red, buzzer);
  delay(ms100 * 4);
}

void allOn() {
  on(whiteR, whiteL, blue, green, yellow, red);
}
void allOff() {
  off(whiteR, whiteL, blue, green, yellow, red , buzzer);
}
void indicate(int pin1, int pin2, int pin3) {
  for (int i = 0; i < 8; i++) {
    on(pin1, pin2, pin3, buzzer);
    delay(ms100 * 2);
    off(pin1, pin2, pin3, buzzer);
    delay(ms100 * 2);
  }
}
void aeroplane() {
  if (relayIncluded) {
    on(red, green, relay);
    delay(ms100);
    off(relay);
    delay(1000);
    on(yellow);
    delay(ms100);
    off(yellow);
    delay(ms100 * 2);
  }
  else {
    on(red, green, whiteL, whiteR);
    delay(ms100);
    off(whiteL, whiteR);
    delay(1000);
    on(yellow);
    delay(ms100);
    off(yellow);
    delay(ms100 * 2);
  }

}

void cop() {
  on(red);
  delay(ms100 * 2);
  off(red);
  on(blue);
  delay(ms100 * 2);
  off(blue);
}
void copTorch() {
  if (relayIncluded) {
    on(relay);
    cop();
  }
  else {
    on(whiteL, whiteR);
    cop();
  }
}
void slideOff() {
  flashReps(whiteR, 0, 1);
  flashReps(blue, 0, 1);
  flashReps(green, 0, 1);
  flashReps(yellow, 0, 1);
  flashReps(red, 0, 1);
  flashReps(whiteL, 0, 1);
  flashReps(red, 0, 1);
  flashReps(yellow, 0, 1);
  flashReps(green, 0, 1);
  flashReps(blue, 0, 1);
}

void slide() {
  on(whiteL);
  delay(ms100);
  on(red);
  delay(ms100);
  on(yellow);
  delay(ms100);
  on(green);
  delay(ms100);
  on(blue);
  delay(ms100);
  on(whiteR);
  delay(ms100);

  off(whiteL);
  delay(ms100);
  off(red);
  delay(ms100);
  off(yellow);
  delay(ms100);
  off(green);
  delay(ms100);
  off(blue);
  delay(ms100);
  off(whiteR);
  delay(ms100);

  on(whiteR);
  delay(ms100);
  on(blue);
  delay(ms100);
  on(green);
  delay(ms100);
  on(yellow);
  delay(ms100);
  on(red);
  delay(ms100);
  on(whiteL);
  delay(ms100);


  off(whiteR);
  delay(ms100);
  off(blue);
  delay(ms100);
  off(green);
  delay(ms100);
  off(yellow);
  delay(ms100);
  off(red);
  delay(ms100);
  off(whiteL);
  delay(ms100);
}

void easeIO() {
  if (relayIncluded) {
    on(relay);
    delay(ms100);
    on(whiteL, whiteR);
    delay(ms100);
    on(red, blue);
    delay(ms100);
    on(yellow, green);
    delay(ms100);
    off(relay);
    delay(ms100);
    off(whiteL, whiteR);
    delay(ms100);
    off(red, blue);
    delay(ms100);
    off(yellow, green);
    on(green, yellow);
    delay(ms100);
    on(blue, red);
    delay(ms100);
    on(whiteR, whiteL);
    delay(ms100);
    on(relay);
    delay(ms100);
    off(green, yellow);
    delay(ms100);
    off(blue, red);
    delay(ms100);
    off(whiteR, whiteL);
    delay(ms100);
    off(relay);
  }
  else {
    on(whiteL, whiteR);
    delay(ms100);
    on(red, blue);
    delay(ms100);
    on(yellow, green);
    delay(ms100);
    off(whiteL, whiteR);
    delay(ms100);
    off(red, blue);
    delay(ms100);
    off(yellow, green);
    on(green, yellow);
    delay(ms100);
    on(blue, red);
    delay(ms100);
    on(whiteR, whiteL);
    delay(ms100);
    off(green, yellow);
    delay(ms100);
    off(blue, red);
    delay(ms100);
    off(whiteR, whiteL);
  }
}

void justBlink() {
  if (relayIncluded) {
    on(relay);
    delay(20);




    //Bug ere
    allOn();
    on(buzzer);
    delay(ms100);
    allOff();
    off(relay);
    delay(ms100);
  }
  else {
    allOn();
    on(buzzer);
    delay(ms100);
    allOff();
    delay(ms100);
  }
}

void madFlash() {
  int thePin = 3 + (rand() % 9);
  int reps = 1 + (rand() % 3);
  flashReps(thePin, 0, reps);
}
void reset() {
  allOff();
  off(relay);
  flash(green);

  ms100 = 100;

  whiteR = 3;
  blue = 4;
  green = 5;
  relay = 6;
  torch = 7;
  yellow = 8;
  red = 9;
  whiteL = 10;
  buzzer = 11;

  mode = "aeroplane";
  relayIncluded = false;
  buzzerIsOn = false;
  muted = false;
  allIsOn = false;
  muted = false;
  whiteRIsOn = false;
  blueIsOn = false;
  greenIsOn = false;
  yellowIsOn = false;
  redIsOn = false;
  whiteLIsOn = false;
  relayIsOn = false;
  torchIsOn = false;

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
      off(relay);
      relayIsOn=false;
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
    else if (gotCode(eqCode, topCode8SE)) {
      if (relayIncluded) {
        flash(red);
        off(relay);
        relayIsOn = false;
        relayIncluded = false;
      }
      else {
        flash(green);
        relayIncluded = true;
      }
    }
    else if (gotCode(nextCode, rightCode8SE)) {
      allOff();
      indicate(whiteR, blue, green);
    }
    else if (gotCode(prevCode, leftCode8SE)) {
      allOff();
      indicate(whiteL, red, yellow);
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
      flash(red);

    }
    else if (gotCode(forwardCode, forwardCode8SE)) {
      for (int i = 0; i < 8; i++) {
        reverse();
      }
    }
    else if (gotCode(returnCode, returnCode8SE)) {
      reset();
    }
    else if (gotCode(rightCode, volUpCode8SE)) {
      if (ms100 < 2000) {
        flash(blue);
        ms100 *= 1.5;
      }
      else {
        flash(green);
      }
    }
    else if (gotCode(leftCode, volDownCode8SE)) {
      if (ms100 > 18) {
        flash(yellow);
        ms100 /= 1.5;

      }
      else {
        flash(red);
      }
    }
    else if (gotCode(muteCode, muteCode8SE)) {
      if (muted) {
        buzzer = 11;
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
    else if (gotCode(modeCode, okCode8SE)) {
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
        relayIsOn = false;
        yellowIsOn = false;
        redIsOn = false;
        whiteLIsOn = false;
        buzzerIsOn = false;

        flash(green);
        mode = "manual";
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
        mode = "slide";
      }
    }
    else if (gotCode(fiveCode, fiveCode8SE)) {
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
        mode = "easeIO";
      }
    }
    else if (gotCode(sixCode, sixCode8SE)) {
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
        flash(blue);
        mode = "justBlink";
      }
    }
    else if (gotCode(sevenCode, sevenCode8SE)) {

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
      else if (mode == "fuze") {
        //Do nothing
      }
      else {
        flash(blue);
        mode = "slideOff";
      }
    }
    else if (gotCode(eightCode, eightCode8SE)) {
      if (mode == "manual") {
        flash(torch);
        if (torchIsOn) {
          off(torch);
          torchIsOn = false;
        }
        else {
          on(torch);
          torchIsOn = true;
        }
      }
      else if (mode == "fuze") {
        off(torch);
        torch = 0;
      }
      else {
        allOff();
        mode = "madFlash";
      }
    }

    else if (gotCode(nineCode, nineCode8SE)) {
      if (mode == "fuze") {
        off(relay);
        relay = 0;
      }
      else {
        if (relayIsOn) {
          off(relay);
          relayIsOn = false;
        }
        else {
          on(relay);
          relayIsOn = true;
        }
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
    flash(red);
  }
  Serial.println(3 + (rand() % 9));


}
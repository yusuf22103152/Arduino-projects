#include <IRremote.h>

const int delayIntro = 100,
          delayTime = 100,
          pushButton = 13,

          whiteL1 = 5,
          whiteL2 = 6,
          red = 7,
          yellow = 8,
          green = 9,
          blue = 10,
          whiteR2 = 11,
          whiteR1 = 12;

boolean buttonState, primaryMode = false, yellowIsOn = false;
String mode = "aeroplane";

int pirState = LOW, mainIndicator = yellow, minorIndicator = green;

void on(int elem) {
  digitalWrite(elem, HIGH);
}

void off(int elem) {
  digitalWrite(elem, LOW);
}

void setup() {
  pinMode(pushButton, INPUT);
  pinMode(whiteL1, OUTPUT);
  pinMode(whiteL2, OUTPUT);
  pinMode(whiteR1, OUTPUT);
  pinMode(whiteR2, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);

  easeIO(delayIntro);
  allOn();
  delay(300);
  allOff();
  delay(300);
  allOn();
  delay(300);
  allOff();
  delay(300);

}

void easeIO(int delayTime) {
  on(whiteL1);
  on(whiteR1);
  delay(delayTime);
  on(whiteL2);
  on(whiteR2);
  delay(delayTime);
  on(red);
  on(blue);
  delay(delayTime);
  on(yellow);
  on(green);
  delay(delayTime);

  off(whiteL1);
  off(whiteR1);
  delay(delayTime);
  off(whiteL2);
  off(whiteR2);
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
  on(whiteR2);
  on(whiteL2);
  delay(delayTime);
  on(whiteR1);
  on(whiteL1);
  delay(delayTime);

  off(green);
  off(yellow);
  delay(delayTime);
  off(blue);
  off(red);
  delay(delayTime);
  off(whiteR2);
  off(whiteL2);
  delay(delayTime);
  off(whiteR1);
  off(whiteL1);
  delay(delayTime);
}

void startAnim() {
  on(whiteL1);
  delay(delayIntro);
  on(whiteL2);
  delay(delayIntro);
  on(red);
  delay(delayIntro);
  on(yellow);
  delay(delayIntro);
  on(green);
  delay(delayIntro);
  on(blue);
  delay(delayIntro);
  on(whiteR2);
  delay(delayIntro);
  on(whiteR1);
  delay(delayIntro);

  off(whiteL1);
  delay(delayIntro);
  off(whiteL2);
  delay(delayIntro);
  off(red);
  delay(delayIntro);
  off(yellow);
  delay(delayIntro);
  off(green);
  delay(delayIntro);
  off(blue);
  delay(delayIntro);
  off(whiteR2);
  delay(delayIntro);
  off(whiteR1);
  delay(delayIntro);

  on(whiteR1);
  delay(delayIntro);
  on(whiteR2);
  delay(delayIntro);
  on(blue);
  delay(delayIntro);
  on(green);
  delay(delayIntro);
  on(yellow);
  delay(delayIntro);
  on(red);
  delay(delayIntro);
  on(whiteL2);
  delay(delayIntro);
  on(whiteL1);
  delay(delayIntro);


  off(whiteR1);
  delay(delayIntro);
  off(whiteR2);
  delay(delayIntro);
  off(blue);
  delay(delayIntro);
  off(green);
  delay(delayIntro);
  off(yellow);
  delay(delayIntro);
  off(red);
  delay(delayIntro);
  off(whiteL2);
  delay(delayIntro);
  off(whiteL1);
  delay(delayIntro);
}
void modeSwing(int indicator) {
  allOff();
  for (int i = 0; i < 7; i++) {
    on(indicator);
    delay(70);
    off(indicator);
    delay(70);
  }
}


void torch() {
  on(whiteL1);
  on(whiteL2);
  on(whiteR1);
  on(whiteR2);
}
void torch2() {
  on(whiteL1);
  on(whiteL2);
  on(whiteR1);
  on(whiteR2);
  on(green);
  on(yellow);
}
void batterySaver() {
  on(whiteR1);
  on(whiteL1);
}
void batterySaver2() {
  on(whiteR2);
  on(whiteL2);
}
void aeroplane() {
  on(red);
  on(green);
  on(whiteL2);
  on(whiteR2);
  delay(100);
  off(whiteL2);
  off(whiteR2);
  delay(1000);
  on(yellow);
  delay(100);
  off(yellow);
  delay(200);
}
void aeroplaneTorch() {
  on(whiteL1);
  on(whiteR1);
  aeroplane();
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
  torch();
  cop();
}

/*void motionAlert() {
  on(buzzer);
  off(red);
  delay(200);
  off(buzzer);
  on(red);
  delay(200);
  on(buzzer);
  off(red);
  delay(200);
  off(buzzer);
  on(red);
  delay(500);
}*/

void allOn() {
  on(whiteL1);
  on(whiteL2);
  on(whiteR1);
  on(whiteR2);
  on(green);
  on(blue);
  on(red);
  on(yellow);
}
void allOff() {
  off(whiteL1);
  off(whiteL2);
  off(whiteR1);
  off(whiteR2);
  off(green);
  off(blue);
  off(red);
  off(yellow);
}

void switchMainIndicators() {
  modeSwing(mainIndicator);
  if (primaryMode) {
    mainIndicator = green;
    minorIndicator = yellow;
    primaryMode = false;
    mode = "aeroplane";
  }
  else {
    mainIndicator = yellow;
    minorIndicator = green;
    primaryMode = true;
    mode = "torch";
  }
}

void switchMainMode() {
  if (mode == "torch") {
    mode = "batterySaver";
  }
  else if (mode == "batterySaver") {
    mode = "batterySaver2";
  }
  else if (mode == "batterySaver2") {
    mode = "allOff";
  }
  else if (mode == "allOff") {
    mode = "torch";
  }
  else {
    mode = "torch";
  }
}


void switchMinorMode() {
  if (mode == "aeroplane") {
    mode = "aeroplaneTorch";
  }
  else if (mode == "aeroplaneTorch") {
    mode = "cop";
  }
  else if (mode == "cop") {
    mode = "copTorch";
  }
  else if (mode == "copTorch") {
    mode = "allOn";
  }
  else if (mode == "allOn") {
    mode = "startAnim";
  }
  else if (mode == "startAnim") {
    mode = "easeIO";
  }
  else if (mode == "easeIO") {
    mode = "aeroplane";
  }
  else {
    mode = "aeroplane";
  }
}


void secureMode() {
 /* pirState = digitalRead(pir);
  digitalWrite(green, HIGH);
  if (pirState == HIGH) {
    for (int i = 0; i < 4; i++)
    {
      motionAlert();
    }
  }*/
}
void readBtn() {
  buttonState = digitalRead(pushButton);
}


void process() {
  //Push button feature
  readBtn();
  if (buttonState == HIGH) {
    modeSwing(minorIndicator);
    readBtn();
    if (buttonState == HIGH) {
      switchMainIndicators();
    }

    else if (primaryMode) {
      switchMainMode();
    }
    else if (!primaryMode) {
      //If primary mode is false, means secondary mode is activated
      switchMinorMode();
    }

    delay(1000);

  }
  //Push button feature



  if (mode == "torch") {
    allOff();
    torch();
  }
  else if (mode == "batterySaver") {
    allOff();
    batterySaver();
  }
  else if (mode == "batterySaver2") {
    allOff();
    batterySaver2();
  }
  else if (mode == "allOff") {
    allOff();
  }
  else if (mode == "aeroplane") {
    allOff();
    aeroplane();
  }
  else if (mode == "aeroplaneTorch") {
    allOff();
    aeroplaneTorch();
  }
  else if (mode == "cop") {
    allOff();
    cop();
  }
  else if (mode == "copTorch") {
    allOff();
    copTorch();
  }
  else if (mode == "allOn") {
    allOff();
    allOn();
  }
  else if (mode == "startAnim") {
    allOff();
    startAnim();
  }
  else if (mode == "easeIO") {
    allOff();
    easeIO(delayIntro);
  }

}

void loop() {
  process();

}

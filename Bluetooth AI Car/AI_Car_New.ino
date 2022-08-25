//April 29 : ZZ mode is not letting itself switch

const int trig = 3,
          echo = 4,

          wrFor = 5,
          wrRev = 6,
          wlRev = 9,
          wlFor = 11,

          Torch = 10,
          buzzer = 12,
          turnWS = 180, //Turn wheel speed
          zigDelay = 500,
          rwSpeed = 170,

          restFor = 300;
int speedVal = 255,
    stVal = speedVal * 0.824; //Stable value : To stable the both wheel, 1 of them needed to decrease speed

boolean modeSwing = false, senSt = false;
String mode = "RC";
/*
  RC : Remote Control
  RB : Robot
  SF : Safe driving mode
  ZZ : Zig Zag
  BL : Blinker
  ML : Manually
*/
uint8_t RLed = A0,
        YLed = A2,
        GLed = A3,
        BLed = A5;

char code = 0;

int sensorAct,
    objDis,
    check365 = 0,
    holdFor = 180,
    animSD = 120;

long duration;

void setup()
{
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(wrFor, OUTPUT);
  pinMode(wlFor, OUTPUT);
  pinMode(wrRev, OUTPUT);
  pinMode(wlRev, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(Torch, OUTPUT);
  pinMode(RLed, OUTPUT);
  pinMode(YLed, OUTPUT);
  pinMode(GLed, OUTPUT);
  pinMode(BLed, OUTPUT);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  for (int m = 0; m < 4; m++) {
    anim1();
  }
}
void turnAt(int lwDir, int lwStat, int rwDir, int rwStat) {
  //left wheel direction, right wheel direction,left wheel status, right wheel status
  analogWrite(lwDir, lwStat);
  analogWrite(rwDir, rwStat);
}
void aOn(int pin1, int pin2 = 0, int pin3 = 0, int pin4 = 0) {
  analogWrite(pin1, speedVal);
  analogWrite(pin2, speedVal);
  analogWrite(pin3, speedVal);
  analogWrite(pin4, speedVal);
}
void on(int pin1, int pin2 = 0, int pin3 = 0, int pin4 = 0, int pin5 = 0, int pin6 = 0, int pin7 = 0, int pin8 = 0) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, HIGH);
  digitalWrite(pin7, HIGH);
  digitalWrite(pin8, HIGH);
}
void off(int pin1, int pin2 = 0, int pin3 = 0, int pin4 = 0, int pin5 = 0, int pin6 = 0, int pin7 = 0, int pin8 = 0) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, LOW);
}
void pwmOn(int pin, int pwmVal = speedVal) {
  analogWrite(pin, pwmVal);
}
void nutral() {
  off(wrFor, wrRev, wlFor, wlRev);
}
void forward() {
  //Car will go forward
  pwmOn(wlFor, stVal);
  pwmOn(wrFor);
  on(GLed);
}
void backward() {
  //Car will go forward
  pwmOn(wlRev, stVal);
  pwmOn(wrRev);
  on(RLed);
}
void right() {
  //Car will go forward
  pwmOn(wlFor, stVal);
  pwmOn(wrRev);
}
void left() {
  //Car will go forward
  pwmOn(wlRev, stVal);
  pwmOn(wrFor);
}
void turn(int whlTSide, int whlNorm) {
  //Wheen turn side, wheel normal
  turnAt(whlTSide, speedVal / 1.59, whlNorm, speedVal);
  on(GLed);
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
void animSlide() {
  on(RLed);
  delay(animSD);
  off(RLed);
  on(YLed);
  modeCodeCheck();
  delay(animSD);
  off(YLed);
  on(GLed);
  modeCodeCheck();
  delay(animSD);
  off(GLed);
  on(BLed);
  modeCodeCheck();
  delay(animSD);
  off(BLed);
  on(GLed);
  modeCodeCheck();
  delay(animSD);
  off(GLed);
  on(YLed);
  modeCodeCheck();
  delay(animSD);
  off(YLed);
}
void anim1() {
  on(RLed, BLed);
  delay(animSD);
  modeCodeCheck();
  off(RLed, BLed);
  on(GLed, YLed);
  delay(animSD);
  modeCodeCheck();
  off(GLed, YLed);
}
void anim2() {
  on(RLed);
  modeCodeCheck();
  delay(animSD);
  off(RLed);
  on(YLed);
  modeCodeCheck();
  delay(animSD);
  off(YLed);
  on(GLed);
  modeCodeCheck();
  delay(animSD);
  off(GLed);
  on(BLed);
  modeCodeCheck();
  delay(animSD);
  off(BLed);

}
void modeCodeCheck() {
  if (Serial.available() > 0 && code == "X") {
    switchMode();
  }
}
void blinker() {

  for (int l = 0; l < 4; l++) {
    animSlide();
  }
  for (int m = 0; m < 4; m++) {
    anim1();
  }
  for (int n = 0; n < 4; n++) {
    anim2();
  }
  
}
void rot90c() {
  lightsOff();
  on(BLed, wrRev, wlFor);
  delay(holdFor);
  nutral();
}
void lightsOff() {
  off(RLed, BLed, GLed, YLed);
}
void rot90cc() {
  lightsOff();
  on(BLed, wrFor, wlRev);
  delay(holdFor);
  nutral();
}
void flash(int pin1, int pin2 = 0) {
  for (int k = 0; k < 2; k++) {
    on(pin1, pin2);
    delay(animSD);
    off(pin1, pin2);
    delay(animSD);
  }
}

void switchMode() {
  lightsOff();
  off(wlFor,wrFor,wlRev,wrRev);
  flash(YLed);
  flash(buzzer);
  //Triangle button : On click changes mode.
  if (mode == "RC") {
    mode = "SF";
  }
  else if (mode == "SF") {
    mode = "RB";
  }
  else if (mode == "RB") {
    mode = "ML";
  }
  else if (mode == "ML") {
    mode = "RC";
  }

}
void ZigZag() {
  forward();
  delay(zigDelay);
  nutral();
  rot90c();
  forward();
  delay(zigDelay);
  nutral();
  rot90cc();
}
void setStVal() {
  stVal = speedVal * 0.824;
}
void process() {
  //Part to run when got code
  if (Serial.available() > 0)
  {
    code = Serial.read();
    switch (code) {
      case '1':
        speedVal = 120;
        setStVal();
        break;
      case '2':
        speedVal = 140;
        setStVal();
        break;
      case '3':
        speedVal = 160;
        setStVal();
        break;
      case '4':
        speedVal = 170;
        setStVal();
        break;
      case '5':
        speedVal = 190;
        setStVal();
        break;
      case '6':
        speedVal = 200;
        setStVal();
        break;
      case '7':
        speedVal = 220;
        setStVal();
        break;
      case '8':
        speedVal = 230;
        setStVal();
        break;
      case '9':
        speedVal = 240;
        setStVal();
        break;
      case 'q':
        speedVal = 255;
        setStVal();
        break;
      case 'W':
        on(Torch);
        break;
      case 'w':
        off(Torch);
        break;
      case 'x':
      case 'X':
        switchMode();
        break;

      case 'F':
        //Forward
        if (mode == "RC") {
          forward();
        }
        else if (mode == "ML") {
          on(GLed);
        }
        else if (mode == "SF") {
          //Continiously forwarding creates a long loop of buzzer flash
          defStats();
          if (senSt) {
            nutral();
            on(buzzer, RLed);
            //Left for later
          }
          else {
            forward();
          }

        }
        break;
      case 'B':
        //Backward
        if (mode == "RC" || mode == "SF") {
          backward();
        }
        else if (mode == "ML") {
          on(RLed);
        }
        break;
      case 'R':
        //Right turn
        if (mode == "RC" || mode == "SF") {
          right();
        }
        else if (mode == "ML") {
          on(BLed);
        }
        break;
      case 'L':
        //Left turn
        if (mode == "RC" || mode == "SF") {
          left();
        }
        else if (mode == "ML") {
          on(YLed);
        }
        break;
      case 'G':
        //Forward left
        if (mode == "RC" || mode == "SF") {
          turnAt(wlFor, stVal / 1.59 , wrFor, speedVal);
        }
        else if (mode == "ML") {
          on(GLed, YLed);
        }
        break;
      case 'I':
        //Forward right
        if (mode == "RC" || mode == "SF") {
          turnAt(wlFor, stVal, wrFor, speedVal / 1.59);
        }
        else if (mode == "ML") {
          on(GLed, BLed);
        }
        break;
      case 'H':
        //Backward left
        if (mode == "RC" || mode == "SF") {
          turnAt(wlRev, stVal / 1.59, wrRev, speedVal);
        }
        else if (mode == "ML") {
          on(RLed, YLed);
        }
        break;
      case 'J':
        if (mode == "RC" || mode == "SF") {
          turnAt(wlRev, stVal, wrRev, speedVal / 1.59);
        }
        else if (mode == "ML") {
          on(RLed, BLed);
        }
        //Backward right
        break;

      case 'S':
        lightsOff();
        //On action up (while no button is pressed)
        if (mode == "RC" || mode == "SF") {
          nutral();
          if (mode == "SF") {
            off(buzzer);
          }
        }
        break;

      case 'V':
        //Sound button : Turns on horn
        on(buzzer);
        break;
      case 'v':
        //Sound button : Turns off horn
        off(buzzer);
        break;
    }
  }
  //End : Part to run when received code

  //Part to run in loop
  if (mode == "RC") {
    on(BLed);
  }
  else if (mode == "SF") {
    on(YLed);
  }
  else if (mode == "RB") {
    lightsOff();
    defStats();
    if (senSt) {
      nutral();
      flash(BLed, buzzer);
      backward();
      delay(120);
      nutral();
      rot90c();
    }
    else {
      forward();
    }
    /*
      Serial.print("Object detected in ");
      Serial.print(objDis);
      Serial.println(" inches");
    */
  }
  else if (mode == "ZZ") {
    lightsOff();
    ZigZag();
  }
  else if (mode == "BL") {
    lightsOff();
    blinker();
  }
  //End : Part to run in loop
}


void loop()
{
  process();

  Serial.print("Mode : ");
  Serial.print(mode);
  Serial.print("  ");
  Serial.print("Speed : ");
  Serial.println(speedVal);



}

//Pins for transfer and receive 
int echo=2;
int trigger=3;

//Buzzer for alerm
int buzzer=4;

//Relay for switching
int relay=5;

//Error indicator
int error=6;

//This will check if water alerm has been alerted or not
String triggered="null";

//Delay time between each buzz when water is high or low 
int delayHigh=400;
int delayLow=100;

//It will count how  many times buzzer has been buzzed
int count;

//The distance of water from sensor or tank top
float waterDistance;

//Duration between signal transmit and receive
long duration;

//Delay between each read of SONAR
int timeBreak=1000;

//The height of tank in inches
float tankHeight = 25;

//Maximum and minimum value of water level when to trigger alarm (In percentage)
int spaceMax = 60;
int spaceMin = 15;

//Distance of water from tank top or sensor (In percentage)
float ToPercent;

//Alarm function when water is in max limit
void alarmHigh() {
  digitalWrite(buzzer, HIGH);
  delay(delayHigh);
  digitalWrite(buzzer, LOW);
  delay(delayHigh);
  }

//Alarm function when water is in min limit
void alarmLow() {
  digitalWrite(buzzer, HIGH);
  delay(delayLow);
  digitalWrite(buzzer, LOW);
  delay(delayLow);
  }  

void convert() {
  waterDistance = (duration/2) / (29.1*2.54); 
  }


//Function to throw and receive signal
void throwSignal() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  }

//Define percentage : Function to convert signal duration to water distance (In percentage)
void DefPercent() {
  convert();
  ToPercent=100*waterDistance/tankHeight;
  }

//Function for main operation 
void Operation() {
  if (ToPercent>100) {
    analogWrite(error, 255);
    digitalWrite(relay, LOW);
    delay(timeBreak);
    digitalWrite(error, LOW);
    }
    
  else if (ToPercent>spaceMax && ToPercent<=100) {
    for (count=0; count<5 && triggered=="up"; count++) {
      alarmLow();
      }
      
    analogWrite(relay,255);  
    triggered="down";  
    }
  
  else if (ToPercent<spaceMin) {
    digitalWrite(relay,LOW);
    for (count=0; count<5 && triggered=="down"; count++) {
      alarmHigh();
      }
    triggered="up";  
    }
  count=0;
  }

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT); 
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  throwSignal();
  DefPercent();
  if (ToPercent<spaceMin) {triggered="down";}  
  else if (ToPercent>spaceMax) {triggered="up";}
}

void loop() {
  throwSignal();
  DefPercent();
  Operation();
  
  Serial.println(ToPercent); 
  delay(timeBreak); 
}
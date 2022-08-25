int echoPin=2;
int trigPin=3;
int buzzer=4;
int relay=5;
int error=6;
String triggered;

int delayHigh=500;
int delayLow=100;

int l,h;

float waterDistance;

long duration;

int timeBreak=1000;

float tankHeight = 57;
int spaceMax = 60;
int spaceMin = 15;

float ToPercent=100*waterDistance/tankHeight;




void alarmHigh() {
  digitalWrite(buzzer, HIGH);
  delay(delayHigh);
  digitalWrite(buzzer, LOW);
  delay(delayHigh);
  }

void alarmLow() {
  digitalWrite(buzzer, HIGH);
  delay(delayLow);
  digitalWrite(buzzer, LOW);
  delay(delayLow);
  }  

void throwSignal() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  waterDistance = (duration/2) / (29.1*2.54); 
  }

void DefPercent() {
   ToPercent=100*waterDistance/tankHeight;
  }

void setup() {
  Serial.begin(9600);

  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

}


void loop() {

  throwSignal();
  DefPercent();

  if (ToPercent>100) {
    analogWrite(error, 255);
    digitalWrite(relay, LOW);
    digitalWrite(error, LOW);
    
    }
  else if (ToPercent>spaceMax && ToPercent<=100) {
    for (l=0; l<5 && triggered=="up"; l++) {
      alarmLow();
      
      }
    analogWrite(relay,255);  
    triggered="down";  
    
    }
  
  else if (ToPercent<spaceMin) {
    digitalWrite(relay,LOW);
    for (h=0; h<5 && triggered=="down"; h++) {
      alarmHigh();
      }
    triggered="up";  
    }
  l=0;
  h=0; 
  Serial.println(ToPercent); 
  delay(timeBreak);
  
  
  
}
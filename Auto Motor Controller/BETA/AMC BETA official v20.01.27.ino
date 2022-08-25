float tankHeight=27,ToPercent,waterDistance;
int spaceMax=60,spaceMin=25;
int echo=2,trigger=3,buzzer=4,relay=5,error=6,triggered,delayHigh=100,delayLow=400,count,timeBreak=1000;
long duration;
void alarmOnStart() {
  Serial.begin(9600);
  digitalWrite(buzzer,HIGH);
  delay(2000);
  digitalWrite(buzzer,LOW);
  delay(8000);
  }
void onStart() {alarmOnStart();}
void alarmLow() {
  digitalWrite(buzzer,HIGH);
  delay(delayLow);
  digitalWrite(buzzer,LOW);
  delay(delayLow);}
void alarmHigh() {
  digitalWrite(buzzer,HIGH);
  delay(delayHigh);
  digitalWrite(buzzer, LOW);
  delay(delayHigh);}  
void convert() {waterDistance=(duration/2)/(29.1*2.54);}
void throwSignal() {
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  duration=pulseIn(echo,HIGH);}
void DefinePercent() {
  convert();
  ToPercent=100*waterDistance/tankHeight;
  }
void Operation() {
  if (ToPercent>120) {
    analogWrite(error,255);}
  else if (ToPercent>spaceMax && ToPercent<=120) {
    digitalWrite(error,LOW);
    for (count=0;count<5 && triggered==1; count++) {alarmLow();}
    analogWrite(relay,255);
    triggered=0;}
  else if (ToPercent<spaceMin) {
    digitalWrite(error,LOW);  
    for (count=0;count<5 && triggered==0;count++) {alarmHigh();}
    digitalWrite(relay,LOW);   
    triggered=1;}}
void setup() {
  Serial.begin(9600);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT); 
  pinMode(buzzer,OUTPUT);
  pinMode(relay,OUTPUT);
  onStart();
  throwSignal();
  DefinePercent();
  if (ToPercent<spaceMin) {triggered=0;}  
  else if (ToPercent>spaceMax) {triggered=1;}}
void loop() {
  throwSignal();
  DefinePercent();
  Operation();
  Serial.println(waterDistance); 
  delay(timeBreak);}
  
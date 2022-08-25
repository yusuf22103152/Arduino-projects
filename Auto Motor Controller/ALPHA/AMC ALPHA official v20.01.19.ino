float tH=25,TP,wD;
int sMx=60,sMn=15;
int e=2,t=3,b=4,r=5,er=6,tgd,dH=100,dL=400,c,tB=1000;
long d;
void aL() {
  digitalWrite(b,HIGH);
  delay(dL);
  digitalWrite(b,LOW);
  delay(dL);}
void aH() {
  digitalWrite(b,HIGH);
  delay(dH);
  digitalWrite(b, LOW);
  delay(dH);}  
void crt() {wD=(d/2)/(29.1*2.54);}
void tS() {
  digitalWrite(t,LOW);
  delayMicroseconds(2);
  digitalWrite(t,HIGH);
  delayMicroseconds(10);
  digitalWrite(t,LOW);
  d=pulseIn(e,HIGH);}
void DP() {
  crt();
  TP=100*wD/tH;
  }
void O() {
  if (TP>100) {
    analogWrite(er,255);}
  else if (TP>sMx && TP<=100) {
    digitalWrite(er,LOW);
    for (c=0;c<5 && tgd==1; c++) {aL();}
    analogWrite(r,255);
    tgd=0;}
  else if (TP<sMn) {
    digitalWrite(er,LOW);  
    for (c=0;c<5 && tgd==0;c++) {aH();}
    digitalWrite(r,LOW);   
    tgd=1;}
  c=0;}
void setup() {
  Serial.begin(9600);
  pinMode(t,OUTPUT);
  pinMode(e,INPUT); 
  pinMode(b,OUTPUT);
  pinMode(r,OUTPUT);
  tS();
  DP();
  if (TP<sMn) {tgd=0;}  
  else if (TP>sMx) {tgd=1;}}
void loop() {
  tS();
  DP();
  O();
  Serial.println(TP); 
  delay(tB);}
const int eEntry = 13, 
tEntry = 12,

bit1=11,
bit2=10,
bit3=9,
bit4=8,
bit5=7,
bit6=6,
bit7=5,
bit8=4,

eExit=2,
tExit=3;

const uint8_t light=A0,fan=A1;

float getDistanceINCH(int echo,int trig) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration=pulseIn(echo, HIGH);
  return (duration / 2) / (29.1 * 2.54);
}
void bitsOff() {
  digitalWrite(bit1,LOW);
  digitalWrite(bit2,LOW);
  digitalWrite(bit3,LOW);
  digitalWrite(bit4,LOW);
  digitalWrite(bit5,LOW);
  digitalWrite(bit6,LOW);
  digitalWrite(bit7,LOW);
  digitalWrite(bit8,LOW);
} 

void starter() {

  int ms=50;
  
  digitalWrite(bit1,HIGH);
  delay(ms);
  digitalWrite(bit2,HIGH);
  delay(ms);
  digitalWrite(bit3,HIGH);
  delay(ms);
  digitalWrite(bit4,HIGH);
  delay(ms);
  digitalWrite(bit4,HIGH);
  delay(ms);
  digitalWrite(bit5,HIGH);
  delay(ms);
  digitalWrite(bit6,HIGH);
  delay(ms);
  digitalWrite(bit7,HIGH);
  delay(ms);
  digitalWrite(bit8,HIGH);
  delay(ms);

  
  digitalWrite(bit1,LOW);
  delay(ms);
  digitalWrite(bit2,LOW);
  delay(ms);
  digitalWrite(bit3,LOW);
  delay(ms);
  digitalWrite(bit4,LOW);
  delay(ms);
  digitalWrite(bit5,LOW);
  delay(ms);
  digitalWrite(bit6,LOW);
  delay(ms);
  digitalWrite(bit7,LOW);
  delay(ms);
  digitalWrite(bit8,LOW);
  delay(ms);


  digitalWrite(bit8,HIGH);
  delay(ms);
  digitalWrite(bit7,HIGH);
  delay(ms);
  digitalWrite(bit6,HIGH);
  delay(ms);
  digitalWrite(bit5,HIGH);
  delay(ms);
  digitalWrite(bit4,HIGH);
  delay(ms);
  digitalWrite(bit3,HIGH);
  delay(ms);
  digitalWrite(bit2,HIGH);
  delay(ms);
  digitalWrite(bit1,HIGH);
  delay(ms);

  
  digitalWrite(bit8,LOW);
  delay(ms);
  digitalWrite(bit7,LOW);
  delay(ms);
  digitalWrite(bit6,LOW);
  delay(ms);
  digitalWrite(bit5,LOW);
  delay(ms);
  digitalWrite(bit4,LOW);
  delay(ms);
  digitalWrite(bit3,LOW);
  delay(ms);
  digitalWrite(bit2,LOW);
  delay(ms);
  digitalWrite(bit1,LOW);
  delay(ms);


}
void tester() {
  starter();
  digitalWrite(light,HIGH);
  delay(1000);
  digitalWrite(light,LOW);
  delay(1000);
  digitalWrite(fan,HIGH);
  delay(1000);
  digitalWrite(fan,LOW);

}


int count=0;
const int gateWidth=30;
void display8Bit(int x) {
  const int arr8bit[8]={128,64,32,16,8,4,2,1};
  const int pins8bit[8]={bit8,bit7,bit6,bit5,bit4,bit3,bit2,bit1};
  bitsOff();
  for(int i=0;i<8;i++) {
    if(x>=arr8bit[i]) {
      x-=arr8bit[i];
      digitalWrite(pins8bit[i],HIGH);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(tEntry, OUTPUT);
  pinMode(eEntry, INPUT);
  pinMode(tExit, OUTPUT);
  pinMode(eExit, INPUT);

  pinMode(bit1,OUTPUT);
  pinMode(bit2,OUTPUT);
  pinMode(bit3,OUTPUT);
  pinMode(bit4,OUTPUT);
  pinMode(bit5,OUTPUT);
  pinMode(bit6,OUTPUT);
  pinMode(bit7,OUTPUT);
  pinMode(bit8,OUTPUT);

  pinMode(light,OUTPUT);
  pinMode(fan,OUTPUT);
  starter();
}

void Main() {
  int entryDis=getDistanceINCH(eEntry,tEntry);
  int exitDis=getDistanceINCH(eExit,tExit);
  Serial.print("Entry distance : ");
  Serial.println(entryDis);
  Serial.print("Exit distance : ");
  Serial.println(exitDis);
  if(entryDis<gateWidth) count++,delay(1000);
  if(exitDis<gateWidth) count--,delay(1000);
  if(count<0) count=0;
  if(count) digitalWrite(fan,HIGH),digitalWrite(light,HIGH);
  else digitalWrite(fan,LOW),digitalWrite(light,LOW);
  display8Bit(count);
}

void loop() {
  Main();
}









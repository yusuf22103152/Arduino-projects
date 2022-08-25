String eight = A0;
String four = A1;
String two = A2;
String one = A4;
int decimal;
int delayTime=200; //animation delay time

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}



void convert() {
  if (decimal<16 && decimal>=0) {
    if (decimal>=8) {
    digitalWrite(eight, HIGH);
    delay(delayTime);
    digitalWrite(eight, LOW);
    delay(delayTime);
    digitalWrite(eight, HIGH);
    delay(delayTime);
    decimal -= 8;
    }
  if (decimal>=4) {
    digitalWrite(four, HIGH);
    delay(delayTime);
    digitalWrite(four, LOW);
    delay(delayTime);
    digitalWrite(four, HIGH);
    delay(delayTime);
    decimal -= 4; 
    }
  if (decimal>=2) {
    digitalWrite(two, HIGH);
    delay(delayTime);
    digitalWrite(two, LOW);
    delay(delayTime);
    digitalWrite(two, HIGH);
    delay(delayTime);
    decimal -= 2; 
    }
  if (decimal>=1) {
    digitalWrite(one, HIGH);
    delay(delayTime);
    digitalWrite(one, LOW);
    delay(delayTime);
    digitalWrite(one, HIGH);
    delay(delayTime);
    }
    
      }
  
  else {
    error();
    error();
    while(1);
  } 
  while(1);

       
  }



void error() {
  digitalWrite(eight, HIGH);
  digitalWrite(four, HIGH);
  digitalWrite(two, HIGH);
  digitalWrite(one, HIGH);
  delay(300);
  digitalWrite(eight, LOW);
  digitalWrite(four, LOW);
  digitalWrite(two, LOW);
  digitalWrite(one, LOW);
  delay(300);
  }




void loop(){

  decimal = 3;         //Input decimal  here and it will convert it to binary
  convert();
   
  
  }



    
  
  

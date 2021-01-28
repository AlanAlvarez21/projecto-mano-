#include <PIDController.h>
volatile long int encoder_pos =0 ,encoder_pos1 = 0;
PIDController pos_pid; 
PIDController pos1_pid; 
int motor_value = 255;

int lastpost,lastpost1;
unsigned int integerValue=0;  // Max value is 65535
char incomingByte;
void setup() {

  Serial.begin(9600);
  pinMode(2, INPUT);// c1 m1
  pinMode(3, INPUT);//c2 m2
   pinMode(4, INPUT);//
  pinMode(5, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
   pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), encoder, RISING);
  attachInterrupt(digitalPinToInterrupt(3), encoder1, RISING);
  pos_pid.begin();    
  pos_pid.tune(15, 1, 2000);   //
  pos_pid.limit(-255, 255);
  pos1_pid.begin();    
  pos1_pid.tune(15, 1, 2000);    
  pos1_pid.limit(-255, 255);
}

void loop() {

if (Serial.available() > 0) {  
    integerValue = 0; 
encoder_pos=lastpost;
encoder_pos1=lastpost1;
           
    while(1) {           
      incomingByte = Serial.read();
      if (incomingByte == '\n') break;   
      if (incomingByte == -1) continue;  
      integerValue *= 10;  
      integerValue = ((incomingByte - 48) + integerValue);
      pos_pid.setpoint(integerValue);
      pos1_pid.setpoint(integerValue);
      
    }
}

   motor_value = pos_pid.compute(encoder_pos);
if(motor_value > 0){
  MotorCounterClockwise(motor_value);
}else{
  MotorClockwise(abs(motor_value));
}
 motor_value = pos1_pid.compute(encoder_pos1);
if(motor_value > 0){
  MotorCounterClockwise1(motor_value);
}else{
  MotorClockwise1(abs(motor_value));
}
  Serial.println((String)encoder_pos+","+(String)encoder_pos1);
//   Serial.println(",");
  // Serial.println(encoder_pos1);
  delay(10);

 
}

void encoder1(){

  if(digitalRead(5) == HIGH){
    encoder_pos1++;
  }else{
    encoder_pos1--;
  }
   lastpost1=encoder_pos1;
}

void encoder(){

  if(digitalRead(4) == HIGH){
    encoder_pos++;
  }else{
    encoder_pos--;
  }
   
  lastpost=encoder_pos;
}

void MotorClockwise(int power){
  if(power > 100){
  analogWrite(9, power);
  digitalWrite(10, LOW);
  }else{
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
}
void MotorClockwise1(int power){
  if(power > 100){
  analogWrite(6, power);
  digitalWrite(11, LOW);
  }else{
    digitalWrite(6, LOW);
    digitalWrite(11, LOW);
  }
}

void MotorCounterClockwise(int power){
  if(power > 100){
  analogWrite(10, power);
  digitalWrite(9, LOW);
  }else{
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }
}
void MotorCounterClockwise1(int power){
  if(power > 100){
  analogWrite(11, power);
  digitalWrite(6, LOW);
  }else{
    digitalWrite(6, LOW);
    digitalWrite(11, LOW);
  }
}

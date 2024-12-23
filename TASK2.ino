//#include utilatomic.h // For the ATOMIC_BLOCK macro

#define ENCA 2  //YELLOW
#define ENCB 3  //WHITE
#define PWM 5
#define IN2 6
#define IN1 7
#define POT A0

volatile int posi = 0; // specify posi as volatile httpswww.arduino.ccreferenceenlanguagevariablesvariable-scope-qualifiersvolatile

void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(POT,INPUT);
  pinMode(EN,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
}

void loop() {
  
  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see httpswww.arduino.ccreferenceenlanguagevariablesvariable-scope-qualifiersvolatile
  int pos = 0; 
 

 int pot = analogRead(POT);
 int half = pot / 2;

 if (pot > half){
  setMotor(1, pot - half, PWM, IN1, IN2);
  delay(200);
  Serial.println(pos);
 }
 else if (pot < half) {
   setMotor(-1, half - pot, PWM, IN1, IN2);
  delay(200);
  Serial.println(pos);
 }

else {
  setMotor(0, 25, PWM, IN1, IN2);
  delay(20);
  Serial.println(pos);
}
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }
}

void readEncoder(){
  int b = digitalRead(ENCB);
  Serial.println(b);
  if(b  >0){
    posi++;
  }
  else{
    posi--;
  }
}
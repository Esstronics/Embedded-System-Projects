#define MotorA1 7
#define MotorA2 6
#define MotorB1 4
#define MotorB2 5
#define PWM     9


#define MotorAForward(pwm)    do{digitalWrite(MotorA1,HIGH); digitalWrite(MotorA2,LOW); analogWrite(PWM,pwm);} while(0)
#define MotorAStop       do{digitalWrite(MotorA1,LOW);  digitalWrite(MotorA2,LOW);} while(0)
#define MotorABackward(pwm)  do{digitalWrite(MotorA1,LOW);  digitalWrite(MotorA2,HIGH); analogWrite(PWM,pwm);}while(0)

#define MotorBForward(pwm)   do{digitalWrite(MotorB1,HIGH); digitalWrite(MotorB2,LOW); analogWrite(PWM,pwm);} while(0)
#define MotorBStop   do{digitalWrite(MotorB1,LOW);  digitalWrite(MotorB2,LOW);} while(0)
#define MotorBBackward(pwm) do{digitalWrite(MotorB1,LOW);  digitalWrite(MotorB2,HIGH); analogWrite(PWM,pwm);}while(0)
int Motor_PWM = 100;



void Front(void)
{
  MotorAForward(Motor_PWM);
  MotorBForward(Motor_PWM);
}

void Back(void)
{
  MotorABackward(Motor_PWM);  MotorBBackward(Motor_PWM);
}
void Right(void)
{ 
  MotorAForward(Motor_PWM);   MotorBBackward(Motor_PWM);
}
void Left(void)
{
  MotorABackward(Motor_PWM);  MotorBForward(Motor_PWM);
}


void setup() {
pinMode(MotorA1,OUTPUT);  pinMode(MotorA2,OUTPUT);
pinMode(MotorB1,OUTPUT);  pinMode(MotorB2,OUTPUT);
}

void loop() {
Back();
//digitalWrite(MotorA1,HIGH); digitalWrite(MotorA2,LOW);
}

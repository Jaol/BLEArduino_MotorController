#include <SPI.h>
#include <ble.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h>




#define I_InA1            6                  // INA motor pin
#define I_InB1            5                    // INB motor pin 
#define I_PWM1            4                   // PWM motor pin

#define II_InA1            3                  // INA motor pin
#define II_InB1            2                  // INB motor pin 
#define II_PWM1            1                   // PWM motor pin

 char fb;
 char lr;
  int I_PWM_val = 0;
  int II_PWM_val =0;
  int steeringActive = 0;
  int throttleActive = 0;
void setup() {

  
    // SETUP MOTOR 
 
  pinMode(I_InA1, OUTPUT);
  pinMode(I_InB1, OUTPUT);
  pinMode(I_PWM1, OUTPUT);
  
  pinMode(II_InA1, OUTPUT);
  pinMode(II_InB1, OUTPUT);
  pinMode(II_PWM1, OUTPUT); 
  Serial.begin(57600);
 
  
  // put your setup code here, to run once:
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  ble_begin();

 Serial.println("Forward = 1 / Backwards = 2 / or 'x' to clear");
  

}




void loop() {

  
  
  while(ble_available()){
       //byte motor1;
    byte valForMotor1;
    byte dirForMotor1;
 
    //byte motor2;
    byte valForMotor2;
    byte dirForMotor2;

    if(valForMotor1 = ble_read()){
     valForMotor1 = ble_read();
     dirForMotor1 = ble_read();
     valForMotor2 = ble_read();
     dirForMotor2 = ble_read();


   if (throttleActive == 1){
     fb = 'x';
     throttleActive = 0;
    }
    
     
    if(valForMotor1 != 99){
      throttleActive = 1;
      if(valForMotor1 == 255){
      fb = '1';
      } if(valForMotor1 == 0){
        fb = '2';
      }
    }
  
 if(steeringActive == 1){
    lr='s';
    steeringActive = 0;
    }


     if(valForMotor2 != 99){
       steeringActive = 1;
       if(valForMotor2 == 255){
      lr = '4';
      } 
      if(valForMotor2 == 0){
      lr = '6';
      }
}
  
   
 
// FORWARD BACKWARD //

    Serial.println(fb);
    if (fb >= '0' && fb <= '1')
    {
     motorForward(255);                        
    }
    if (fb >= '2' && fb <= '3')
    {
     motorBackward(255);
   
    }
    if (fb == 'x')
    {
    motorStop();
    Serial.println("throttlestop");
    }
   }
    
    
    // LEFT RIGHT //
     Serial.println(lr);
     if (lr >= '4' && lr <= '5')
    {
     motorIIBackward(255);
    }
      if (lr >= '6' && lr <= '7')
    {
   motorIIForward(255);
    }
  if (lr == 's')
    {
    motorIIStop();
      Serial.println("steering stop");
    }
    }

ble_do_events();
}

void motorForward(int I_PWM_val)  {
  analogWrite(I_PWM1, I_PWM_val);
  digitalWrite(I_InA1, LOW);
  digitalWrite(I_InB1, HIGH);
  Serial.println("motor forward");
}
void motorIIForward(int II_PWM_val)  {
  analogWrite(II_PWM1, II_PWM_val);
  digitalWrite(II_InA1, LOW);
  digitalWrite(II_InB1, HIGH);
  Serial.println("motor left");
}


void motorBackward(int I_PWM_val)  {
  analogWrite(I_PWM1, I_PWM_val);
  digitalWrite(I_InA1, HIGH);
  digitalWrite(I_InB1, LOW);
  Serial.println("motor backward");
}

void motorIIBackward(int II_PWM_val)  {
  analogWrite(II_PWM1, II_PWM_val);
  digitalWrite(II_InA1, HIGH);
  digitalWrite(II_InB1, LOW);
  Serial.println("motor right");
}

void motorStop()  {
  analogWrite(I_PWM1, 0);
  digitalWrite(I_InA1, LOW);
  digitalWrite(I_InB1, LOW);
}

void motorIIStop()  {
  analogWrite(II_PWM1, 0);
  digitalWrite(II_InA1, LOW);
  digitalWrite(II_InB1, LOW);
}



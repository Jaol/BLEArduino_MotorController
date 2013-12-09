#include <SPI.h>
#include <ble.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h>
#include "Boards.h"



#define I_InA1            10                  // INA motor pin
#define I_InB1            9                    // INB motor pin 
#define I_PWM1            8                   // PWM motor pin

#define II_InA1            13                  // INA motor pin
#define II_InB1            12                  // INB motor pin 
#define II_PWM1            11                   // PWM motor pin

void setup() {

  
    // SETUP MOTOR 
 
  pinMode(I_InA1, OUTPUT);
  pinMode(I_InB1, OUTPUT);
  pinMode(I_PWM1, OUTPUT);
  
  pinMode(II_InA1, OUTPUT);
  pinMode(II_InB1, OUTPUT);
  pinMode(II_PWM1, OUTPUT); 

  // put your setup code here, to run once:
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  ble_begin();

  Serial.begin(57600);
}

void motorForward(int I_PWM_val)  {
  analogWrite(I_PWM1, I_PWM_val);
  digitalWrite(I_InA1, LOW);
  digitalWrite(I_InB1, HIGH);
}
void motorIIForward(int II_PWM_val)  {
  analogWrite(II_PWM1, II_PWM_val);
  digitalWrite(II_InA1, LOW);
  digitalWrite(II_InB1, HIGH);
}


void motorBackward(int I_PWM_val)  {
  analogWrite(I_PWM1, I_PWM_val);
  digitalWrite(I_InA1, HIGH);
  digitalWrite(I_InB1, LOW);
}

void motorIIBackward(int II_PWM_val)  {
  analogWrite(II_PWM1, II_PWM_val);
  digitalWrite(II_InA1, HIGH);
  digitalWrite(II_InB1, LOW);
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

void loop() {
  // put your main code here, to run repeatedly: 


  if(ble_connected()){
   // digitalWrite(7,255); 
  }  

   

  
  while(ble_available()){
    
    
    
    
    //byte motor1;
    byte valForMotor1;
    byte dirForMotor1;
    
    //byte motor2;
    byte valForMotor2;
    byte dirForMotor2;
    
    if(valForMotor1 = ble_read()){
      //read the first number for the led to address, and the second for the value...

     dirForMotor1 = ble_read();
     
     valForMotor2 = ble_read();
     dirForMotor2 = ble_read();
     
     //digitalWrite(dir_a, dirForMotor1);
     //analogWrite(pwm_a, valForMotor1);
     
     //digitalWrite(dir_b, dirForMotor2);
     //analogWrite(pwm_b, valForMotor2);
    


     //Serial.print("dirForMotor1:");     
     //Serial.println(dirForMotor1);

      
     //Serial.print("valForMotor1:");     
     //Serial.println(valForMotor1);
      
     //Serial.print("valForMotor2:");     
     //Serial.println(valForMotor2);
     
     //Serial.print("dirForMotor2:");     
     //Serial.println(dirForMotor2);

      //Serial.println("-----");

//Serial.println(valForMotor1);
//Serial.println(valForMotor2);
// Go farward
if(valForMotor1 >= 240){
Serial.println("Going forward");
     motorForward(255);                        
    }else{
    motorStop();
    motorIIStop();
    }
if(valForMotor1 <= 50){
Serial.println("Going backwards");
 motorBackward(255);   
    }else{
    motorStop();
    motorIIStop();
    } 
   if(valForMotor2 >= 240){
Serial.println("Left");
//motorIIForward(100);   
    }else{
    motorStop();
    motorIIStop();
    }
   if(valForMotor2 <= 50){
Serial.println("Right");
//motorIIBackward(100);
    } else{
    motorStop();
    motorIIStop();
    }
    
  }
  }
  /*
  if(digitalRead(4) == LOW){
      Serial.println("HI");
       ble_write('1'); 
    }
  */
  if (!ble_connected())
  {
    digitalWrite(7, LOW);

    //analog_enabled = false;
    //digitalWrite(DIGITAL_OUT_PIN, LOW);
  }
  
  // Allow BLE Shield to send/receive data
  ble_do_events();
  //digitalWrite(RED, LOW);
}



#include <SPI.h>
#include <ble.h>
#include <boards.h>
//#include <ble_shield.h>
#include <ble_mini.h>
#include <services.h>

#define I_InA1            7                  // INA motor pin
#define I_InB1            6                   // INB motor pin 
#define I_PWM1            5                   // PWM motor pin

#define II_InA1            4                  // INA motor pin
#define II_InB1            3                  // INB motor pin 
#define II_PWM1            2                   // PWM motor pin

#define incomming         A1

int speedValue = 0;

unsigned char len = 0;
 char fb;
 char lr;
  int I_PWM_val = 0;
  int II_PWM_val =0;
  int steeringActive = 0;
  int throttleActive = 0;
  int currentPWM = 0;
  int running = 0;
  int steering = 0;
  unsigned char buf[16] = {0};
void setup() {

  
    // SETUP MOTOR 
 
  pinMode(I_InA1, OUTPUT);
  pinMode(I_InB1, OUTPUT);
  pinMode(I_PWM1, OUTPUT);
  
  pinMode(II_InA1, OUTPUT);
  pinMode(II_InB1, OUTPUT);
  pinMode(II_PWM1, OUTPUT); 
  
  pinMode(incomming, OUTPUT);
  
  Serial.begin(19200);
 
  
  // put your setup code here, to run once:
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  BLEMini_begin(57600);
  

 //Serial.println("Forward = 1 / Backwards = 2 / or 'x' to clear");
  

}




void loop() {
  
  while( BLEMini_available()){
       //byte motor1;
    byte valForMotor1;
    byte dirForMotor1;
 
    //byte motor2;
    byte valForMotor2;
    byte dirForMotor2;

byte speedVal;

    if(valForMotor1 = BLEMini_read()){
     valForMotor1 = BLEMini_read();
     dirForMotor1 = BLEMini_read();
     valForMotor2 = BLEMini_read();
     dirForMotor2 = BLEMini_read();



if(dirForMotor1 == 3){
speedValue = 255;
}if(dirForMotor1 == 4){
speedValue = 125;
}if(dirForMotor1 == 5){
speedValue = 55;
}


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
       steering = 1;
       if(valForMotor2 == 255){
      lr = '4';
      } 
      if(valForMotor2 == 0){
      lr = '6';
      }
}
  
   
 
// FORWARD BACKWARD //

    //Serial.println(fb);
    if (fb >= '0' && fb <= '1')
    {
       running = 1;
     motorForward(speedValue);                        
    }
    if (fb >= '2' && fb <= '3')
    {
       running = 2;
     motorBackward(speedValue);
   
    }
    if (fb == 'x')
    {
    motorStop();
    //Serial.println("throttlestop");
    }
   }
    
    
    // LEFT RIGHT //
     //Serial.println(lr);
     if (lr >= '4' && lr <= '5')
    {
     motorIIBackward(speedValue);
    }
      if (lr >= '6' && lr <= '7')
    {
   motorIIForward(speedValue);
    }
  if (lr == 's')
    {
    motorIIStop();
      //Serial.println("steering stop");
    }
    }

//ble_do_events();
}

void motorForward(int I_PWM_val)  {

  digitalWrite(I_InA1, LOW);
  digitalWrite(I_InB1, HIGH);
  //Serial.println("motor forward");
  digitalWrite(incomming, HIGH);
    // Propose acceleration loop: 
    analogWrite(I_PWM1, I_PWM_val);

sendData('1');

}
void motorIIForward(int II_PWM_val)  {
  analogWrite(II_PWM1, II_PWM_val);
  digitalWrite(II_InA1, LOW);
  digitalWrite(II_InB1, HIGH);
  //Serial.println("motor left");


}


void motorBackward(int I_PWM_val)  {
  // Deaccelerate
  

  digitalWrite(I_InA1, HIGH);
  digitalWrite(I_InB1, LOW);
  //Serial.println("motor backward");
  digitalWrite(incomming, LOW);
   analogWrite(I_PWM1, I_PWM_val);
  sendData('2');
}

void motorIIBackward(int II_PWM_val)  {
  analogWrite(II_PWM1, II_PWM_val);
  digitalWrite(II_InA1, HIGH);
  digitalWrite(II_InB1, LOW);
  //Serial.println("motor right");

  
}

void motorStop()  {
  running = 0;
  analogWrite(I_PWM1, 0);
  digitalWrite(I_InA1, LOW);
  digitalWrite(I_InB1, LOW);
  
  sendData('0');
}

void motorIIStop()  {
  analogWrite(II_PWM1, 0);
  digitalWrite(II_InA1, LOW);
  digitalWrite(II_InB1, LOW);
  
 
}

void sendData(int valueToSend){

 byte buf[1];
          buf[0] = valueToSend;
          BLEMini_write_bytes(buf, 1);
}



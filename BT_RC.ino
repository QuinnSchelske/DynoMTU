/*
 Barrett Anderies
 March 11, 2013
 This is a modified version of the PS3BT.ino example sketch by Kristian Lauszus
 For more information visit his blog: http://blog.tkjelectronics.dk/ or 
 send him an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>                                                    //Include the necessary libraries.
#include <Servo.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd); 

Servo servo1;                                                         //Create instances of type Servo. servo1 is the steering servo and servo2 is the ESC.
Servo servo2;

void setup() {
  Serial.begin(115200);                                              
  if (Usb.Init() == -1) {                                            
    Serial.print(F("\r\nOSC did not start"));
    while(1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));              
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  servo1.attach(5);                                                  //Steering servo on digital pin 5
  servo2.attach(3);                                                  //ESC on sigital pin 3
}
void loop() 
{
  Usb.Task();

  if(PS3.PS3Connected || PS3.PS3NavigationConnected) {
    
    servo1.write(map(PS3.getAnalogHat(RightHatX), 0, 255, 0, 180));
    servo2.write(map(PS3.getAnalogHat(LeftHatY), 0, 255, 180, 0));
  }
  else 
   {
    servo1.write(90);
    servo2.write(90);
   }
    
    if(PS3.getButtonClick(PS)) {
      PS3.disconnect();
   }
}

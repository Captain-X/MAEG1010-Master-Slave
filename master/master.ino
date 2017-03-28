/* Wire Master Send & Receive
//

// MAE1010 2017

it is re-wrote from the lab workshop
I2Cmaster_snd_rec

it is a demo by usig a Joystick 

X+ (0x01), X- (0x02)
Y+ (0x03), Y- (0x04)


*/

#include <stdio.h>
#include <Wire.h>    // must add in for i2c

#define SLV_id 8    // must define target slave address

int sndLED=13;    // define an LED tells command sent
char buf[40];     // for printing 

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master, NO need)
  Serial.begin(9600);           // start serial for output
}


void loop()
{
  route1();
  route2();
  playMusic();
  Master_I2Csend(SLV_id, 0x01);
  if(Master_I2Creceive()==0x01){
     route3();
     Master_I2Csend(SLV_id, 0x02);
  } 
}

void route1(){
  
}

void route2(){
  
}

void route3(){
  
}

void playMusic(){
  
}

// there are 6 byte sent, only the last one is command
void Master_I2Csend(byte id, byte value)
{
  Wire.beginTransmission(id); // transmit to device SLV_id
  Wire.write("cmd no is 0x"); // sends five bytes
  Wire.write(value);          // sends one byte
  Wire.endTransmission();     // stop transmitting
}

/*
  it is for receive
*/
byte Master_I2Creceive()
{
  Wire.requestFrom(SLV_id, 1);    // request 1 bytes from slave device

  while (Wire.available())   // slave may send less than requested
  {
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    return Wire.read();
  }
  delay(500);
}



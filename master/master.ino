/* Wire Master Send & Receive
// MAE1010 2017

*/

#include <stdio.h>
#include <Wire.h>    // must add in for i2c

#define SLV_id 8    // must define target slave address

int sndLED=13;    // define an LED tells command sent

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master, NO need)
  Serial.begin(9600);           // start serial for output


  //codes below only need to be executed once.
  route1();
  route2();
  playMusic();
  Master_I2Csend(SLV_id, 0x01);
  do{
    //leave blank to hold the master until the slave is done.
  }while(Master_I2Creceive()!=0x01);
  route3();
  Master_I2Csend(SLV_id, 0x02);
}

void loop()
{
  
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
    delay(500);
    return Wire.read();
  }
  
}



/* Wire Master Send & Receive
//

// MAE1010 2017

it is re-wrote from the lab workshop
I2Cslave_snd_rec

it is a demo by usig a Joystick 
Master : joystick

Slave : motors
DC1, DC2
SV1, SV2,SV3

X+ (0x01), X- (0x02)  for dc motor
Y+ (0x03), Y- (0x04)  for sv motors

HW assignment:
 DC MOTOR 1
 IN1  A2
 IN2  7
 PWM1 3

 DC MOTOR 2
 IN3  8
 IN4  12
 PWM2 6

 SV1  9
 SV2  10
 SV3  11
 by wkmok
 */

#include <stdio.h>
#include <Wire.h>
#include <Servo.h>

#define SLV_id 8

char inChar;

Servo sv1;  // create servo object to control a servo

int in1 = A2;
int in2 = 7;
int in3 = 8 ;
int in4 = 12 ;
int PWM1 = 3 ;
int PWM2 = 6 ;

int angle1=150;
int angle2=120;

byte gripped=0x00;
volatile byte cmd_no = 0;
volatile byte Ack = 0;

char buf[16];
//byte tmp_cmd_no=0;

// HW setup
void motorSetup()
{
  pinMode(13, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //PWM
  analogWrite (PWM1, 110);
  analogWrite (PWM2, 110);
  digitalWrite (in1, HIGH);
  digitalWrite (in2, HIGH);
  digitalWrite (in3, HIGH);
  digitalWrite (in4, HIGH);

  sv1.attach(9);
}

void setup()
{
  Wire.begin(SLV_id);                // init i2c bus with address SLV_id  = 8
  Wire.onReceive(slave_receiveEvent); // register event
  Wire.onRequest(slave_requestEvent); // register event
  Serial.begin(9600);           // start serial for output
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  motorSetup();
}

void loop()
{ 
  switch (cmd_no)
  {
    case 0x01 :   grip();
      break;
    case 0x02 :   sv1.write(angle1);
      break;
  }
  cmd_no = 0; // reset cmd_no
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void slave_receiveEvent(int howMany)
{
  while (Wire.available() > 1) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  cmd_no = Wire.read();    // receive byte as an integer
  Serial.println(cmd_no, HEX);        // print the integer
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void slave_requestEvent()
{
  Wire.write(gripped); // respond with message of 16 bytes
}


void grip(){
  sv1.write(angle1);
  delay(1000);
  DC_mtr(1, 200, 1, 0);
  delay(1000);
  sv1.write(angle2);
  gripped=0x01;
}



// for dc motor IO assignment 
void DC_mtr(byte motor_no, byte speedx, byte a1, byte a2)
{
  switch (motor_no)
  {
    case 1:
      digitalWrite (in1, a1);
      digitalWrite (in2, a2);
      analogWrite (PWM1, 200);
      delay(10); // overcome starting torque
      analogWrite (PWM1, speedx);

      break;
    case 2:
      digitalWrite (in3, a1);
      digitalWrite (in4, a2);
      analogWrite (PWM2, 200);
      delay(10); // overcome starting torque
      analogWrite (PWM2, speedx);
      break;

  }
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    inChar = (char)Serial.read();
  }
}




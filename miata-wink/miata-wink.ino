#include "OneButton.h"

#define PIN_INPUT1 D3
#define PIN_INPUT2 D4

#define leftup D1          // digital output pin for left headlight up
#define rightup D5          // digital output pin for right headlight up
#define leftdown D2         // digital output pin for left headlight down
#define rightdown D6         // digital output pin for right headlight down
#define origwire D7         // digital output pin for original wires relay

// Setup a new OneButton on pin PIN_INPUT2.
OneButton buttonLeft(PIN_INPUT1, true, true);
// Setup a new OneButton on pin PIN_INPUT2.
OneButton buttonRight(PIN_INPUT2, true, true);


// setup code here, to run once:
void setup() {
  // Setup the Serial port. see http://arduino.cc/en/Serial/IfSerial
  Serial.begin(115200);  
  Serial.println("Starting Wink Wink");

  // link the button 1 functions.
  buttonLeft.attachClick(LeftWink);
  buttonLeft.attachDoubleClick(MexicanWave);
  buttonLeft.attachLongPressStart(longPressStart1);
  //buttonLeft.attachLongPressStop(longPressStop1);
  //buttonLeft.attachDuringLongPress(longPress1);

  // link the button 2 functions.
  buttonRight.attachClick(RightWink);
  buttonRight.attachDoubleClick(doubleclick2);
  buttonRight.attachLongPressStart(mavackaStart);
  buttonRight.attachLongPressStop(mavackaEnd);
  buttonRight.attachDuringLongPress(mavackaHold);

  pinMode(origwire, OUTPUT);
  digitalWrite(origwire, HIGH);
  
  pinMode(leftup, OUTPUT);
  digitalWrite(leftup, HIGH);
  
  pinMode(rightup, OUTPUT);
  digitalWrite(rightup, HIGH);
   
  pinMode(leftdown, OUTPUT);    
  digitalWrite(leftdown, HIGH);
   
  pinMode(rightdown, OUTPUT);    
  digitalWrite(rightdown, HIGH);

}  // setup


// main code here, to run repeatedly:
void loop() {
  // keep watching the push buttons:
  buttonLeft.tick();
  buttonRight.tick();
  // You can implement other code in here or just wait a while
  delay(10);
}  // loop




// This function will be called once, when the buttonLeft is pressed for a long time.
void longPressStart1() {
  Serial.println("Button 1 longPress start");
}  // longPressStart1

// This function will be called often, while the buttonLeft is pressed for a long time.
void longPress1() {
  Serial.println("Button 1 longPress...");
}  // longPress1

// This function will be called once, when the buttonLeft is released after beeing pressed for a long time.
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
}  // longPressStop1

void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
}  // doubleclick2

void RightWink()
{
  Serial.print("Right Wink");  

  originalOFF();
   
  digitalWrite(rightup,  HIGH);
  digitalWrite(rightdown, LOW);
   
  delay(750); 
  digitalWrite(rightup, LOW);
  digitalWrite(rightdown, HIGH);
    
  delay(750);
  digitalWrite(leftup,  HIGH);
  digitalWrite(rightup,  HIGH);
  digitalWrite(leftdown, HIGH);
  digitalWrite(rightdown,HIGH);
  
  originalON();  
}
void LeftWink()
{
  Serial.print("LEft Wink");  

  originalOFF();
   
  digitalWrite(leftup,  HIGH);
  digitalWrite(leftdown, LOW);
   
  delay(750); 
  digitalWrite(leftup, LOW);
  digitalWrite(leftdown, HIGH);
    
  delay(750);
  digitalWrite(leftup,  HIGH);
  digitalWrite(rightup,  HIGH);
  digitalWrite(leftdown, HIGH);
  digitalWrite(rightdown,HIGH);
  
  originalON();  
}
void MexicanWave() {     
  Serial.print("Mexico!");  
  originalOFF();

  digitalWrite(leftdown,  LOW );
  delay(350);
  digitalWrite(rightdown,  LOW);
  delay(500);  

  digitalWrite(leftdown,  HIGH );
  digitalWrite(leftup, LOW);
  delay(250);

  digitalWrite(rightdown,  HIGH );
  digitalWrite(rightup, LOW);
  delay(750); 
  
  digitalWrite(leftup,  HIGH);
  digitalWrite(rightup,  HIGH);
  digitalWrite(leftdown, HIGH);
  digitalWrite(rightdown,HIGH);

  originalON();  
}

void mavackaStart() {     
  Serial.print("Mavacka START");  
 
  originalOFF(); 
}
void mavackaHold() {     
  Serial.print("Mavacka Hold");  
  digitalWrite(leftdown,  LOW );  
  digitalWrite(rightdown,  LOW);  
  digitalWrite(leftup,  LOW );  
  digitalWrite(rightup,  LOW);
}

void mavackaEnd() {     
  Serial.print("Mavacka End"); 

  originalON();  
}

void originalOFF()
{
  digitalWrite(origwire, LOW); 
  delay(100); 
}
void originalON()
{
  delay(100); 
  digitalWrite(origwire, HIGH);   
}
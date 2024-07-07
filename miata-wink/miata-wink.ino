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
  buttonRight.attachLongPressStart(longPressStart2);
  //buttonRight.attachLongPressStop(longPressStop2);
  //buttonRight.attachDuringLongPress(longPress2);

}  // setup


// main code here, to run repeatedly:
void loop() {
  // keep watching the push buttons:
  buttonLeft.tick();
  buttonRight.tick();
  // You can implement other code in here or just wait a while
  delay(10);
}  // loop


// ----- button 1 callback functions

// This function will be called when the buttonLeft was pressed 1 time (and no 2. button press followed).
void click1() {
  Serial.println("Button 1 click.");
}  // click1


// This function will be called when the buttonLeft was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
}  // doubleclick1


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

void click2() {
  Serial.println("Button 2 click.");
}  // click2


void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
}  // doubleclick2


void longPressStart2() {
  Serial.println("Button 2 longPress start");
}  // longPressStart2


void longPress2() {
  Serial.println("Button 2 longPress...");
}  // longPress2

void longPressStop2() {
  Serial.println("Button 2 longPress stop");
}  // longPressStop2

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
  delay(250);
  digitalWrite(rightdown,  LOW);
  delay(500);  

  digitalWrite(leftdown,  HIGH );
  digitalWrite(leftup, LOW);
  delay(250);

  digitalWrite(rightdown,  HIGH );
  digitalWrite(rightup, LOW);
  delay(500); 
  
  digitalWrite(leftup,  HIGH);
  digitalWrite(rightup,  HIGH);
  digitalWrite(leftdown, HIGH);
  digitalWrite(rightdown,HIGH);

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
void SerialTest()
{
  Serial.print("Serial TEST ONLY");  
}

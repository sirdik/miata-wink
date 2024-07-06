//miata headlight motor functions rev4


#define buttonPin D3       // analog input pin to use as a digital input
#define leftup D1          // digital output pin for left headlight up
#define rightup D5          // digital output pin for right headlight up
#define leftdown D2         // digital output pin for left headlight down
#define rightdown D6         // digital output pin for right headlight down
#define origwire D7         // digital output pin for right headlight down
// power variable
boolean ledVal = true;    // state of headlight power

//=================================================

void setup() {

  // Set button input pin
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH );

  //set output for relay interupting original wire
  pinMode(origwire, OUTPUT);
  digitalWrite(origwire, HIGH); 
   
   // Set LED output pins
   pinMode(leftup, OUTPUT);
   digitalWrite(leftup, ledVal);
   //digitalWrite(leftup, HIGH);

   pinMode(rightup, OUTPUT);
   digitalWrite(rightup, ledVal);
   
   pinMode(leftdown, OUTPUT);    
   digitalWrite(leftdown, ledVal);
   
   pinMode(rightdown, OUTPUT);    
   digitalWrite(rightdown, ledVal);
}

void loop() { 
  // Get button event and act accordingly
  
   int b = checkButton();
   if (b == 1) clickEvent();
   if (b == 2) doubleClickEvent();
   if (b == 3) holdEvent();
   if (b == 4) longHoldEvent();
  
}

//=================================================
// Events to trigger

void clickEvent()
{
   digitalWrite(origwire, LOW); 
   delay(100); 
   
   digitalWrite(leftup,  !ledVal);
   digitalWrite(leftdown, ledVal);
   
   delay(750); 
    digitalWrite(leftup, ledVal);
    digitalWrite(leftdown, !ledVal);
    
   delay(750);
    digitalWrite(leftup,  HIGH);
    digitalWrite(rightup,  HIGH);
    digitalWrite(leftdown, HIGH);
    digitalWrite(rightdown,HIGH);
  
  delay(100); 
  digitalWrite(origwire, HIGH);   
}
void doubleClickEvent() {
   ledVal = !ledVal;
   
   digitalWrite(origwire, LOW); 
   delay(100);

   digitalWrite(leftup,  ledVal );
   digitalWrite(rightup,  ledVal);
   digitalWrite(leftdown, !ledVal);
   digitalWrite(rightdown, !ledVal);
   
   delay(750);
    digitalWrite(leftup,  HIGH);
    digitalWrite(rightup,  HIGH);
    digitalWrite(leftdown, HIGH);
    digitalWrite(rightdown,HIGH);

    delay(100); 
  digitalWrite(origwire, HIGH);
}
void holdEvent() {
   ledVal = !ledVal;
   
   digitalWrite(origwire, LOW); 
   delay(100);

   digitalWrite(leftup,  !ledVal );
   digitalWrite(rightup,  ledVal);
   digitalWrite(leftdown, ledVal);
   digitalWrite(rightdown, !ledVal);
   
   delay(750);
    digitalWrite(leftup,  HIGH);
    digitalWrite(rightup,  HIGH);
    digitalWrite(leftdown, HIGH);
    digitalWrite(rightdown,HIGH);

  delay(100); 
  digitalWrite(origwire, HIGH);
}
void longHoldEvent() {
   ledVal = HIGH; 
  
  digitalWrite(origwire, LOW); 
  delay(100);

    digitalWrite(leftup, !ledVal);
    digitalWrite(rightup,  !ledVal);
    digitalWrite(leftdown, ledVal);
    digitalWrite(rightdown, ledVal);
    
   delay(750);
    digitalWrite(leftup,  HIGH);
    digitalWrite(rightup,  HIGH);
    digitalWrite(leftdown, HIGH);
    digitalWrite(rightdown,HIGH);

  delay(100); 
  digitalWrite(origwire, HIGH); 
    ledVal = false;
  
}
//==================================================

int debounce = 50;          // ms debounce period to prevent flickering when pressing or releasing the button
int DCgap = 250;            // max ms between clicks for a double click event
int holdTime = 500;        // ms hold period: how long to wait for press+hold event
int longHoldTime = 1500;    // ms long hold period: how long to wait for press+hold event

// Button variables
boolean buttonVal = HIGH;   // value read from button
boolean buttonLast = HIGH;  // buffered value of the button's previous state
boolean DCwaiting = false;  // whether we're waiting for a double click (down)
boolean DConUp = false;     // whether to register a double click on next release, or whether to wait and click
boolean singleOK = true;    // whether it's OK to do a single click
long downTime = -1;         // time the button was pressed down
long upTime = -1;           // time the button was released
boolean ignoreUp = false;   // whether to ignore the button release because the click+hold was triggered
boolean waitForUp = false;        // when held, whether to wait for the up event
boolean holdEventPast = false;    // whether or not the hold event happened already
boolean longHoldEventPast = false;// whether or not the long hold event happened already

int checkButton() {    
   int event = 0;
   buttonVal = digitalRead(buttonPin);
   // Button pressed down
   if (buttonVal == LOW && buttonLast == HIGH && (millis() - upTime) > debounce)
   {
       downTime = millis();
       ignoreUp = false;
       waitForUp = false;
       singleOK = true;
       holdEventPast = false;
       longHoldEventPast = false;
       if ((millis()-upTime) < DCgap && DConUp == false && DCwaiting == true)  DConUp = true;
       else  DConUp = false;
       DCwaiting = false;
   }
   // Button released
   else if (buttonVal == HIGH && buttonLast == LOW && (millis() - downTime) > debounce)
   {        
       if (not ignoreUp)
       {
           upTime = millis();
           if (DConUp == false) DCwaiting = true;
           else
           {
               event = 2;
               DConUp = false;
               DCwaiting = false;
               singleOK = false;
           }
       }
   }
   // Test for normal click event: DCgap expired
   if ( buttonVal == HIGH && (millis()-upTime) >= DCgap && DCwaiting == true && DConUp == false && singleOK == true && event != 2)
   {
       event = 1;
       DCwaiting = false;
   }
   // Test for hold
   if (buttonVal == LOW && (millis() - downTime) >= holdTime) {
       // Trigger "normal" hold
       if (not holdEventPast)
       {
           event = 3;
           waitForUp = true;
           ignoreUp = true;
           DConUp = false;
           DCwaiting = false;
           downTime = millis();
           holdEventPast = true;
       }
       // Trigger "long" hold
       if ((millis() - downTime) >= longHoldTime)
       {
           if (not longHoldEventPast)
           {
               event = 4;
               longHoldEventPast = true;
           }
       }
   }
   buttonLast = buttonVal;
   return event;
}
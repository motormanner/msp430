/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +3.3V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 modified Apr 27 2012
 by Robert Wessels
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = PUSH2;     // the number of the pushbutton pin
const int ledPin =  RED_LED;      // the number of the LED pin
int poti_in= 14;
int poti_buffer=0;

int out_1=5;
int out_2=6;
int out_3=7;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  pinMode(out_1, OUTPUT);      
  pinMode(out_2, OUTPUT);      
  pinMode(out_3, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);     
  pinMode(poti_in, INPUT);     
  
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  poti_buffer = analogRead(poti_in);
int output_drive = map(poti_buffer, 0, 1023, 0, 255);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
 // if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
    digitalWrite(out_1, 1);  
    digitalWrite(out_2, 1);  
    digitalWrite(out_3, 1);  
    delay(output_drive);

    digitalWrite(ledPin, 0);  
    digitalWrite(out_1, 0);  
    digitalWrite(out_2, 0);  
    digitalWrite(out_3, 0);  
    delay(500);
//  } 
//  else {
//    // turn LED off:
//    digitalWrite(ledPin, 1); 
//  }
}

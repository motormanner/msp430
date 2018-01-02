/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// most launchpads have a red LED
#define LED RED_LED

//see pins_energia.h for more LED definitions
#define gLED GREEN_LED
  int ido = 300;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);     
  pinMode(gLED, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(gLED, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(ido);               // wait for a second
  digitalWrite(gLED, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(ido);               // wait for a second
}

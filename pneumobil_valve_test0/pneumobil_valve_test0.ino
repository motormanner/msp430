int ValveMain_A = 2;
int ValveMain_B = 6;

int buttonState = 0;    
int delay_T = 1000;

void setup() {
  //pinMode(ledPin, OUTPUT);      
  pinMode(ValveMain_A, OUTPUT);
  pinMode(ValveMain_B, OUTPUT);
  digitalWrite(ValveMain_A, LOW);  
  digitalWrite(ValveMain_B, LOW);  

}

void loop(){

  digitalWrite(ValveMain_A, HIGH);  
  digitalWrite(ValveMain_B, LOW);  
delay(delay_T);
  digitalWrite(ValveMain_A, LOW);  
  digitalWrite(ValveMain_B, LOW);  
delay(delay_T);  
  digitalWrite(ValveMain_A, LOW);  
  digitalWrite(ValveMain_B, HIGH);  
delay(delay_T);
  digitalWrite(ValveMain_A, LOW);  
  digitalWrite(ValveMain_B, LOW);  
delay(delay_T);
}

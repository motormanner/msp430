int reed_out=6;
int reed_in=7;

int piston_in=9;
int piston_out=10;
int enable_run=0;

boolean in_flag=0;
boolean out_flag=1;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

const int buttonPin = PUSH2;     // the number of the pushbutton pin


int sensorValue = 0;
int outputValue = 0;  


void setup() {
Serial.begin(9600);

pinMode(piston_out, OUTPUT);
pinMode(piston_in, OUTPUT);  
pinMode(reed_out, INPUT_PULLUP);     
pinMode(reed_in, INPUT_PULLUP);     
pinMode(buttonPin, INPUT_PULLUP);     
}

void loop(){
  
  in_flag=digitalRead(reed_in);
  out_flag=digitalRead(reed_out);
  //enable_run=digitalRead(buttonPin);

  sensorValue = analogRead(analogInPin);            
  if (sensorValue>=15)enable_run=1;
  else enable_run=0;

  if (!in_flag and enable_run){
  digitalWrite(piston_out, HIGH); 
  digitalWrite(piston_in, LOW); 
  }
  
  if (!out_flag and enable_run){
  digitalWrite(piston_out, LOW); 
  digitalWrite(piston_in, HIGH); 
  
  }
  Serial.print("belul: ");
  Serial.print(digitalRead(reed_in));
  Serial.print(" , kivul: ");
  Serial.println(digitalRead(reed_out));
  Serial.print("sensor = " );                       
  Serial.println(sensorValue); 
  
  
/*
  buttonState = digitalRead(buttonPin);
 if (buttonState == HIGH) {     
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    digitalWrite(ledPin, LOW); 
  }
  
  */
}

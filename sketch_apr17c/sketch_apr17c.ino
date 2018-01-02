int heater_1=18;
int heater_2=19;

int in_1=14;
int in_2=15;
void setup()
{
pinMode (heater_1, OUTPUT);
pinMode (heater_2, OUTPUT);
pinMode (RED_LED, OUTPUT);
pinMode(PUSH2, INPUT_PULLUP);     
pinMode(in_1, INPUT);     
pinMode(in_2                                        , INPUT);     
Serial.begin(9600);
}

void loop()
{
  int set_out = digitalRead(PUSH2);
if (set_out){
digitalWrite(heater_1,0);
digitalWrite(heater_2,0);
digitalWrite(RED_LED,0);

}
else{
digitalWrite(heater_1,1);
digitalWrite(heater_2,1);
digitalWrite(RED_LED,1);
}
  
  delay(100);
  
Serial.print(analogRead(in_1));
Serial.print("..");
Serial.println(analogRead(in_2));
}

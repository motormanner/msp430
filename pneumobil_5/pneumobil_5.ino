
int ValveMain_A = 6;
int ValveMain_B = 7;
int out_stop_position=300;
int in_stop_position=20;
int state_p=0;
int mid_delay=15;

void setup()
{
Serial.begin(115200); 
  pinMode(ValveMain_A, OUTPUT);
  pinMode(ValveMain_B, OUTPUT);
  digitalWrite(ValveMain_A, LOW);  
  digitalWrite(ValveMain_B, LOW);  
}

void loop()
{
int PistonA_position = map(analogRead(A0),170,860,320,0);
int PistonB_position = map(analogRead(A3),170,860,320,0);
state_p=0;
Serial.println("----------------------");
if(PistonA_position >= out_stop_position)Serial.println("A_OUT");
if(PistonA_position <= in_stop_position)Serial.println("A_IN");
if(PistonB_position >= out_stop_position){
  Serial.println("B_OUT");
  state_p=1;
}
if(PistonB_position <= in_stop_position){
  Serial.println("B_IN");
  state_p=2;
  }
  
if (state_p==1){
digitalWrite(ValveMain_A,1);
digitalWrite(ValveMain_B,0);
//delay(mid_delay);
//digitalWrite(ValveMain_A,0);
//digitalWrite(ValveMain_B,0);
Serial.println("1");

}
else if(state_p==2){
digitalWrite(ValveMain_A,0);
digitalWrite(ValveMain_B,1);
//delay(mid_delay);
//digitalWrite(ValveMain_A,0);
//digitalWrite(ValveMain_B,0);
Serial.println("2");
}
else {
digitalWrite(ValveMain_A,0);
digitalWrite(ValveMain_B,0);
Serial.println("0");
}
delay(500);

}

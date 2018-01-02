boolean direction_flag=0;
uint8_t piston_state=0;

uint8_t reed_A1= 10;
uint8_t reed_B1= 9;
uint8_t reed_A2= 8;
uint8_t reed_B2= 7;

uint8_t valve_A1= 12;
uint8_t valve_B1= 19;
uint8_t valve_A2= 13;
uint8_t valve_B2= 18;

uint8_t delay_counter=0;
uint8_t pedal=2;
int throtle=0;

void setup()
{
  Serial.begin(9600);
pinMode(valve_A1, OUTPUT);      
pinMode(valve_B1, OUTPUT);      
pinMode(valve_A2, OUTPUT);      
pinMode(valve_B2, OUTPUT);      
digitalWrite(valve_A1,0);
digitalWrite(valve_B1,0);
digitalWrite(valve_A2,0);
digitalWrite(valve_B2,0);
pinMode(reed_A1, INPUT_PULLUP);     
pinMode(reed_B1, INPUT_PULLUP);     
pinMode(reed_A2, INPUT_PULLUP);     
pinMode(reed_B2, INPUT_PULLUP);     
pinMode(pedal, INPUT);     
Serial.println("test_run v2.0");
}

void loop()
{
  check_input();
  throtle=analogRead(pedal);
  if (piston_state==1)direction_flag=0;
  if (piston_state==3)direction_flag=1;
  if (!direction_flag)move_fw();
  if (direction_flag)move_bw();
  delay_cycle();
  Serial.println(throtle);
}


void move_fw(){
digitalWrite(valve_A2,0);
digitalWrite(valve_B1,0);
if (throtle>500)digitalWrite(valve_A1,1);
else digitalWrite(valve_A1,0);
digitalWrite(valve_B2,1);
}

void move_bw(){
digitalWrite(valve_A2,1);
if (throtle>500)digitalWrite(valve_B1,1);
else digitalWrite(valve_B1,0);
digitalWrite(valve_A1,0);
digitalWrite(valve_B2,0);
}

void check_input(){
if(!digitalRead(reed_A1) and !digitalRead(reed_B1) and digitalRead(reed_A2) and digitalRead(reed_B2)){
//Serial.println("hatul");
piston_state=1;
}

if(digitalRead(reed_A1) and digitalRead(reed_B1) and !digitalRead(reed_A2) and !digitalRead(reed_B2)){
//Serial.println("elol");
piston_state=3;
}

if(digitalRead(reed_A1) and digitalRead(reed_B1) and digitalRead(reed_A2) and digitalRead(reed_B2)){
//Serial.println("kozepen");
piston_state=2;
}

}



void delay_cycle(){
delay_counter=0;

}

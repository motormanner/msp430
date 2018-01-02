int s_input_array[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // first analog sensor
int loop_counter = 0; // second analog sensor
int thirdSensor = 0; // digital sensor
int inByte = 0; // incoming serial byte

void setup()
{
  Serial.begin(119200);
  Serial.println(" ");
  Serial.println("Ready to roll!");
}

void loop()
{
  
  get_input();
  send_output(); 
  loop_count();
  delay(1000);
}

void get_input(){

 if (Serial.available() > 0) {
    inByte = Serial.read();
    s_input_array[loop_counter]=inByte;
   }
}
void send_output(){
  for(int i=0; i<=15; i++){
    Serial.println(s_input_array[i]);
  }
  Serial.print("---");
  Serial.println(loop_counter);
}  
  
void loop_count(){
if(loop_counter<=14)loop_counter++;
else loop_counter=0;
}

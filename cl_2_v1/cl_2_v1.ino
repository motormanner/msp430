int X1=11;
int X2=10;
int X3=2;
int Y1=19;
int Y2=18;
int Y3=13;
int Y4=12;
int read_delay=20;
int button_press_flag=0;


int pressed_keys[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};


void setup()
{
  Serial.begin(115200);
  Serial.println("hohoo, hohoo!");

  pinMode(X1, OUTPUT); // digital sensor is on digital pin 2
  pinMode(X2, OUTPUT); // digital sensor is on digital pin 2
  pinMode(X3, OUTPUT); // digital sensor is on digital pin 2
  pinMode(Y1, INPUT_PULLDOWN); // digital sensor is on digital pin 2
  pinMode(Y2, INPUT_PULLDOWN); // digital sensor is on digital pin 2
  pinMode(Y3, INPUT_PULLDOWN); // digital sensor is on digital pin 2
  pinMode(Y4, INPUT_PULLDOWN); // digital sensor is on digital pin 2
}

void loop()
{
  /*
if (read_keys()){
Serial.println(button_press_flag);
button_press_flag=0;
}
else{
Serial.println("nop");
delay(333);}
*/

read_keys();
uart_send();



/*if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    // read first analog input:
    firstSensor = analogRead(A0);
    // read second analog input:
    secondSensor = analogRead(A1);
    // read switch, map it to 0 or 255L
    thirdSensor = map(digitalRead(2), 0, 1, 0, 255); 
    // send sensor values:
    Serial.print(firstSensor);
    Serial.print(",");
    Serial.print(secondSensor);
    Serial.print(",");
    Serial.println(thirdSensor); 
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0,0,0"); // send an initial string
    delay(300);
  }*/
}

int read_keys(){
read_segment_1();
read_segment_2();
read_segment_3();

delay(read_delay);
return(button_press_flag);
}

void uart_send(){

  
  for(int i=0; i<=12; i++){
    if(pressed_keys[i]){
      Serial.println(i);
      pressed_keys[i]=0;
      Serial.print("\r");
      delay(200);
    }
    //Serial.print(pressed_keys[i]);
    //delay(10);
  }
  
}

void read_segment_1(){
digitalWrite(X1,1);
digitalWrite(X2,0);
digitalWrite(X3,0);
if (digitalRead(Y1)) {
  pressed_keys[3]=1;
  button_press_flag++;
  }
if (digitalRead(Y2)) {
  pressed_keys[6]=1;
  button_press_flag++;
  //Serial.println("pecka");
  }
if (digitalRead(Y3)) {
  pressed_keys[9]=1;
  button_press_flag++;
  }
if (digitalRead(Y4)) {
  pressed_keys[11]=1;
  button_press_flag++;
  }
}
void read_segment_2(){

digitalWrite(X1,0);
digitalWrite(X2,1);
digitalWrite(X3,0);
if (digitalRead(Y1)) {
  pressed_keys[2]=1;
  button_press_flag++;
  }
if (digitalRead(Y2)) {
  pressed_keys[5]=1;
  button_press_flag++;
  }
if (digitalRead(Y3)) {
  pressed_keys[8]=1;
  button_press_flag++;
  }
if (digitalRead(Y4)) {
  pressed_keys[0]=1;
  button_press_flag++;
  }
}
void read_segment_3(){

digitalWrite(X1,0);
digitalWrite(X2,0);
digitalWrite(X3,1);
if (digitalRead(Y1)) {
  pressed_keys[1]=1;
  button_press_flag++;
  }
if (digitalRead(Y2)) {
  pressed_keys[4]=1;
  button_press_flag++;
  }
if (digitalRead(Y3)) {
  pressed_keys[7]=1;
  button_press_flag++;
  }
if (digitalRead(Y4)) {
  pressed_keys[10]=1;
  button_press_flag++;
  }
}

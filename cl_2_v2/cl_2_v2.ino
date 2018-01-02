int X1=11;
int X2=10;
int X3=2;
int Y1=19;
int Y2=18;
int Y3=13;
int Y4=12;
int beep=5;
int led_a=6;
int led_b=7;
int led_c=8;
int led_d=9;
int read_delay=20;
int button_press_flag=0;

char uart_input[7]={0,0,0,0,0,0,0};
int uart_input_counter=0;
int pressed_keys[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
boolean stringComplete = false;


void setup()
{
  Serial.begin(115200);
  Serial.println("Bubles, ready!");

  pinMode(X1, OUTPUT);
  pinMode(X2, OUTPUT);
  pinMode(X3, OUTPUT);
  pinMode(Y1, INPUT_PULLDOWN);
  pinMode(Y2, INPUT_PULLDOWN);
  pinMode(Y3, INPUT_PULLDOWN);
  pinMode(Y4, INPUT_PULLDOWN);
  pinMode(beep, OUTPUT);
  pinMode(led_a, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_c, OUTPUT);
  pinMode(led_d, OUTPUT);

  digitalWrite(X1, 0);
  digitalWrite(X2, 0);
  digitalWrite(X3, 0);
  digitalWrite(beep, 0);
  digitalWrite(led_a, 0);
  digitalWrite(led_b, 0);
  digitalWrite(led_c, 0);
  digitalWrite(led_d, 0);
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

  if (stringComplete) {
    stringComplete = false;
    check_content();
    clear_uart_input();
  }

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

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
        Serial.println(uart_input_counter);

    uart_input[uart_input_counter]= inChar;
    if(uart_input_counter<=5)uart_input_counter++;
    Serial.println(inChar);
    if (inChar == '\r') {
      //digitalWrite(GREEN_LED, 1);
      uart_input_counter=0;
    
    stringComplete = true;
    } 
  }
}

void clear_uart_input(){

for(int b=0; b<=5; b++)uart_input[b]=0;

}



void check_content(){
  if(uart_input[0]=='#'){
  if(uart_input[1]== 'E' && uart_input[2]=='C' && uart_input[3]=='H' && uart_input[4]=='O' && uart_input[5]=='0' ){
  Serial.println("echo");
  }
   if(uart_input[1]== 'E' && uart_input[2]=='C' && uart_input[3]=='H' && uart_input[4]=='O' && uart_input[5]=='1' ){
  Serial.println("V.:1.0");
  }
    if(uart_input[1]== 'B' && uart_input[2]=='E' && uart_input[3]=='E' && uart_input[4]=='P' && uart_input[5]=='0'){
  digitalWrite(beep, 0);
  Serial.println("beep OFF");
  }
    if(uart_input[1]== 'B' && uart_input[2]=='E' && uart_input[3]=='E' && uart_input[4]=='P' && uart_input[5]=='1'){
  digitalWrite(beep, 1);
  Serial.println("beep ON");
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='A' && uart_input[5]=='0'){
  Serial.println("led A OFF");
  digitalWrite(led_a, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='A' && uart_input[5]=='1'){
  Serial.println("led A ON");
  digitalWrite(led_a, 1);
  }
  
      if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='B' && uart_input[5]=='0'){
  Serial.println("led B OFF");
  digitalWrite(led_b, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='B' && uart_input[5]=='1'){
  Serial.println("led B ON");
  digitalWrite(led_b, 1);
  }
  
      if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='C' && uart_input[5]=='0'){
  Serial.println("led C OFF");
  digitalWrite(led_c, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='C' && uart_input[5]=='1'){
  Serial.println("led C ON");
  digitalWrite(led_c, 1);
  }
  
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='D' && uart_input[5]=='0'){
  Serial.println("led D OFF");
  digitalWrite(led_d, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='D' && uart_input[5]=='1'){
  Serial.println("led D ON");
  digitalWrite(led_d, 1);
  }
}
}

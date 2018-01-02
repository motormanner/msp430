
char uart_input[7]={0,0,0,0,0,0,0};
int uart_input_counter=0;

String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(GREEN_LED, OUTPUT); 
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print(uart_input[0]); 
    Serial.print(uart_input[1]); 
    Serial.print(uart_input[2]); 
    Serial.print(uart_input[3]); 
    Serial.print(uart_input[4]); 
    Serial.print(uart_input[5]); 
   // Serial.println(uart_input[6]); 
    
    stringComplete = false;
    check_content();
    clear_uart_input();
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
  Serial.println("beep0");
  }
    if(uart_input[1]== 'B' && uart_input[2]=='E' && uart_input[3]=='E' && uart_input[4]=='P' && uart_input[5]=='1'){
  Serial.println("beep1");
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='A' && uart_input[5]=='0'){
  Serial.println("leda0");
  digitalWrite(GREEN_LED, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='A' && uart_input[5]=='1'){
  Serial.println("leda1");
  digitalWrite(GREEN_LED, 1);
  }
  
      if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='B' && uart_input[5]=='0'){
  Serial.println("leda0");
  digitalWrite(RED_LED, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='B' && uart_input[5]=='1'){
  Serial.println("leda1");
  digitalWrite(RED_LED, 1);
  }
  
      if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='C' && uart_input[5]=='0'){
  Serial.println("ledC0");
  digitalWrite(GREEN_LED, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='C' && uart_input[5]=='1'){
  Serial.println("ledC1");
  digitalWrite(GREEN_LED, 1);
  }
  
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='D' && uart_input[5]=='0'){
  Serial.println("ledD0");
  digitalWrite(GREEN_LED, 0);
  }
    if(uart_input[1]== 'L' && uart_input[2]=='E' && uart_input[3]=='D' && uart_input[4]=='D' && uart_input[5]=='1'){
  Serial.println("ledD1");
  digitalWrite(GREEN_LED, 1);
  }
}
}

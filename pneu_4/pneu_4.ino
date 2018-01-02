int uart_incoming_register=0;
boolean uart_in_flag =0;
boolean uart_echo_flag=1;
char ascii_characters[127]={ '_','!','_','#','$','%','&','_','(',')','*','+','_','-','.','_','0','1','2','3','4','5','6','7','8','9',':','_','<','=','>','?','_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','_','_','_','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','_','|','_','~'};
int uart_buffer_in[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int uart_buffer_in_counter=0;
int uart_raw_flag=0;

void setup(){
Serial.begin(9600);
Serial.flush();
Serial.println(" ");
Serial.println("Device initializing");
}
//-----mainloop--------------------------------------------------------------------------
void loop(){
uart_check();
//uart_answer();
delay(103);
}

//-----otherfunctions----------------------------------------------------------------------------------
char to_ascii(int x){
  if (x >=32 and x<=126){
  return (ascii_characters[x-32]);
  }
  }

void uart_answer(){
  if(uart_raw_flag==1){
  for (int i=0; i<=31;i++){
    Serial.print(uart_buffer_in[i]);
    Serial.print("_");
    }

  }
  else{
      for (int j=0; j<=31;j++){
    Serial.print(to_ascii(uart_buffer_in[j]));
    Serial.print("_");
    }
   
    }
      Serial.println(" ");
}

void uart_check(){
if (Serial.available()>0){
  uart_incoming_register= Serial.read();
  uart_in_flag=1;
  }
if (uart_in_flag != 0){
  if (uart_buffer_in_counter<=31 and uart_buffer_in_counter>=0){
  uart_buffer_in[uart_buffer_in_counter]=uart_incoming_register;
  uart_buffer_in_counter++;
  //Serial.println(to_ascii(uart_incoming_register));
  uart_in_flag=0;
  }
  else Serial.println("buffer O F------------------------------------------------------------------");
  } 
  }

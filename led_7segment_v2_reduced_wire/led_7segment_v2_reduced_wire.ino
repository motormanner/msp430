/*
CONNECTOR:

0  :GND          -/GND
0  :Vcc          3.3V
0  :CLK          pin6/L_clk
0  :CLR(!)       pin7/L_clr
0  :B(SIGNAL)    pin8/L_signal
0  :A(SIGNAL)    3.3V
0  :NC
0  :NC
0  :NC
x  :(NO CABLE)


*/

int L_clk=6;
int L_serial=8;
int L_clr=7;

int delay_whait=500;
int delay_clk=5;
int delay_serial=5;
void setup() {     
  pinMode(L_clk, OUTPUT);     
  pinMode(L_serial, OUTPUT);     
  pinMode(L_clr, OUTPUT);     
led_7_segment_clear();
}



void loop() {
for (int i=0;i<=11;i++){
  led_print(i);
delay(delay_whait);
led_7_segment_clear();
delay(delay_whait);
}
}

void led_7_segment_clear(){
/*
digitalWrite(L_clr, HIGH);
delay(1);
digitalWrite(L_clr, LOW); 
delay(1);
digitalWrite(L_clr, HIGH);
delay(1);
*/
for (int i=0;i<=9;i++){
led_7_segment_cycle_L();
}
}

void led_7_segment_cycle(){
digitalWrite(L_clk, LOW);
  delayMicroseconds(delay_clk);
  digitalWrite(L_clk, HIGH);
  delayMicroseconds(delay_clk);
}

void led_7_segment_cycle_H(){
  digitalWrite(L_serial, HIGH);
  delayMicroseconds(delay_serial);
  led_7_segment_cycle();
}

void led_7_segment_cycle_L(){
  digitalWrite(L_serial, LOW);
  delayMicroseconds(delay_serial);
  led_7_segment_cycle();
}

void led_7_segment_n0(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
}

void led_7_segment_n1(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
}

void led_7_segment_n2(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n3(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n4(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
}

void led_7_segment_n5(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n6(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n7(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
}

void led_7_segment_n8(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n9(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_n10(){
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_7_segment_nE(){
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_L();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
  led_7_segment_cycle_H();
}

void led_print(int x){
  switch (x){
  case 0:led_7_segment_n0();
  break;
  case 1:led_7_segment_n1();
  break;
  case 2:led_7_segment_n2();
  break;
  case 3:led_7_segment_n3();
  break;
  case 4:led_7_segment_n4();
  break;
  case 5:led_7_segment_n5();
  break;
  case 6:led_7_segment_n6();
  break;
  case 7:led_7_segment_n7();
  break;
  case 8:led_7_segment_n8();
  break;
  case 9:led_7_segment_n9();
  break;
  case 10:led_7_segment_n10();
  break;
  default:led_7_segment_nE();
  }
}

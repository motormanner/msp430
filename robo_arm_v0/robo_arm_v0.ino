int SRVO_a =8 ;
int SRVO_b =9 ;
int SRVO_c =10 ;
int SRVO_d =13 ;
int SRVO_e =12 ;
int SRVO_f =11 ;

int a_time=1500;
//int min_b = 400;
//int max_b = 2600;

void setup()
{
  pinMode(SRVO_a, OUTPUT);     
  pinMode(SRVO_b, OUTPUT);     
  pinMode(SRVO_c, OUTPUT);     
  pinMode(SRVO_d, OUTPUT);     
  pinMode(SRVO_e, OUTPUT);     
  pinMode(SRVO_f, OUTPUT);     

}

void loop()
{
//move_a(400,2600,5);
//move_b(400,2600,5);
//move_c(500,2300,5);
//move_d(400,2600,3);
move_e(450,2600,2);
move_f(500,2300,2);
}

void move_a(int min_a,int max_a,int stp){
for(int i=min_a;i<=max_a;i=i+stp){
   digitalWrite(SRVO_a, HIGH);
   delayMicroseconds(i);
   digitalWrite(SRVO_a, LOW);
   delayMicroseconds(20000-i);
}
for(int i=max_a;i>=min_a;i=i-stp){
   digitalWrite(SRVO_a, HIGH);
   delayMicroseconds(i);  
   digitalWrite(SRVO_a, LOW);
   delayMicroseconds(20000-i);
}
}

void move_b(int min_b,int max_b, int stp){
for(int i=min_b;i<=max_b;i=i+stp){
   digitalWrite(SRVO_b, HIGH);
   delayMicroseconds(i);
   digitalWrite(SRVO_b, LOW);
   delayMicroseconds(20000-i);
}
for(int i=max_b;i>=min_b;i=i-stp){
   digitalWrite(SRVO_b, HIGH);
   delayMicroseconds(i);  
   digitalWrite(SRVO_b, LOW);
   delayMicroseconds(20000-i);
}
}

void move_c(int min_c,int max_c,int stp){
for(int i=min_c;i<=max_c;i=i+stp){
   digitalWrite(SRVO_c, HIGH);
   delayMicroseconds(i);
   digitalWrite(SRVO_c, LOW);
   delayMicroseconds(20000-i);
}
for(int i=max_c;i>=min_c;i=i-stp){
   digitalWrite(SRVO_c, HIGH);
   delayMicroseconds(i);  
   digitalWrite(SRVO_c, LOW);
   delayMicroseconds(20000-i);
}
}


void move_d(int min_d,int max_d,int stp){
for(int i=min_d;i<=max_d;i=i+stp){
   digitalWrite(SRVO_d, HIGH);
   delayMicroseconds(i);
   digitalWrite(SRVO_d, LOW);
   delayMicroseconds(20000-i);
}
for(int i=max_d;i>=min_d;i=i-stp){
   digitalWrite(SRVO_d, HIGH);
   delayMicroseconds(i);  
   digitalWrite(SRVO_d, LOW);
   delayMicroseconds(20000-i);
}
}


void move_e(int min_e,int max_e,int stp){
for(int i=min_e;i<=max_e;i=i+stp){
   digitalWrite(SRVO_e, HIGH);
   delayMicroseconds(i);
   digitalWrite(SRVO_e, LOW);
   delayMicroseconds(20000-i);
}
for(int i=max_e;i>=min_e;i=i-stp){
   digitalWrite(SRVO_e, HIGH);
   delayMicroseconds(i);  
   digitalWrite(SRVO_e, LOW);
   delayMicroseconds(20000-i);
}
}


void move_f(int min_f,int max_f,int stp){
for(int i=min_f;i<=max_f;i=i+stp){
   digitalWrite(SRVO_f, HIGH);
   delayMicroseconds(i);
   digitalWrite(SRVO_f, LOW);
   delayMicroseconds(20000-i);
}
for(int i=max_f;i>=min_f;i=i-stp){
   digitalWrite(SRVO_f, HIGH);
   delayMicroseconds(i);  
   digitalWrite(SRVO_f, LOW);
   delayMicroseconds(20000-i);
}
}

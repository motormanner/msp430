void setup()
{
Serial.begin(115200); 
}

void loop()
{
int PistonA_position = analogRead(A0);
int PistonB_position = analogRead(A3);

  //Serial.println(" ");
  Serial.println(" ");
  Serial.print("Henger A: ");
  Serial.println(map(PistonA_position,170,860,320,0));
  Serial.print("Henger B: ");
  Serial.println(map(PistonB_position,170,860,320,0));
  //Serial.println(" ");
  //Serial.println(" ");  
  delay(100);  
}

int rpm = 950;
int ect = 68;
int lambda = 1337;
int mappress = 60;
int battery = 13337;
int wait = 20;

void setup() {
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.print(rpm);
   Serial.print("\t");
   
   Serial.print(ect);
   Serial.print("\t");
   
   Serial.print(lambda);
   Serial.print("\t");
   
   Serial.print(mappress);
   Serial.print("\t");

   Serial.print(battery);
   Serial.println("");

   rpm+=100;
   ect+=1;
   lambda+=777;
   mappress+=10;

   if (rpm > 10000)
   rpm = 950;

   if (ect > 75)
   ect = 68;

   if (lambda > 15000)
   lambda = 1337;

   if (mappress > 200)
   mappress = 60;
   delay(wait);
}

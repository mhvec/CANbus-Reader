int rpm = 950;
int ect = 68;
int lambda = 0;
int mappress = 100;
int wait = 20;

void setup() {
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
   Serial.print("ECT: ");
   Serial.print(ect);
   Serial.print("    ");
   Serial.print("Lambda: ");
   Serial.print(lambda);
   Serial.print("    ");
   Serial.print("MAP: ");
   Serial.print(mappress);
   Serial.print("    ");
   Serial.print("RPM: ");
   Serial.print(rpm);
   Serial.println("");

   rpm+=5;
   ect+=1;
   lambda+=1;
   mappress+=1;

   if (rpm > 8200)
   rpm = 950;

   if (ect > 75)
   ect = 68;

   if (lambda > 9)
   lambda = 0;

   if (mappress > 200)
   mappress = 100;
   delay(wait);
}

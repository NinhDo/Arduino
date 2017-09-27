// Bestemmer hvilken analog input som skal brukes
const int sensorPin = A0;
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  // Les verdien som kommer fra sensoren. Verdien er mellom 0 og 1024
  int value = analogRead(sensorPin);
 
  Serial.println(value);
  // Vent ett halvt sekund før vi går videre
  delay(500);
}
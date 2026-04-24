void setup() {
  pinMode(11, OUTPUT); // Rojo
  pinMode(12, OUTPUT); // Amarillo
  pinMode(13, OUTPUT); // Verde
}

void loop() {
  // LED rojo
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(1500);

  // LED amarillo
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delay(1500);

  // LED verde
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delay(1500);
}
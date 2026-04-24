#define SIG_PIN 9
#define BUZZER_PIN 6

void setup() {
  pinMode(SIG_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration;
  float distance;

  // Enviar pulso ultrasónico
  pinMode(SIG_PIN, OUTPUT);
  digitalWrite(SIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SIG_PIN, LOW);

  // Leer eco
  pinMode(SIG_PIN, INPUT);
  duration = pulseIn(SIG_PIN, HIGH);

  // Convertir a cm
  distance = duration * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Control del buzzer según distancia
  if (distance > 0 && distance < 10) {
    tone(BUZZER_PIN, 2000);   // muy cerca
  } 
  else if (distance < 20) {
    tone(BUZZER_PIN, 1500);
    delay(100);
    noTone(BUZZER_PIN);
    delay(100);
  } 
  else if (distance < 40) {
    tone(BUZZER_PIN, 1000);
    delay(200);
    noTone(BUZZER_PIN);
    delay(200);
  } 
  else {
    noTone(BUZZER_PIN); // lejos
  }

  delay(100);
}

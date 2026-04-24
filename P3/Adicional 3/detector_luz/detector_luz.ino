#define LDR_PIN A0
#define LED_PIN 9

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int luz = analogRead(LDR_PIN); // 0 - 1023

  Serial.print("Luz: ");
  Serial.println(luz);

  // Invertimos:
  // más luz ambiental a menos LED
  int brillo = map(luz, 0, 1023, 255, 0);

  // hacer curva más agresiva
  brillo = (brillo * brillo) / 255;

  analogWrite(LED_PIN, brillo);

  delay(50);
}

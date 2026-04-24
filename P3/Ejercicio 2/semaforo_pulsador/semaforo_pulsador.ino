const int boton = 7;

void setup() {
  pinMode(11, OUTPUT); // Rojo
  pinMode(12, OUTPUT); // Amarillo
  pinMode(13, OUTPUT); // Verde

  pinMode(boton, INPUT_PULLUP);
}

void loop() {
  int estadoBoton = digitalRead(boton);

  if (estadoBoton == LOW) {
    // Botón pulsado → solo rojo
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  } else {
    // Secuencia normal

    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    delay(1500);

    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    delay(1500);

    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    delay(1500);
  }
}

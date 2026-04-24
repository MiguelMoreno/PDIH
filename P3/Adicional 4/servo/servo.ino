#include <Servo.h>

#define BUTTON_PIN 2
#define SERVO_PIN 9

Servo servo;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  servo.attach(SERVO_PIN);
  servo.write(0);
}

void loop() {
  int estado = digitalRead(BUTTON_PIN);

  if (estado == LOW) {
    servo.write(90);
  } else {
    servo.write(0);
  }
}

# Práctica 3 - Arduino: Entrada y Salida Digital

**Alumno:** Miguel Moreno Murcia  
**Curso/Grupo:** 4º  
**Asignatura:** PDIH

---

# 1. Introducción

En esta práctica se ha trabajado con la plataforma Arduino con el objetivo de comprender el funcionamiento de las entradas y salidas digitales.

Se han desarrollado varios proyectos básicos basados en el control de LEDs, pulsadores y sensores, utilizando tanto simulación en Tinkercad como implementación en hardware real.

Además dentor de la carpeta de cada ejercicio se incluyen videos demostrativos de cada uno de los ellos.

---

# 2. Componentes utilizados

- Arduino UNO  
- LEDs (rojo, amarillo, verde)  
- Resistencias de 220Ω  
- Pulsador  
- Sensor LDR (fotorresistencia)  
- Protoboard  
- Cables de conexión
- Sensor ultrasónico (HC-SR04)
- Servomotor

---

# 3.1 Proyecto 1: Secuencia de LEDs

## 3.1.1 Descripción

Se ha implementado un programa que enciende y apaga tres LEDs (rojo, amarillo y verde) de forma secuencial, simulando un semáforo. Cada LED permanece encendido durante 1.5 segundos.

---

## 3.1.2 Esquema de montaje

<p align="center">
  <img src="./Ejercicio 1/montaje1.png" width="500">
</p>

---

## 3.1.3 Código

```cpp
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

```
---

## 3.1.4 Resultado

<p align="center">
  <img src="./Ejercicio 1/IMG_20260424_174850.jpg" width="500">
</p>

---

# 3.2 Proyecto 2: Control de LED con pulsador

## 3.2.1 Descripción

En este proyecto se amplía el anterior incorporando un pulsador que permite activar o desactivar el LED rojo conectado al pin digital 11. Cuando el pulsador está presionado, el LED rojo se enciende y los LEDs amarillo y verde permanecen apagados.

---

## 3.2.2 Esquema de montaje

<p align="center">
  <img src="./Ejercicio 2/montaje2.png" width="500">
</p>

---

## 3.2.3 Código

```cpp
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
    // Botón pulsado a solo rojo
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

```
---

## 3.2.2 Esquema de montaje

<p align="center">
  <img src="./Ejercicio 2/IMG_20260424_175157.jpg" width="500">
</p>

---

# 3.3 Proyecto 3: Secuencia de LEDs tipo “Coche fantástico”

## 3.3.1 Descripción

En este proyecto se implementa una secuencia de LEDs que simula el efecto de las luces del coche fantástico. Para ello, se encienden y apagan cuatro LEDs de forma secuencial, generando un efecto de desplazamiento de luz de izquierda a derecha y viceversa.


---

## 3.2.4 Resultado

<p align="center">
  <img src="./Adicional 1/montaje3.png" width="500">
</p>

---

## 3.3.3 Código

```cpp
int leds[] = {13, 12, 11, 10};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Ida (izquierda a derecha)
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
    delay(150);
    digitalWrite(leds[i], LOW);
  }

  // Vuelta (derecha a izquierda)
  for (int i = 2; i > 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(150);
    digitalWrite(leds[i], LOW);
  }
}

```

---

## 3.3.4 Resultado

<p align="center">
  <img src="./Adicional 1/IMG_20260424_175643.jpg" width="500">
</p>

---

# 3.4 Proyecto 4: Detector de distancia con sensor ultrasónico

## 3.4.1 Descripción

En este proyecto se implementa un sistema de medición de distancia utilizando un sensor ultrasónico (HC-SR04). El sistema mide la distancia a un objeto y la muestra por el monitor serie.

Además, se añade una señal acústica mediante un buzzer que varía su frecuencia en función de la distancia detectada: cuanto más cerca está el objeto, más rápido suena el pitido.


---

## 3.4.2 Esquema de montaje

<p align="center">
  <img src="./Adicional 2/montaje4.png" width="500">
</p>

---

## 3.4.3 Código

```cpp
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

```

---

## 3.4.4 Resultado

<p align="center">
  <img src="./Adicional 2/IMG_20260424_180032.jpg" width="500">
</p>

---

# 3.5 Proyecto 5: Detector de luz con LDR

## 3.5.1 Descripción

En este proyecto se implementa un sistema de detección de luz utilizando una fotorresistencia (LDR). El objetivo es medir la cantidad de luz ambiental y controlar la intensidad de un LED en función de dicha medida.

Cuando hay mucha luz ambiental, el LED se atenúa, y cuando hay poca luz, el LED aumenta su brillo.

---

## 3.5.2 Esquema de montaje

<p align="center">
  <img src="./Adicional 3/montaje5.png" width="500">
</p>

---

## 3.5.3 Código

```cpp
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

```
---

## 3.5.2 Esquema de montaje

<p align="center">
  <img src="./Adicional 3/IMG_20260424_180857.jpg" width="500">
</p>

---

# 3.6 Proyecto 6: Control de motor servo con pulsador

## 3.6.1 Descripción

En este proyecto se implementa el control de un motor servo mediante un pulsador. Cuando el usuario presiona el botón, el servo se activa y se mueve a una posición determinada (por ejemplo 90° o 180°).
---

## 3.6.2 Esquema de montaje

<p align="center">
  <img src="./Adicional 4/montaje6.png" width="500">
</p>

---

## 3.6.3 Código

```cpp
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

```
---

## 3.6.2 Esquema de montaje

<p align="center">
  <img src="./Adicional 4/IMG_20260424_181522.jpg" width="500">
</p>

---
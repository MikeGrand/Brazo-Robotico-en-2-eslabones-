#include <Servo.h>

const float DEG_A_RAD = PI / 180.0;
const float RAD_A_DEG = 180.0 / PI;

Servo servoBase;
Servo servoCodo;

float longEslabon1 = 8;
float longEslabon2 = 6;

// Coordenadas de destino y ángulos actuales
float coordX, coordY;
float angBaseActual = 0, angCodoActual = 0;
float angBaseDestino, angCodoDestino;

// Tiempo estimado para que el servo gire 90°
const int tiempoGiro90 = 1000; 

void setup() {
  Serial.begin(9600);
  servoBase.attach(9);
  servoCodo.attach(10);

  Serial.println("Brazo robótico listo.");
  Serial.println("Ingrese coordenadas X Y:");
}

// Calcula el ángulo del codo segundo eslabón
float calcularAnguloCodo(float x, float y) {
  float numerador = (x * x) + (y * y) - (longEslabon1 * longEslabon1) - (longEslabon2 * longEslabon2);
  float denominador = 2 * longEslabon1 * longEslabon2;
  float cosAngulo = numerador / denominador;

  // Verifica que el valor esté en el rango válido en este caso [-1, 1]
  cosAngulo = constrain(cosAngulo, -1.0, 1.0);
  return acos(cosAngulo) * RAD_A_DEG;
}

// Calcula el ángulo de la base (primer eslabón)
float calcularAnguloBase(float x, float y, float angCodo) {
  float parte1 = atan2(y, x);
  float parte2 = atan2(longEslabon2 * sin(angCodo * DEG_A_RAD),
                       longEslabon1 + longEslabon2 * cos(angCodo * DEG_A_RAD));
  return (parte1 - parte2) * RAD_A_DEG;
}

// Comprueba si la coordenada está dentro del alcance del brazo
bool dentroDelAlcance(float x, float y) {
  float distancia = sqrt(x * x + y * y);
  return distancia <= (longEslabon1 + longEslabon2);
}

// Simula el movimiento de un servo de rotación continua
void moverServoContinuo(Servo &servo, float angInicio, float angDestino) {
  float diferencia = angDestino - angInicio;
  if (fabs(diferencia) < 1.0) return; // movimiento pequeño → ignorar

  int direccion = (diferencia > 0) ? 1 : -1;
  int tiempoMovimiento = abs(diferencia) * tiempoGiro90 / 90.0;

  // Control de dirección
  servo.write(direccion > 0 ? 180 : 0);
  delay(tiempoMovimiento);
  servo.write(90); // detener
}

void loop() {
  if (Serial.available() > 0) {
    coordX = Serial.parseFloat();
    coordY = Serial.parseFloat();
    while (Serial.available() > 0) Serial.read(); // limpiar buffer

    if (coordX == 0 && coordY == 0) {
      Serial.println("Entrada inválida. Intente nuevamente.");
      return;
    }

    Serial.print("→ Coordenadas ingresadas: (");
    Serial.print(coordX);
    Serial.print(", ");
    Serial.print(coordY);
    Serial.println(")");

    if (dentroDelAlcance(coordX, coordY)) {
      angCodoDestino = calcularAnguloCodo(coordX, coordY);
      angBaseDestino = calcularAnguloBase(coordX, coordY, angCodoDestino);

      Serial.print("Ángulo base: ");
      Serial.println(angBaseDestino);
      Serial.print("Ángulo codo: ");
      Serial.println(angCodoDestino);

      moverServoContinuo(servoBase, angBaseActual, angBaseDestino);
      moverServoContinuo(servoCodo, angCodoActual, angCodoDestino);

      angBaseActual = angBaseDestino;
      angCodoActual = angCodoDestino;
    } else {
      Serial.println("Coordenada fuera de alcance del brazo.");
    }

    Serial.println("Ingrese las siguientes coordenadas (X Y):");
  }
}

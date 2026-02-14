# Brazo-Robotico-en-2-eslabones-
Brazo robótico 2DOF con Arduino que utiliza cinemática inversa para posicionar el efector final a partir de coordenadas (X, Y) ingresadas por el monitor serial, controlando dos servos de rotación continua.

Este proyecto implementa un brazo robótico de 2 grados de libertad (2DOF) utilizando Arduino y dos servomotores:

Servo Base (rotación horizontal)

Servo Codo (articulación intermedia)

El sistema utiliza cinemática inversa para calcular automáticamente los ángulos necesarios para alcanzar una coordenada específica (X, Y) en el plano cartesiano, el usuario introduce coordenadas por el Monitor Serial, y el brazo se mueve automáticamente hacia esa posición si está dentro del alcance físico.

¿Qué hace el usuario? El usuario (operador del sistema):

Abre el Monitor Serial, ingresa coordenadas en formato: X Y

Ejemplo: 6 5

Presiona Enter.

El sistema: 

- Valida las coordenadas
- Calcula los ángulos necesarios
- Mueve el brazo automáticamente
- Si la coordenada está fuera del alcance, el sistema lo notifica.

## Funcionamiento Interno del Código
Definición de Parámetros Físicos
float longEslabon1 = 8;
float longEslabon2 = 6;
Se definen las longitudes de los dos eslabones del brazo:
Eslabón 1: 8 unidades
Eslabón 2: 6 unidades
Estas medidas determinan el alcance máximo del brazo.

## Conversión de Ángulos
const float DEG_A_RAD = PI / 180.0;
const float RAD_A_DEG = 180.0 / PI;
Se definen constantes para convertir entre:

- Grados → Radianes

- Radianes → Grados

Necesario porque:

- sin(), cos(), atan2() trabajan en radianes

- Los servos trabajan en grados

## Ciclo Principal (loop())

El programa:

- Espera datos del Monitor Serial

- Lee X e Y

- Valida que no sean 0 0

- Verifica alcance

- Calcula ángulos

- Mueve los servos

- Actualiza ángulos actuales

Solicita nuevas coordenadas

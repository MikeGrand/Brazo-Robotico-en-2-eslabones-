# Brazo-Robotico-en-2-eslabones-
Brazo robótico 2DOF con Arduino que utiliza cinemática inversa para posicionar el efector final a partir de coordenadas (X, Y) ingresadas por el monitor serial, controlando dos servos de rotación continua.

Este proyecto implementa un brazo robótico de 2 grados de libertad (2DOF) utilizando Arduino y dos servomotores:

Servo Base (rotación horizontal)

Servo Codo (articulación intermedia)

El sistema utiliza cinemática inversa para calcular automáticamente los ángulos necesarios para alcanzar una coordenada específica (X, Y) en el plano cartesiano, el usuario introduce coordenadas por el Monitor Serial, y el brazo se mueve automáticamente hacia esa posición si está dentro del alcance físico.


#include <Wire.h>
#include <LIDARLite.h>

// Variables globales
LIDARLite lidarLite;
int distanciaAnterior = 0;

void setup() {
  Serial.begin(115200); // Inicializa la conexión serial para mostrar las lecturas de distancia
  
  lidarLite.begin(0, true); // Establece la configuración predeterminada y I2C a 400 kHz
  lidarLite.configure(0); // Cambia este número para probar configuraciones alternativas
}

void loop() {
  int dist = lidarLite.distance(); // Toma una medición de la distancia
  
  // Calcula la variación de distancia
  int variacion = dist - distanciaAnterior;
  
  // Guarda la distancia actual como la distancia anterior
  distanciaAnterior = dist;
  
  // Muestra la distancia y la variación en tiempo real
  Serial.print("Distancia: ");
  Serial.print(dist);
  Serial.print(" cm");
  Serial.print(" | Variacion: ");
  Serial.println(variacion);
  
  delay(100); // Espera 100 ms antes de tomar la siguiente medición
}

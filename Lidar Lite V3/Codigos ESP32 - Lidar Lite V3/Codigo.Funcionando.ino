#include <Wire.h>
#include <LIDARLite.h>

// Globales
LIDARLite lidarLite;
int cal_cnt = 0;

void setup()
{
  Serial.begin(115200); // Inicializa la conexión serial para mostrar las lecturas de distancia

  lidarLite.begin(0, true); // Establece la configuración predeterminada y I2C a 400 kHz
  lidarLite.configure(0); // Cambie este número para probar configuraciones alternativas
}

void loop()
{
  int dist;

  // Al principio de cada 100 lecturas,
  // tome una medición con corrección de sesgo de receptor
  if (cal_cnt == 0) {
    dist = lidarLite.distance(); // Con corrección de sesgo
  } else {
    dist = lidarLite.distance(false); // Sin corrección de sesgo
  }

  // Incrementa el contador de lecturas
  cal_cnt++;
  cal_cnt = cal_cnt % 100;

  // Muestra la distancia
  Serial.print(dist);
  Serial.println(" cm");

  delay(10);
}

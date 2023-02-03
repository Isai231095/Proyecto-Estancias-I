#include <Wire.h>
#include <LIDARLite.h>

#define LIDAR_LITE_ADDRESS 0x62 // Dirección predeterminada del Lidar Lite
int previousDistance = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(); // Inicializamos el protocolo I2C
}

void loop() {
  int distance = getDistance(); // Obtenemos la distancia medida
  if(distance != previousDistance);{ // Si la distancia ha cambiado
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      previousDistance = distance; //Actualizamos la distancia previa
  }
}

int getDistance() {
  int val;
  Wire.beginTransmission((int)LIDAR_LITE_ADDRESS); // Iniciamos la transmisión a la dirección del Lidar Lite
  Wire.write((int)0x00); // Escribimos el registro de lectura
  Wire.endTransmission(); // Finalizamos la transmisión
 
  Wire.requestFrom((int)LIDAR_LITE_ADDRESS, 2); // Solicitamos dos bytes de la dirección del Lidar Lite
  while(Wire.available() < 2); // Esperamos a que los datos estén disponibles
  val = Wire.read(); // Leemos el primer byte
  val = val << 8; // Desplazamos el primer byte para que quede en la posición más significativa
  val |= Wire.read(); // Leemos el segundo byte y lo añadimos a la posición menos significativa
  return val;
}

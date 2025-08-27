#include <Wire.h>
#include "MAX30105.h"   // Librería oficial SparkFun MAX3010x
#include "heartRate.h"  // Opcional (para HR/SpO2), no la usamos aquí

MAX30105 sensor;

const byte ledBrightness = 50;   // mA (0 - 50 mA, ajusta según necesidad)
const byte sampleAverage = 4;    // 1, 2, 4, 8, 16, 32
const byte ledMode       = 3;    // 1 = Red, 2 = Red+IR, 3 = Red+IR+Green
const int  sampleRate    = 100;  // Hz
const int  pulseWidth    = 411;  // 69, 118, 215, 411 (us)
const int  adcRange      = 16384; // nA (2048, 4096, 8192, 16384)

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!sensor.begin(Wire, I2C_SPEED_STANDARD)) {  // usar I2C estándar
    Serial.println("Error: MAX30101 no detectado. Revisa conexiones.");
    while (1);
  }

  // Configuración del sensor
  sensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

  // Encabezado CSV
  Serial.println("Tiempo[ms],RED (u.a.),IR (u.a.),GREEN (u.a.)");
}

void loop() {
  long red   = sensor.getRed();    // Valor ADC del LED rojo
  long ir    = sensor.getIR();     // Valor ADC del LED IR
  long green = (ledMode == 3) ? sensor.getGreen() : 0;  // Valor ADC del LED verde

  // Imprimir en formato CSV
  Serial.print(millis()); Serial.print(",");
  Serial.print(red);      Serial.print(",");
  Serial.print(ir);       Serial.print(",");
  Serial.println(green);

  delay(10);  // Ajusta según sampleRate (100 Hz → ~10 ms entre muestras)
}

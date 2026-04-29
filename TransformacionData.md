# Transformación y Procesamiento de la Data Cruda del MAX30101/MAX30102

## ¿Qué es la data cruda del MAX30101?

El sensor MAX30101/MAX30102 NO entrega directamente:

* frecuencia cardíaca
* SpO2
* respiración
* presión arterial

El sensor entrega señales ópticas crudas llamadas:

* RED
* IR (infrarrojo)
* GREEN

Estas señales son mediciones del ADC interno del sensor.

---

# ¿Qué significa “data cruda”?

La data cruda son valores digitales obtenidos directamente del fotodiodo y convertidor ADC interno del sensor.

Ejemplo:

```csv id="9w6m20"
Tiempo[ms],RED,IR,GREEN
0,52311,61200,1400
10,52400,61180,1410
20,52550,61210,1425
```

Estos números:

* NO son voltios
* NO son milivoltios
* NO son BPM
* NO son porcentaje de oxígeno

Son simplemente:

```text id="pfk1zl"
intensidades ópticas digitalizadas
```

---

# ¿Qué representa cada canal?

## RED

LED rojo.

Longitud de onda aproximada:

```text id="yzk7mu"
660 nm
```

Usado principalmente para:

* SpO2
* absorción sanguínea

---

## IR

LED infrarrojo.

Longitud de onda aproximada:

```text id="94y52g"
880 nm
```

Usado para:

* frecuencia cardíaca
* PPG
* perfusión sanguínea

El canal IR suele ser el más utilizado para análisis PPG.

---

## GREEN

LED verde.

Usado en:

* movimiento
* señales superficiales
* wearables

En muchos casos puede tener más ruido.

---

# ¿Qué es PPG?

PPG significa:

```text id="r6kl6x"
Photoplethysmography
```

o:

```text id="wyjv6o"
Fotopletismografía
```

Es una técnica óptica para medir cambios de volumen sanguíneo.

---

# ¿Por qué la señal cambia?

La señal cambia porque:

* el corazón bombea sangre
* cambia la absorción de luz
* cambia la cantidad de luz reflejada

Por eso aparece una señal periódica.

---

# Componentes de la señal PPG

La señal tiene dos componentes principales:

## 1. Componente DC

Parte lenta o constante.

Representa:

* tejido
* hueso
* piel
* iluminación base

---

## 2. Componente AC

Parte pulsátil.

Representa:

* latidos cardíacos
* cambios sanguíneos

Esta es la parte más importante.

---

# Pipeline típico de procesamiento

La data cruda normalmente pasa por varias etapas.

---

# 1. Adquisición

Captura desde Arduino.

Ejemplo:

```python id="6sgz6r"
line = ser.readline()
```

---

# 2. Limpieza de señal

Eliminar:

* ruido
* spikes
* errores seriales

Ejemplos:

* moving average
* median filter
* Savitzky-Golay
* low-pass filter

---

# 3. Remover componente DC

Muchas veces se elimina la tendencia lenta:

```python id="c3pmgd"
signal = signal - np.mean(signal)
```

o usando filtros pasa-altos.

---

# 4. Filtrado

Para aislar frecuencia cardíaca.

Rango típico:

```text id="jl3tqv"
0.5 Hz – 5 Hz
```

equivalente aproximadamente a:

```text id="cnj4wu"
30 BPM – 300 BPM
```

---

# 5. Normalización

La señal puede normalizarse:

```python id="u0s6m0"
signal = (signal - mean) / std
```

Esto ayuda en:

* Machine Learning
* Deep Learning

---

# 6. Detección de picos

Buscar máximos locales.

Los picos representan latidos cardíacos.

---

# 7. Cálculo de BPM

Fórmula:

```text id="0qj7ng"
BPM = 60 / periodo
```

---

# 8. Extracción de características

Ejemplos:

* amplitud
* energía
* FFT
* HRV
* frecuencia dominante
* estadísticas

---

# 9. Machine Learning / IA

La señal procesada puede usarse en:

* clasificación
* detección de estrés
* detección de fatiga
* biometría
* monitoreo fisiológico

---

# Problemas comunes en la data cruda

## 1. Saturación

La señal queda “pegada”.

Causas:

* LED muy brillante
* dedo demasiado cerca
* exceso de reflexión

Solución:

```cpp id="0cq2vt"
ledBrightness
```

---

## 2. Mucho ruido

Causas:

* movimiento
* cable suelto
* mala alimentación
* mala conexión GND

---

## 3. Señal plana

Causas:

* dedo mal colocado
* sensor desconectado
* mala iluminación

---

## 4. Valores extremadamente altos

Puede deberse a:

* saturación ADC
* configuración incorrecta

Probar:

```cpp id="8g8n5l"
adcRange
```

---

# Importante sobre la frecuencia de muestreo

Si:

```cpp id="xyj0i6"
sampleRate = 100
```

Entonces:

```text id="l8xvpa"
100 muestras por segundo
```

Cada muestra ocurre aproximadamente cada:

```text id="sn0i7z"
10 ms
```

---

# ¿Por qué guardar data cruda?

Porque permite:

✅ reprocesar señales
✅ probar distintos filtros
✅ entrenar modelos IA
✅ comparar algoritmos
✅ evitar pérdida de información

---

# Recomendación importante

Siempre guardar:

* timestamp
* configuración del sensor
* sampleRate
* pulseWidth
* adcRange
* condiciones experimentales

---

# Ejemplo de procesamiento futuro

La data guardada puede analizarse luego con:

* Python
* MATLAB
* LabVIEW
* R
* TensorFlow
* PyTorch

---

# Librerías útiles en Python

## Procesamiento de señales

```bash id="81y6m4"
pip install scipy
```

---

## Machine Learning

```bash id="nt8p0m"
pip install scikit-learn
```

---

## Deep Learning

```bash id="0l5q2l"
pip install tensorflow
```

o:

```bash id="d3r0y2"
pip install torch
```

---

# Recomendación final

Guardar SIEMPRE la data cruda original.

Nunca sobrescribir el dataset original después de filtrar o transformar señales.

Mantener:

```text id="fjzv6s"
raw_data/
processed_data/
features/
models/
```

Esto ayuda enormemente en:

* investigación
* trazabilidad
* reproducibilidad
* debugging
* publicaciones científicas

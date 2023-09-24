// Ciclos de trabajo para Toggle
const unsigned long trabajo1 = 500/2;
const unsigned long trabajo2 = 323/2;

// Variables para llevar el seguimiento del tiempo
unsigned long TAnterior1 = 0;
unsigned long TAnterior2 = 0;

// Estado actual de los LEDs
int led1 = LOW;
int led2 = LOW;

void setup() {
  // Inicializa los pines de los LEDs como salidas
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // Obtiene el tiempo actual
  unsigned long TActual = millis();

  // Controla el primer LED (500 ms)
  if (TActual - TAnterior1 >= trabajo1) {
    TAnterior1 = TActual;
    // Cambia el estado del LED
    if (led1 == LOW) {
      led1 = HIGH;
    } else {
      led1 = LOW;
    }
    // Enciende o apaga el LED
    digitalWrite(12, led1);
  }

  // Controla el segundo LED (323 ms)
  if (TActual - TAnterior2 >= trabajo2) {
    TAnterior2 = TActual;
    // Cambia el estado del LED
    if (led2 == LOW) {
      led2 = HIGH;
    } else {
      led2 = LOW;
    }
    // Enciende o apaga el LED
    digitalWrite(13, led2);
  }
}

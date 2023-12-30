// Variable para almacenar el número del núcleo en el que se ejecutará la tarea
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;  // Si es uniprocesador, se ejecutará en el Core 0
#else
static const BaseType_t app_cpu = 1;  // Por defecto, se ejecutará en el Core 1
#endif

// Definición de pines para los LEDs
const int ledPinCore0 = 2; // Pines de led
const int ledPinCore1 = 4;

// Función que se ejecutará en el Core 0
void taskCore0(void *parameter) {
  for (;;) {
    digitalWrite(ledPinCore0, HIGH);
    delay(500);
    digitalWrite(ledPinCore0, LOW);
    delay(500);
  }
}

// Función que se ejecutará en el Core 1
void taskCore1(void *parameter) {
  for (;;) {
    digitalWrite(ledPinCore1, HIGH);
    delay(300);
    digitalWrite(ledPinCore1, LOW);
    delay(300);
  }
}

void setup() {
  // Inicializa los pines de los LEDs como salidas
  pinMode(ledPinCore0, OUTPUT);
  pinMode(ledPinCore1, OUTPUT);

  // Crea las tareas para cada núcleo
  xTaskCreatePinnedToCore(
    taskCore0,       // Función que se ejecutará en el Core 0
    "TaskCore0",     // Nombre de la tarea
    10000,           // Tamaño del stack de la tarea
    NULL,            // Parámetro de la tarea (en este caso, no se utiliza)
    1,               // Prioridad de la tarea
    NULL,            // Manejador de la tarea (en este caso, no se utiliza)
    0                // Núcleo en el que se ejecutará la tarea (Core 0)
  );

  xTaskCreatePinnedToCore(
    taskCore1,       // Función que se ejecutará en el Core 1
    "TaskCore1",     // Nombre de la tarea
    10000,           // Tamaño del stack de la tarea
    NULL,            // Parámetro de la tarea (en este caso, no se utiliza)
    1,               // Prioridad de la tarea
    NULL,            // Manejador de la tarea (en este caso, no se utiliza)
    app_cpu          // Núcleo en el que se ejecutará la tarea (Core 1 o Core 0 según la configuración)
  );
}

void loop() {
  // El loop principal no hace nada 
}

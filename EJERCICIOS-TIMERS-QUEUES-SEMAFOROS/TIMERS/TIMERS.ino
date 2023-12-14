// Código de seis timer
// Selección de la CPU en caso de que el ESP32 tenga múltiples núcleos
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Definición de seis temporizadores
static TimerHandle_t auto_reload_timer = NULL;
static TimerHandle_t auto_reload_timer2 = NULL;
static TimerHandle_t auto_reload_timer3 = NULL;
static TimerHandle_t auto_reload_timer4 = NULL;
static TimerHandle_t auto_reload_timer5 = NULL;
static TimerHandle_t auto_reload_timer6 = NULL;

// Función de devolución de llamada para el temporizador 1
void myTimerCallback(TimerHandle_t xTimer) {
  if ((uint32_t)pvTimerGetTimerID(xTimer) == 1) {
    Serial.println("Timer 1");
  }
}

// Función de devolución de llamada para el temporizador 2
void myTimerCallback2(TimerHandle_t xTimer) {
  if ((uint32_t)pvTimerGetTimerID(xTimer) == 1) {
    Serial.println("Timer 2");
  }
}

// Función de devolución de llamada para el temporizador 3
void myTimerCallback3(TimerHandle_t xTimer) {
  if ((uint32_t)pvTimerGetTimerID(xTimer) == 1) {
    Serial.println("Timer 3");
  }
}

// Función de devolución de llamada para el temporizador 4
void myTimerCallback4(TimerHandle_t xTimer) {
  if ((uint32_t)pvTimerGetTimerID(xTimer) == 1) {
    Serial.println("Timer 4");
  }
}

// Función de devolución de llamada para el temporizador 5
void myTimerCallback5(TimerHandle_t xTimer) {
  if ((uint32_t)pvTimerGetTimerID(xTimer) == 1) {
    Serial.println("Timer 5");
  }
}

// Función de devolución de llamada para el temporizador 6
void myTimerCallback6(TimerHandle_t xTimer) {
  if ((uint32_t)pvTimerGetTimerID(xTimer) == 1) {
    Serial.println("Timer 6");
  }
}

void setup() {
  // Configuración del puerto serie (Serial)
  Serial.begin(115200);

  // Creación de seis temporizadores con diferentes períodos
  auto_reload_timer = xTimerCreate(
                      "Auto-reload timer",        // Nombre del temporizador
                      110 / portTICK_PERIOD_MS,  // Periodo del temporizador (en ticks)
                      pdTRUE,                     // Auto-recarga
                      (void *)1,                  // ID del temporizador
                      myTimerCallback);           // Función de devolución de llamada

  auto_reload_timer2 = xTimerCreate(
                      "Auto-reload timer",        // Nombre del temporizador
                      120 / portTICK_PERIOD_MS,  // Periodo del temporizador (en ticks)
                      pdTRUE,                     // Auto-recarga
                      (void *)1,                  // ID del temporizador
                      myTimerCallback2);          // Función de devolución de llamada

  auto_reload_timer3 = xTimerCreate(
                      "Auto-reload timer",        // Nombre del temporizador
                      130 / portTICK_PERIOD_MS,  // Periodo del temporizador (en ticks)
                      pdTRUE,                     // Auto-recarga
                      (void *)1,                  // ID del temporizador
                      myTimerCallback3);          // Función de devolución de llamada

  auto_reload_timer4 = xTimerCreate(
                      "Auto-reload timer",        // Nombre del temporizador
                      140 / portTICK_PERIOD_MS,  // Periodo del temporizador (en ticks)
                      pdTRUE,                     // Auto-recarga
                      (void *)1,                  // ID del temporizador
                      myTimerCallback4);          // Función de devolución de llamada

  auto_reload_timer5 = xTimerCreate(
                      "Auto-reload timer",        // Nombre del temporizador
                      150 / portTICK_PERIOD_MS,  // Periodo del temporizador (en ticks)
                      pdTRUE,                     // Auto-recarga
                      (void *)1,                  // ID del temporizador
                      myTimerCallback5);          // Función de devolución de llamada

  auto_reload_timer6 = xTimerCreate(
                      "Auto-reload timer",        // Nombre del temporizador
                      160 / portTICK_PERIOD_MS,  // Periodo del temporizador (en ticks)
                      pdTRUE,                     // Auto-recarga
                      (void *)1,                  // ID del temporizador
                      myTimerCallback6);          // Función de devolución de llamada


  // Inicio de los temporizadores
  xTimerStart(auto_reload_timer, portMAX_DELAY);
  xTimerStart(auto_reload_timer2, portMAX_DELAY);
  xTimerStart(auto_reload_timer3, portMAX_DELAY);
  xTimerStart(auto_reload_timer4, portMAX_DELAY);
  xTimerStart(auto_reload_timer5, portMAX_DELAY);
  xTimerStart(auto_reload_timer6, portMAX_DELAY);

}

void loop() {
}

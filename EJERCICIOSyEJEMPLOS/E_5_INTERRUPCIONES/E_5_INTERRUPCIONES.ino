//Este codigo genera una interrupcion cada que se presiona el boton del pin 2 en la que se aumenta en uno un contador y se imprime su valor
int contador = 0;
// Definir el semáforo
SemaphoreHandle_t semaforo;

// Manejador de la interrupción de temporizador
void manejarInterrupcion() {
  
    // Notificar a la tarea principal que puede ejecutarse
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(semaforo, &xHigherPriorityTaskWoken);
    
    // Si una tarea de mayor prioridad se desbloqueó, solicitar cambio de contexto
    if (xHigherPriorityTaskWoken == pdTRUE) {
      portYIELD_FROM_ISR();
    }

}

// Función de la tarea principal
void tareaPrincipal(void *parametro) {
  while (1) {
    // Esperar a que se libere el semáforo
    
    if (xSemaphoreTake(semaforo, portMAX_DELAY)) {
      // Realizar tarea cuando se notifica desde la interrupción
      Serial.println(contador);
      contador++;
      // Puedes hacer más operaciones aquí

      // Esperar un tiempo antes de la próxima ejecución
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Crear semáforo
  semaforo = xSemaphoreCreateBinary();
  pinMode(2, INPUT);
  // Inicializar el semáforo
  xSemaphoreGive(semaforo);

  // Configurar interrupción de temporizador en el pin 2
  attachInterrupt(digitalPinToInterrupt(2), manejarInterrupcion, RISING);

  // Crear tarea principal
  xTaskCreate(tareaPrincipal, "TareaPrincipal", 4096, NULL, 1, NULL);
}

void loop() {
  // No es necesario implementar el loop en FreeRTOS
}

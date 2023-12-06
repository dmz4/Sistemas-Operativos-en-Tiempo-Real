//Este codigo crea tareas y la elimina, cada que crea una tarea imprime el numero detarea con el indice que se usa para wl ciclo en el que se crean las tareas
static int no_tarea = 400;

SemaphoreHandle_t barridoSemaforo = xSemaphoreCreateCounting(no_tarea, 0);

void tareaGenerica (void * parameter)
{
  String mns_generico = "Tarea #: ";
  Serial.println(mns_generico);
  Serial.println((int)parameter);
  xSemaphoreGive(barridoSemaforo);
  vTaskDelete(NULL);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Inicio del programa");
  for(int i = 0; i<no_tarea; i++)
  {
    xTaskCreatePinnedToCore(tareaGenerica,
                          "Tarea Generica",
                          1024,
                          (void *)i,
                          0,
                          NULL,
                          1);

    vTaskDelay(2 / portTICK_PERIOD_MS);
  }

  for(int i = 0; i<no_tarea; i++)
  {
    xSemaphoreTake(barridoSemaforo, portMAX_DELAY);
  }
  Serial.println("Tareas cargadas en semaforos");

}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskSuspend(NULL);
  //vTaskDelay(1000 / portTICK_PERIOD_MS);

}

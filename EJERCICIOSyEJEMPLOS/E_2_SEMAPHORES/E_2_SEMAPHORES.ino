//este codigo hace que el productor ponga datos en todos los registros de un buffer y despues un consumidor los recoge, los lee y los pone a 0 para que el productor siga escribiendo en ellos
static int no_tarea = 10;
static int buff[10];
int dato = 0;
int i = 0;
SemaphoreHandle_t barridoSemaforo = xSemaphoreCreateCounting(no_tarea, 0);

void tareaGenerica (void * parameter)
{
  dato = dato + 1;
  buff[i] = dato;
  Serial.println("El productor ya cargo el dato");
  xSemaphoreGive(barridoSemaforo);
  vTaskDelete(NULL);
}

void leerGenerica (void * parameter)
{
  if(xSemaphoreTake(barridoSemaforo, portMAX_DELAY) == true)
  {
    Serial.print("El consumidor consumio: ");
    Serial.println(buff[i]);
    buff[i] = 0;
    vTaskDelete(NULL);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Inicio del programa");
  for(i = 0; i<no_tarea; i++)
  {
    xTaskCreatePinnedToCore(tareaGenerica,
                          "Tarea Generica",
                          1024,
                          (void *)i,
                          0,
                          NULL,
                          1);

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
  for(i = 0; i<no_tarea; i++)
  {
    xTaskCreatePinnedToCore(leerGenerica,
                          "Leer Generica",
                          1024,
                          (void *)i,
                          0,
                          NULL,
                          1);

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  
  Serial.println("Tareas cargadas en semaforos");

}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskSuspend(NULL);
  //vTaskDelay(1000 / portTICK_PERIOD_MS);

}

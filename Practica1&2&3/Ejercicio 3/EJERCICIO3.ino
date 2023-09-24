// Solo se utiliza el core 1
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif


static TaskHandle_t Tarea01 = NULL;
static TaskHandle_t Tarea02 = NULL;
static TaskHandle_t Tarea03 = NULL;

//Tarea UART 01
void TareaUART01(void*parameter){
  while(1){
    Serial.println();
    Serial.println("          Inicio del Programa Tarea 1");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 02
void TareaUART02(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Tarea 2");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 03
void TareaUART03(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Tarea 3");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(300);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreatePinnedToCore (
              TareaUART01,    // Funcion que se manda a llamar
              "Tarea01",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              3,              // Prioridades
              &Tarea01,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              TareaUART02,    // Funcion que se manda a llamar
              "Tarea02",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              2,              // Prioridades
              &Tarea02,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              TareaUART03,    // Funcion que se manda a llamar
              "Tarea03",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea03,           //
              app_cpu);       //Core
  // put your setup code here, to run once:
}

void loop() {

  vTaskDelay (500/ portTICK_PERIOD_MS);  
  if (Tarea01 != NULL) {

    vTaskDelete(Tarea01);

    Tarea01 = NULL;

  }
  vTaskDelay (1000/ portTICK_PERIOD_MS);
  vTaskSuspend(Tarea02);
  vTaskDelay (2000/ portTICK_PERIOD_MS);
  vTaskResume(Tarea02);
  vTaskDelay (1000/ portTICK_PERIOD_MS);
}
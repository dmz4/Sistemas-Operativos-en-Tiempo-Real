//Tablero de automovil con FREERTOS
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif


static TaskHandle_t Tarea01 = NULL;
static TaskHandle_t Tarea02 = NULL;
static TaskHandle_t Tarea03 = NULL;
static TaskHandle_t Tarea04 = NULL;
static TaskHandle_t Tarea05 = NULL;
static TaskHandle_t Tarea06 = NULL;
static TaskHandle_t Tarea07 = NULL;
static TaskHandle_t Tarea08 = NULL;
static TaskHandle_t Tarea09 = NULL;


//Tarea UART 01
void Aceite(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Aceite");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 02
void Airbag(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Airbag");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 03
void Temperatura(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Temperatura");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 04
void Cinturon(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Cinturon");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 05
void Puertas(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Puertas");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 06
void Cofre(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Cofre");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 07
void Cajuela(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Cajuela");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 08
void Intermitentes(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Intermitentes");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//Tarea UART 09
void Dirreccionales(void*parameter){
  while(1){
    Serial.println();
    Serial.println("Dirreccionales");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(300);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
    xTaskCreatePinnedToCore (
              Aceite,    // Funcion que se manda a llamar
              "Tarea01",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea01,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Airbag,    // Funcion que se manda a llamar
              "Tarea02",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea02,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Temperatura,    // Funcion que se manda a llamar
              "Tarea03",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea03,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Cinturon,    // Funcion que se manda a llamar
              "Tarea04",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea04,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Puertas,    // Funcion que se manda a llamar
              "Tarea05",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea05,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Cofre,    // Funcion que se manda a llamar
              "Tarea06",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea06,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Cajuela,    // Funcion que se manda a llamar
              "Tarea07",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea07,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Intermitentes,    // Funcion que se manda a llamar
              "Tarea08",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea08,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Dirreccionales,    // Funcion que se manda a llamar
              "Tarea09",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea09,           //
              app_cpu);       //Core
  // put your setup code here, to run once:  

}

void loop() {

  vTaskDelay (500/ portTICK_PERIOD_MS);  
  
  */
}

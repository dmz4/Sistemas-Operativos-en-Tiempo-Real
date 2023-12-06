//Este codigo hace que el productor deposite datos en registros pares para que despues consumer los lea y muestre
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static int buf[10];
static int apuntador = 0;
static SemaphoreHandle_t bin_sem;

void producer(void *parameters){
  int num = 0;
  Serial.println("Tarea productor");
  while(1){
    xSemaphoreGive(bin_sem);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    while(apuntador < 10){
      buf[apuntador] = num;
      apuntador = apuntador + 2;
      num = num + 2;
    }
    Serial.println("Registro listo");
    apuntador = 0;
    num = 0;
  }
}

void consumer(void *parameters){
  int val;
  while(1){
    if(xSemaphoreTake(bin_sem, portMAX_DELAY) == true){
      if(buf[0] != 0 || buf[2] != 0 || buf[4] != 0 || buf[6] != 0 || buf[8] != 0){
        Serial.println("Consumidor");
        while(apuntador <10){
          val = buf[apuntador];
          Serial.println(val);
          buf[apuntador] = 0;
          apuntador = apuntador + 2;
        }
    
        apuntador = 0;
      }
    }
  }

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("---Mensaje de inicio---");
  bin_sem = xSemaphoreCreateBinary();
      xTaskCreatePinnedToCore (
              producer,    // Funcion que se manda a llamar
              "Productor",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              consumer,    // Funcion que se manda a llamar
              "Consumidor",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core

}

void loop() {
  // put your main code here, to run repeatedly:
  vTaskDelay(1000 / portTICK_PERIOD_MS);

}
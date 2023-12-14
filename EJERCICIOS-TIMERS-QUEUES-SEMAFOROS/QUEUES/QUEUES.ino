// Este codigó hace dos productores llenen un buffer en las posiciones pares e impares y despue sdos consumidores toman los datos los leen y dejan en cero los espacios para denotar que los han vaciado
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Definición del búfer y punteros para registros pares e impares
static int buf[10];
static int apuntadorpar = 0;
static int apuntadorimpar = 1;

// Definición de semáforos para la sincronización
static SemaphoreHandle_t semaforo1;
static SemaphoreHandle_t semaforo2;
static SemaphoreHandle_t semaforo3;
static SemaphoreHandle_t semaforo4;


// Función de la tarea del productor para registros pares
void ProducerPar(void *parameters){
  int numpar = 0;
 
  while(1){
    if(xSemaphoreTake(semaforo4, portMAX_DELAY) == true) 
    {
      Serial.println("Tarea de productor par");
      vTaskDelay(200 / portTICK_PERIOD_MS);
      while(apuntadorpar < 10){
        buf[apuntadorpar] = numpar;       //Escritura en el registro posiciones pares
        apuntadorpar = apuntadorpar + 2;
        numpar = numpar + 2;
      }
      Serial.println("Registro par listo");
      apuntadorpar = 0;
      numpar = 0;
      xSemaphoreGive(semaforo1);
    }
  }
}

// Función de la tarea del productor para registros impares
void ProducerImpar(void *parameters){
  int numimpar = 1;
 
  while(1){
    if(xSemaphoreTake(semaforo1, portMAX_DELAY) == true)
    {
       Serial.println("Tarea de productor impar");
      vTaskDelay(200 / portTICK_PERIOD_MS);
      while(apuntadorimpar < 10){
        buf[apuntadorimpar] = numimpar; //Escritura en el registro posiciones impares
        apuntadorimpar = apuntadorimpar + 2;
        numimpar = numimpar + 2;
      }
      Serial.println("Registro impar listo");
      apuntadorimpar = 1;
      numimpar = 1;
      xSemaphoreGive(semaforo2);
    }
  }
}

// Función de la tarea del consumidor para registros pares
void ConsumerPar(void *parameters){
  int valpar;
  while(1){
    if(xSemaphoreTake(semaforo2, portMAX_DELAY) == true){
      if(buf[0] != 0 || buf[2] != 0 || buf[4] != 0 || buf[6] != 0 || buf[8] != 0){  // Si alguna de estas posiciones es diferente a cero signfica que no estan vacias
        Serial.println("Consumidor par");
        while(apuntadorpar <10){
          valpar = buf[apuntadorpar]; //Lectura del registro en posiciones pares
          Serial.println(valpar);
          buf[apuntadorpar] = 0; //Borramos el registro
          apuntadorpar = apuntadorpar + 2;
        }
    
        apuntadorpar = 0; 
        xSemaphoreGive(semaforo3);
      }
    }
  }

}

// Función de la tarea del consumidor para registros impares
void ConsumerImpar(void *parameters){
  int valimpar;
  while(1){
    if(xSemaphoreTake(semaforo3, portMAX_DELAY) == true){
      if(buf[1] != 0 || buf[3] != 0 || buf[5] != 0 || buf[7] != 0 || buf[9] != 0){ // Si alguna de estas posiciones es diferente a cero signfica que no estan vacias
        Serial.println("Consumidor impar");
        while(apuntadorimpar <10){
          valimpar = buf[apuntadorimpar]; //Lectura del registro en posiciones pares
          Serial.println(valimpar);
          buf[apuntadorimpar] = 0; //Borramos el registro
          apuntadorimpar = apuntadorimpar + 2;
        }
    
        apuntadorimpar = 1; 
        xSemaphoreGive(semaforo4);
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

  // Creación de semáforos
  semaforo1 = xSemaphoreCreateBinary();
  semaforo2 = xSemaphoreCreateBinary();
  semaforo3 = xSemaphoreCreateBinary();
  semaforo4 = xSemaphoreCreateBinary();

    // Creación de tareas
    xTaskCreatePinnedToCore (
              ProducerPar,    // Funcion que se manda a llamar
              "ProductorPar",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core

    xTaskCreatePinnedToCore (
              ProducerImpar,    // Funcion que se manda a llamar
              "ProductorImpar",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core


    xTaskCreatePinnedToCore (
              ConsumerPar,    // Funcion que se manda a llamar
              "ConsumidorPar",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core

    xTaskCreatePinnedToCore (
              ConsumerImpar,    // Funcion que se manda a llamar
              "ConsumidorImpar",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core

// Inicialización del semáforo para el productor par
xSemaphoreGive(semaforo4);

}

void loop() {

  vTaskDelay(1000 / portTICK_PERIOD_MS);

}

// Solo se utiliza el core 1
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif


static TaskHandle_t Tarea01 = NULL;
static TaskHandle_t Tarea02 = NULL;

bool global = false;


void escribir(bool estado)
{
  global = estado;
}

bool leer()
{
  if(global == false)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void critica(int tarea)
{ 
  if(tarea == 1)
  {
    Serial.println("Tarea 1 en Seccion critica");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  if(tarea == 2)
  {
    Serial.println("Tarea 2 en Seccion critica");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
  
}

//Tarea UART 01
void TareaUART01(void*parameter){
  while(1){
    if(leer() == false)
    {
      escribir(true);
      critica(1);
      escribir(false);;
    }
    Serial.println("Tarea 1");
    vTaskDelay(100 / portTICK_PERIOD_MS);

  }
}

//Tarea UART 02
void TareaUART02(void*parameter){
  while(1){
    if(leer() == false)
    {
      escribir(true);
      critica(2);
      escribir(false);
    }
    Serial.println("Tarea 2");
    vTaskDelay(100 / portTICK_PERIOD_MS);

  }
}



void setup() {
  Serial.begin(300);
    xTaskCreatePinnedToCore (
              TareaUART01,    // Funcion que se manda a llamar
              "Tarea01",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea01,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              TareaUART02,    // Funcion que se manda a llamar
              "Tarea02",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea02,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

}

void loop() {
}
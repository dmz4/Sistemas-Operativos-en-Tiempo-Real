// Solo se utiliza el core 1
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
//Peterson
//senal1 = true que el proceso 1 quiere entrar y false cuando no quiera entrar
//senal2 = true que el proceso 2 quiere entrar y false cuando no quiera entrar
//turno = 1 le toca al proceso 1
//turno = 2 le toca al proceso 2

int turno = 1;

bool senal1 = false;
bool senal2 = false;


static TaskHandle_t Tarea01 = NULL;
static TaskHandle_t Tarea02 = NULL;


void critica(int tarea)
{
  if(tarea == 1)
  {
    Serial.println("Seccion critica ocupada por Tarea 1");
  }
  
  if(tarea == 2)
  {
    Serial.println("Seccion critica ocupada por Tarea 2");
  }
}

//Tarea UART 01
void TareaUART01(void*parameter){
  while(1){
    
    senal1 = true;
    turno = 2;
    if((senal2 == true) && (turno == 2))
    {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
   
    critica(1);
    senal1 = false;
    
    Serial.println("Tarea 1");    
    
  }
}

//Tarea UART 02
void TareaUART02(void*parameter){
  while(1){
    
    senal2 = true;
    turno = 1;
    if((senal1 == true) && (turno == 1))
    {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    critica(2);
    senal2 = false;
    
    Serial.println("Tarea 2");
    
  }
}



void setup() {
  Serial.begin(750);
 
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

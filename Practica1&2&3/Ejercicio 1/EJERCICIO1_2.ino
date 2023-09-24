// Solo se utiliza el core 1
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

//Pins
static const int LED01 = 12;
static const int LED02 = 13;

//Tarea 01 
void toggleLED_1(void *parameter) {
  while(1) {
   
      digitalWrite(LED01, HIGH);
      vTaskDelay(250 / portTICK_PERIOD_MS);
      digitalWrite(LED01, LOW);
      vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}
void toggleLED_2(void *parameter) {
  while(1) {
      digitalWrite(LED02, HIGH);
      vTaskDelay(161.5 / portTICK_PERIOD_MS);
      digitalWrite(LED02, LOW);
      vTaskDelay(161.5 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(LED01, OUTPUT);
  pinMode(LED02, OUTPUT);
    xTaskCreatePinnedToCore (
            toggleLED_1,    // Funcion que se manda a llamar
            "Toggle 01",    // El nombre de la tarea
            1024,           // Stack size
            NULL,           //
            1,              // Prioridades
            NULL,           //
            app_cpu);       //Core
  // put your setup code here, to run once:
    xTaskCreatePinnedToCore (
            toggleLED_2,    // Funcion que se manda a llamar
            "Toggle 02",    // El nombre de la tarea
            1024,           // Stack size
            NULL,           //
            1,              // Prioridades
            NULL,           //
            app_cpu);       //Core

}

void loop() {
  // put your main code here, to run repeatedly:

}

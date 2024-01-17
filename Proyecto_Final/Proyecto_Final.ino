#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Librerias
#include "Adafruit_VL53L0X.h"
#include "BluetoothSerial.h"

// Pines para motores
int Rmotor = 25;
int Lmotor = 18;

// Pin de Led para indicar que no se encontro salida
int LED_WARNING = 23;
int LED_TIEMPO=17;
// Pin de led con PWM proporcional al nivel de bateria del potenciometro
int LED_POTE = 15;        //Led de PWM de bateria

// Pin para potenciometro que establece el tiempo
int Pote_Tiempo = 2;
int Pote_Bateria = 4;

// Pines para ultrasonicos
int triggerD=27;
int echoD=26;
int triggerI=14;
int echoI=12;

// Limite frontal y lateral
int lim_frontal = 50;
int lim_lateral = 300;

// Limite de giro en delays
int del_lim_max = 80; // delay maximo
int del_lim_min = 1; // delay minimo

// Contador de giro
int contador_giro = 0;


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int valorPote;
int valorPWM;

//Variable de Tiempo de funcionamiento
static int Tiempo;
static int extra;

//Variable para Paro del Sistema
int Paro=0;
int Estado=0;
//Variable de Sensores
// El indice 0 es para el sensor Vl053x
// El indice 1 para el ultrasonico derecho
// El indice 2 para el izuqierdo
// El indice 3 para el potenciometro
static float Sensores[]={0,0,0};
int D=10;
// Tiempos para adquirir datos de sensores ultrasonicos
int tiempoD;
int tiempoI;

// Semaforos par avanzar y girar
static SemaphoreHandle_t xSemaphore1,xSemaphore2, xSemaphore3;
//Timer Interrupcion
static TimerHandle_t one_shot_timer = NULL;
// Sensor VL053XL
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Bluetooth
String device_name = "ESP32-RTOS";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;


//Funciones de recepcion de señales de ultrasonicos
float* Distancias(){
  // Ultrasonico derecho
  digitalWrite(triggerD,HIGH);
  delay(1);
  digitalWrite(triggerD,LOW);
  tiempoD= pulseIn(echoD,HIGH);
  tiempoD=map(tiempoD, 0, 3047, 0, 80);
  Sensores[1]=tiempoD/58.2;

  // Ultrasonico izquierdo
  digitalWrite(triggerI,HIGH);
  delay(1);
  digitalWrite(triggerI,LOW);
  tiempoI= pulseIn(echoI,HIGH);
  tiempoI=map(tiempoI, 0, 3047, 0, 80);
  Sensores[2]=tiempoI/58.2;

  return Sensores;
}

//Funcion para interupcion del timer 
void myTimerCallback(TimerHandle_t xTimer) {

  // Timer one shot
  if ((uint32_t)pvTimerGetTimerID(xTimer) == 0) {
    //Serial.println("Timer One-shot desbordado");
    Paro=5;      
    SerialBT.println("----------");
    SerialBT.println("----------");
    SerialBT.print("Suspendido"); 
    SerialBT.println("----------");
    SerialBT.println("----------");
    digitalWrite(Rmotor, LOW);
    digitalWrite(Lmotor, LOW);
    digitalWrite(LED_TIEMPO, HIGH); 
  }
}

void AVANZAR(void*parameter){
  while(1){
    // Hacer take de semaforo 1
    xSemaphoreTake(xSemaphore1, portMAX_DELAY);
    // Variable donde se almacenan las distancias
    float *distanceX = Distancias();
      D=(lox.readRange())/10;
    if(D > lim_frontal) // si la distancia es mayor al limite frontal
    {
      Estado=1;
      // Avanzar recto
      digitalWrite(Rmotor, HIGH);
      digitalWrite(Lmotor, HIGH);
      if (Paro>1){
        digitalWrite(Rmotor, LOW);
        digitalWrite(Lmotor, LOW);        
      }
      xSemaphoreGive(xSemaphore1);
    }
    else
    {
      // Sino hacer give del semaforo 2 para pasar a la funcion de GIRAR
      xSemaphoreGive(xSemaphore2);
    }

  }
}

void GIRAR(void*parameter){
  while(1){   
    // Hacer take de semaforo 2 procedente de AVANZAR
    xSemaphoreTake(xSemaphore2, portMAX_DELAY);
    // Variable donde se almacenan las distancias
    float *distanceX = Distancias();
    // Girar
    digitalWrite(Rmotor, HIGH);
    digitalWrite(Lmotor, LOW);
    if (Paro>1){
      digitalWrite(Rmotor, LOW);
      digitalWrite(Lmotor, LOW);        
    }
    // Definicion limites de delay para funcion random considerando las distancias de los ultrasonicos
    
    if(distanceX[1] < lim_lateral && distanceX[2] < lim_lateral)
    {
      del_lim_min = 20;
      del_lim_max = 60;
    }
    if(distanceX[1] < lim_lateral){ // Limites si hay algo a la derecha
      del_lim_min = 20;
      del_lim_max = 80;
    }

    if(distanceX[2] < lim_lateral){ // Limites si hay algo a la izquieda
      del_lim_min = 10;
      del_lim_max = 60;
    }

    // Aplicacion de delay basado en un numero aleatorio teniendo en cuenta los limites antes espceificados
    vTaskDelay((random(del_lim_min, del_lim_max)) / portTICK_PERIOD_MS);
    
    // Aumento en uno del contador de giros
    contador_giro = contador_giro + 1;
    
    // Si el contador de giros 
    if(contador_giro < 10){
      D=(lox.readRange())/10;
      // Si la distancia es mayor al limte frontal que regrese a la funcion AVANZAR
      if(D > lim_frontal)
      {
        contador_giro = 0;
        xSemaphoreGive(xSemaphore1);
      }
      else
      {
        xSemaphoreGive(xSemaphore2);
      }
    }
    else  // Si se supera el numero de giros se hace give del semaforo 3 que conduce a la funcion SLEEP
    { 
      contador_giro = 0;
      xSemaphoreGive(xSemaphore3);
    } 
  }
}

// Tarea que se ejecuta cuando no hay salida
void SLEEP(void*parameter){
  while(1){
    // Hacer take de semaforo 3 procedente de GIRAR
    xSemaphoreTake(xSemaphore3, portMAX_DELAY);

    digitalWrite(LED_WARNING, HIGH);
    vTaskDelay(50/ portTICK_PERIOD_MS);

    digitalWrite(Rmotor, LOW);
    digitalWrite(Lmotor, LOW);        //Apagamos los mototes

    D=(lox.readRange())/10;
    if(D > 20+lim_frontal) // Se hace give al semaforo 1 de la tarea AVANZAR
    {
      digitalWrite(LED_WARNING, LOW);
      vTaskDelay(50 / portTICK_PERIOD_MS);

      xSemaphoreGive(xSemaphore1); 
    }else{
      xSemaphoreGive(xSemaphore3);
    }
  }
}
void SEND(void*parameter){
  while(1){
    // Variable donde se almacenan las distancias
    float *distanceX = Distancias();

    // Envio de datos por Bluetooth
    SerialBT.print("Distancia frontal: ");
    SerialBT.println(D);
    SerialBT.print("Distancia lateral derecha: "); 
    SerialBT.println(distanceX[1]);
    SerialBT.print("Distancia lateral izquierda: "); 
    SerialBT.println(distanceX[2]);
    SerialBT.print("Nivel de bateria: "); 
    SerialBT.println(analogRead(Pote_Bateria));   
    SerialBT.print("Tiempo: "); 
    SerialBT.println(Tiempo/1000);     
    SerialBT.println("----------");
    SerialBT.println("----------");

    // Delay para que no se mande tan seguido
    vTaskDelay((50) / portTICK_PERIOD_MS);

    if(Paro>1){
      vTaskSuspend(NULL);
    }  
  }  
}

// Tarea para mandar PWM al LED proporcional al nivel de bateria del potenciometro
void LED_Bateria(void*parameter){
  while(1){
  valorPote=analogRead(Pote_Bateria);
  valorPWM = map(valorPote, 0, 4095, 0, 255);
  ledcWrite(ledChannel, valorPWM);
  vTaskDelay(50 / portTICK_PERIOD_MS);

    if(Paro>1){
      vTaskSuspend(NULL);
    }  
  }
}



void setup() {

  Serial.begin(115200);

  //Comunicacion Bluetooth
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

  
  // Para sensor VL053X
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
    // power
  //Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));
  
  lox.startRangeContinuous();

  //Configuracion del Pin de LED_PWM
  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED_POTE, ledChannel);
  extra=map(analogRead(Pote_Tiempo), 0, 4095, 0, 240000);
  Tiempo=60000+extra;


  // Ultrasonicos
  //Ultra derecho
  pinMode(triggerD,OUTPUT);
  pinMode(echoD,INPUT);
  ////Ultra izquierdo
  pinMode(triggerI,OUTPUT);
  pinMode(echoI,INPUT);

  pinMode(Rmotor, OUTPUT);
  pinMode(Lmotor, OUTPUT);

  SerialBT.println("----------");
  SerialBT.print("Tiempo: "); 
  SerialBT.println(Tiempo);    

  SerialBT.println("----------");

  // Led para indicar que no hay salida
  pinMode(LED_WARNING, OUTPUT);
  pinMode(LED_TIEMPO, OUTPUT);
  digitalWrite(LED_WARNING, LOW);
  digitalWrite(LED_TIEMPO, LOW);

  // Semaforos par avanzar y girar
  xSemaphore1 = xSemaphoreCreateBinary();
  xSemaphore2 = xSemaphoreCreateBinary();

  // Semaforo para ir a tarea SLEEP porque no encontro salida el carro
  xSemaphore3 = xSemaphoreCreateBinary();

  // Le damos el semaforo a AVANZAR inicialmente
  xSemaphoreGive(xSemaphore1);  

      xTaskCreatePinnedToCore (
              AVANZAR,    // Funcion que se manda a llamar
              "Avanzar",    // El nombre de la tarea
              4096,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

        xTaskCreatePinnedToCore (
              GIRAR,    // Funcion que se manda a llamar
              "Girar",    // El nombre de la tarea
              4096,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

          xTaskCreatePinnedToCore (
              SLEEP,    // Funcion que se manda a llamar
              "Sleep",    // El nombre de la tarea
              4096,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

        xTaskCreatePinnedToCore (
              SEND,    // Funcion que se manda a llamar
              "Send",    // El nombre de la tarea
              4096,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

            xTaskCreatePinnedToCore (
              LED_Bateria,    // Funcion que se manda a llamar
              "LED_Bateria",    // El nombre de la tarea
              4096,           // Stack size
              NULL,           //
              1,              // Prioridades
              NULL,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

  one_shot_timer = xTimerCreate(
                      "One-shot",           
                      Tiempo / portTICK_PERIOD_MS,  
                      pdFALSE,                    
                      (void *)0,                 
                      myTimerCallback);  
  
  xTimerStart(one_shot_timer, portMAX_DELAY);                      
}

void loop() {
}
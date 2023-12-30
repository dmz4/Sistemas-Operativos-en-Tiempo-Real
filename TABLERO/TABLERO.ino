//Tablero de automovil con FREERTOS
#include <ESP32Servo.h>
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Tareas
static TaskHandle_t Tarea01 = NULL;
static TaskHandle_t Tarea02 = NULL;
static TaskHandle_t Tarea03 = NULL;
static TaskHandle_t Tarea04 = NULL;
static TaskHandle_t Tarea05 = NULL;
static TaskHandle_t Tarea06 = NULL;
static TaskHandle_t Tarea07 = NULL;
static TaskHandle_t Tarea08 = NULL;
static TaskHandle_t Tarea09 = NULL;

// Velocidad
int velocidadKm = 0;
int RPM = 0;

Servo vKm;
Servo vRPM;

// LED PARA TESTIGO DE TEMPERATURA
#define TEMP_RED    23 
#define TEMP_GREEN  22 

float temperature = 0;


// LED PARA TESTIGO DE ACEITE
#define ACEITE_RED    19 
#define ACEITE_GREEN  18 

float aceite = 0;


// LED PARA TESTIGO DE AIRBAG
#define AIRBAG_LED 17

int sensor_airbag = 0; // Si es HIGH se activa el testigo


// LED PARA TESTIGO DE CINTURON
#define CINTO_LED 16

int sensor_cinturon = 0; // Si es HIGH se activa el testigo

// LED PARA TESTIGO DE PUERTAS
#define DOOR_LED 4

int sensor_puertas = 0; // Si es HIGH se enciende el testigo lo que indica que una puerta esta abierta


// LED PARA TESTIGO DE COFRE
#define COFRE_LED 0

int sensor_cofre = 0; // Si es HIGH se enciende el testigo lo que indica que el cofre esta abierto

// LED PARA TESTIGO DE CAJUELA
#define CAJUELA_LED 2

int sensor_cajuela = 0; // Si es HIGH se enciende el testigo

// LEDs PARA INTERMITENTES Y DIRECCIONALES
#define RIGHT 21
#define LEFT 5
int s_dir = 0; // Si es 0 estan apagadas, 1 si estan intermitentes, 2 direccionales derecha y 3 direccionales izquierda

//Tarea testigo de aceite
void Aceite(void*parameter){
  while(1){
    aceite = analogRead(39); // Nivel de aceite en porcentaje
    
    if(aceite > 10 && aceite <= 20) // Si el nivel de aceite esta ente 10% y 20& el testigo prende en amarillo
    {
      analogWrite(ACEITE_RED,   255);
      analogWrite(ACEITE_GREEN, 255);
    }
    if(aceite >= 0 && aceite <= 10) // Si el nivel de aceite es inferior a 10& el testigo prende en rojo
    {
      analogWrite(ACEITE_RED,   255);
      analogWrite(ACEITE_GREEN, 0);
    }
  }
}

//Tarea testigo airbag
void Airbag(void*parameter){
  while(1){
    sensor_airbag = digitalRead(34); // Lectura de sensor de airbag
    
    if(sensor_airbag == HIGH)
    {
      digitalWrite(AIRBAG_LED, HIGH);
    }
    else
    {
      digitalWrite(AIRBAG_LED, LOW);
    }
  }
}

//Tarea testigo de temperatura
void Temperatura(void*parameter){
  while(1){
    temperature = analogRead(36); // Lectura de sensor de temperatura
    
    if(temperature >= 80 && temperature < 90) // Si la temperatura es mayor a 80 y menor a 90 el testigo prende de color amarillo
    {
      analogWrite(TEMP_RED,   255);
      analogWrite(TEMP_GREEN, 255);
    }
    if(temperature >= 90 && temperature <= 100) // Si la temperatura es mayor a 90 y menor o igual a 100 el testigo prende de color rojo
    {
      analogWrite(TEMP_RED,   255);
      analogWrite(TEMP_GREEN, 0);
    }
    
  }
}

//Tarea testigo de cinturon
void Cinturon(void*parameter){
  while(1){
    velocidadKm = analogRead(13); // Lectura de velocidad en kilometros
    sensor_cinturon = digitalRead(35); // Lectura de sensor de cinturon
    
    if(sensor_cinturon == HIGH && velocidadKm >= 20) // Si el sensor manda alto y la velocidad es mayor a 20 km/h
    {
      digitalWrite(CINTO_LED, HIGH);
    }
    else
    {
      digitalWrite(CINTO_LED, LOW);
    }
  }
}

//Tarea testigo de puertas
void Puertas(void*parameter){
  while(1){
    sensor_puertas = digitalRead(32); // Lectura de sensor de puertas abiertas
   
    if(sensor_puertas == HIGH) // Si el sensor manda alto 
    {
      digitalWrite(DOOR_LED, HIGH);
    }
    else
    {
      digitalWrite(DOOR_LED, LOW);
    }
  }
}

//Tarea testigo de cofre
void Cofre(void*parameter){
  while(1){
    sensor_cofre = digitalRead(33); // Lectura de sensor de puertas abiertas
    
    if(sensor_cofre == HIGH) // Si el sensor manda alto 
    {
      digitalWrite(COFRE_LED, HIGH);
    }
    else
    {
      digitalWrite(COFRE_LED, LOW);
    }
  }
}

//Tarea testigo de cajuela
void Cajuela(void*parameter){
  while(1){
    sensor_cajuela = digitalRead(25); // Lectura de sensor de puertas abiertas
    
    if(sensor_cajuela == HIGH) // Si el sensor manda alto 
    {
      digitalWrite(CAJUELA_LED, HIGH);
    }
    else
    {
      digitalWrite(CAJUELA_LED, LOW);
    }
  }
}

//Tarea intermitentes y direccionales
void IntermitentesDIR(void*parameter){
  while(1){
   
    s_dir = analogRead(12); // Lectura de señal para intermitentes y direccionales
    
    if(s_dir == 0) // Si es 0 las luces se apagan
    {
      digitalWrite(RIGHT, LOW);
      digitalWrite(LEFT, LOW);
    }
    else
    {
      if(s_dir == 1) // Si es 1 todas encienden de manera intermitente
      {
        digitalWrite(RIGHT, HIGH);
        digitalWrite(LEFT, HIGH);
        delay(100);
        digitalWrite(RIGHT, LOW);
        digitalWrite(LEFT, LOW);
        delay(100);

      }
      else
      {
        if(s_dir == 2) // Si es 2 encienden las de la derecha
        {
          digitalWrite(RIGHT, HIGH);
          digitalWrite(LEFT, LOW);
          delay(100);
          digitalWrite(RIGHT, LOW);
          digitalWrite(LEFT, LOW);
          delay(100);

        }
        else
        {
          if(s_dir == 3) // Si es 3 encienden las direccionales de la izquierda
          {
            digitalWrite(RIGHT, LOW);
            digitalWrite(LEFT, HIGH);
            delay(100);
            digitalWrite(RIGHT, LOW);
            digitalWrite(LEFT, LOW);
            delay(100);
          }

        }
        

      }
      

    }
    
  }
}

//Tarea indicadores de velocidad
void Velocidad(void*parameter){
  while(1){
    velocidadKm = analogRead(13);
    RPM = analogRead(14); 
    //Hacemos regla de 3 para obtenr el angulo del servo respecto a la velocidad                                          
    float anguloKm = velocidadKm * 180 / 261; // Maxima 260 km/h
    float anguloRPM = RPM * 180 / 3001; // Maxima 3000 rpm
    vKm.write(anguloKm); // Movemos los servomotores al angulo correspondiente
    vRPM.write(anguloRPM);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(AIRBAG_LED, OUTPUT);
  pinMode(TEMP_RED, OUTPUT);
  pinMode(TEMP_GREEN, OUTPUT);
  pinMode(ACEITE_RED, OUTPUT);
  pinMode(ACEITE_GREEN, OUTPUT);
  pinMode(CINTO_LED, OUTPUT);
  pinMode(DOOR_LED, OUTPUT);
  pinMode(COFRE_LED, OUTPUT);
  pinMode(CAJUELA_LED, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  pinMode(LEFT, OUTPUT);
  vKm.attach(27, 500, 2500);
  vRPM.attach(26, 500, 2500);
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
              IntermitentesDIR,    // Funcion que se manda a llamar
              "Tarea08",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea08,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              Velocidad,    // Funcion que se manda a llamar
              "Tarea09",    // El nombre de la tarea
              1024,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea09,           //
              app_cpu);       //Core
  // put your setup code here, to run once:  

}

void loop() {

 
}


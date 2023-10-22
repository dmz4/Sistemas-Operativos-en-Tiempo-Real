#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>


const char* ssid = "Jamal";
const char* password = "HolaLangi";


#define BOTtoken "6514138245:AAHObPHJiYK72gIIP7QVvm8Ioa0g_JHh914"  


#define CHAT_ID "1035266335"

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


int botRequestDelay = 100;
unsigned long lastTimeBotRan;

int S1 = 0;
int S2 = 0;
String cadena;
String mensaje;

static TaskHandle_t Tarea01 = NULL;
static TaskHandle_t Tarea02 = NULL;
static TaskHandle_t Tarea03 = NULL;

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

void critica(int tarea, String texto)
{ 
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    if(tarea == 1)
    {
      Serial.println("Tarea 1 en Seccion critica");
      mensaje = "Tarea 1: ";
    }
    if(tarea == 2)
    {
      Serial.println("Tarea 2 en Seccion critica");
      mensaje = "Tarea 2: ";
    }
    if(tarea == 3)
    {
      Serial.println("Tarea 3 en Seccion critica");
      mensaje = "Tarea 3: ";
    }
    String chat_id = "1035266335";
    Serial.println(chat_id);
    mensaje.concat(texto);
    Serial.println(mensaje);

    if (tarea == 1){
      bot.sendMessage(chat_id, mensaje, "");
    }
    else{
      if (tarea == 2){
        bot.sendMessage(chat_id, mensaje, "");
      }
      else{
        if(tarea == 3)
        {
          bot.sendMessage(chat_id, mensaje, "");
        }
      }
    }
    lastTimeBotRan = millis();
  }  
  
}

void TareaT01(void*parameter){
  while(1){
    S1 = analogRead(34);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    if(leer() == false)
    {
      escribir(true);
      critica(1, String(S1));
      escribir(false);
      
    }
  }
}

void TareaT02(void*parameter){
  while(1){
    S2 = digitalRead(4);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    if(leer() == false)
    {
      escribir(true);
      critica(2, String(S2));
      escribir(false);
    }
  }
}

void TareaT03(void*parameter){
  while(1){
    if(Serial.available() > 0)
    {
      cadena = Serial.readStringUntil('\n');
      if(leer() == false)
      {
        escribir(true);
        critica(3, cadena);
        escribir(false);;
      }
    }
  }
}


void setup() {

  Serial.begin(115200);
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      
    client.setTrustAnchors(&cert); 
  #endif

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println(WiFi.localIP());
 
    xTaskCreatePinnedToCore (
              TareaT01,    // Funcion que se manda a llamar
              "Tarea01",    // El nombre de la tarea
              8192,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea01,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              TareaT02,    // Funcion que se manda a llamar
              "Tarea02",    // El nombre de la tarea
              8192,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea02,           //
              app_cpu);       //Core
  // put your setup code here, to run once:

    xTaskCreatePinnedToCore (
              TareaT03,    // Funcion que se manda a llamar
              "Tarea03",    // El nombre de la tarea
              8192,           // Stack size
              NULL,           //
              1,              // Prioridades
              &Tarea03,           //
              app_cpu);       //Core
  // put your setup code here, to run once:
}

void loop() {

}
// Codigo semaforos 
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

const int ROJO_01 = 19;
const int AMARILLO_01 = 18;
const int VERDE_01 = 5;
const int ROJO_02 = 17;
const int AMARILLO_02 = 16;
const int VERDE_02 = 4;

const int boton1 = 34;
const int boton2 = 25;

static bool marca01 = false;
static bool marca02 = false;
static bool marca03 = false;
static bool marca04 = false;

static bool marcaE = false;
static bool senal=false;


///tiempo de presion
unsigned long prev=millis();
// Prototipos de tareas
void estado01(void *parameters);
void estado02(void *parameters);
void estado03(void *parameters);
void estado04(void *parameters);

void estadoA(void*parameters);///activado emergencia
void estadoD(void*parameters);///desactivar emergencia
void estado00(void*parameters);//leer entradas


static SemaphoreHandle_t xSemaphore1,xSemaphore2,xSemaphore3,xSemaphore4,xSemaphoreA,xSemaphoreD,xSemaphoreAA;

int prendido=HIGH;
int presionado1,presionado2,presionado21,presionado22;
int estadoboton1, estadoboton2;
int tiempopresionado,tiempopresionado2;

void setup() {
  Serial.begin(115200);

  // Configurar pines de los LEDs como salidas
  pinMode(ROJO_01, OUTPUT);
  pinMode(AMARILLO_01, OUTPUT);
  pinMode(VERDE_01, OUTPUT);
  pinMode(ROJO_02, OUTPUT);
  pinMode(AMARILLO_02, OUTPUT);
  pinMode(VERDE_02, OUTPUT);

  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);


  xSemaphore1 = xSemaphoreCreateBinary();
  xSemaphore2 = xSemaphoreCreateBinary();
  xSemaphore3 = xSemaphoreCreateBinary();
  xSemaphore4 = xSemaphoreCreateBinary();

//Semaforos de activa y desactivar
  xSemaphoreA = xSemaphoreCreateBinary();
  xSemaphoreD = xSemaphoreCreateBinary();  
  xSemaphoreAA = xSemaphoreCreateBinary();


  xTaskCreatePinnedToCore(estado01,"estado01",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(estado02,"estado02",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(estado03,"estado03",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(estado04,"estado04",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(estadoA,"estadoA",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(estadoD,"estadoD",1024,NULL,1,NULL,app_cpu);
  //xTaskCreatePinnedToCore(estado00,"estado00",1024,NULL,1,NULL,app_cpu);


  xTaskCreatePinnedToCore(salida01,"salida01",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(salida02,"salida02",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(salida03,"salida03",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(salida04,"salida04",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(salida05,"salida05",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(salida06,"salida06",1024,NULL,1,NULL,app_cpu);
  xTaskCreatePinnedToCore(salida07,"salida07",1024,NULL,1,NULL,app_cpu);

    //xTaskCreatePinnedToCore(entrada01,"entrada01",1024,NULL,1,NULL,app_cpu);


  xSemaphoreGive(xSemaphore1);  
}

void loop() {

}

void estadoA(void *parameters){
xSemaphoreTake(xSemaphoreA, portMAX_DELAY);
  if(marcaE==false){
    marca01=false;
    marca02=false;
    marca03=false;
    marca04=false;
    marcaE=true;
vTaskDelay(1000/portTICK_PERIOD_MS);}else{
  xSemaphoreGive(xSemaphoreD);}
}

void estadoD(void *parameters){
xSemaphoreTake(xSemaphoreD, portMAX_DELAY);
marcaE=false;
   marca01=false;
    marca02=false;
    marca03=false;
    marca04=false;
vTaskDelay(1000/portTICK_PERIOD_MS);
xSemaphoreGive(xSemaphore1);
}

void estado01(void *parameters){
  while (1) {
    xSemaphoreTake(xSemaphore1, portMAX_DELAY);
    marca04=false;
    marca01=true;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xSemaphoreGive(xSemaphore2);
  }
}

void estado02(void *parameters){
  while (1) {
    xSemaphoreTake(xSemaphore2, portMAX_DELAY);
    marca01=false;
    marca02=true;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xSemaphoreGive(xSemaphore3);
  }
}

void estado03(void *parameters){
  while (1) {
    xSemaphoreTake(xSemaphore3, portMAX_DELAY);
    marca02=false;
    marca03=true;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xSemaphoreGive(xSemaphore4);
  }
}

void estado04(void *parameters){
  while (1) {
    xSemaphoreTake(xSemaphore4, portMAX_DELAY);
    marca03=false;
    marca04=true;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    xSemaphoreGive(xSemaphore1);
  }
}

void salida01(void *parameters){
  while(1){
    if(marca01 == true ){
      digitalWrite(ROJO_01, HIGH);
    }else{
      digitalWrite(ROJO_01, LOW);
    }
  }
}
void salida02(void *parameters){
  while(1){
    if(marca02 == true){
      digitalWrite(AMARILLO_01, HIGH);
    }else{
      digitalWrite(AMARILLO_01, LOW);
    }
  }
}
void salida03(void *parameters){
  while(1){
    if(marca03 == true || marca04 == true){
      digitalWrite(VERDE_01, HIGH);
    }else{
      digitalWrite(VERDE_01, LOW);
    }
  }
}
void salida04(void *parameters){
  while(1){
    if(marca03 == true){
      digitalWrite(ROJO_02, HIGH);
    }else{
      digitalWrite(ROJO_02, LOW);
    }
  }
}
void salida05(void *parameters){
  while(1){
    if(marca04 == true){
      digitalWrite(AMARILLO_02, HIGH);
    }else{
      digitalWrite(AMARILLO_02, LOW);
    }
  }
}
void salida06(void *parameters){
  while(1){
    if(marca01 == true || marca02 == true){
      digitalWrite(VERDE_02, HIGH);
    }else{
      digitalWrite(VERDE_02, LOW);
    }
  }
}

void salida07(void *parameters){
while(1){
unsigned long tiempo=millis();
  if(marcaE==true){
if(tiempo-prev>500){
  digitalWrite(VERDE_02, prendido);
  digitalWrite(VERDE_01, prendido);
  digitalWrite(ROJO_02, prendido);
  digitalWrite(ROJO_01, prendido);
  digitalWrite(AMARILLO_02, prendido);
  digitalWrite(AMARILLO_01, prendido);
  prendido=!prendido;
  prev=tiempo;
   }
 }
  }
}



void estado00(void *parameters){
  while(1){
  xSemaphoreTake(xSemaphore1,portMAX_DELAY);
  marca01=false;
    marca02=false;
    marca03=false;
    marca04=false;
    marcaE=false;
estadoboton1=digitalRead(boton1);
if(estadoboton1==HIGH){
   presionado1=millis();
    while(estadoboton1==HIGH){
      estadoboton1=digitalRead(boton1);
      estadoboton2=digitalRead(boton2);
       presionado2=millis();
       tiempopresionado=presionado1-presionado2;
          if(tiempopresionado > 2000 && estadoboton2==HIGH){
            presionado21=millis()+2000;
              while(estadoboton2==HIGH){
                presionado22=millis();
              estadoboton2=digitalRead(boton2);
                     tiempopresionado2=presionado21-presionado22;

              }
          }
    }
estadoboton1=digitalRead(boton1);
}

if(tiempopresionado > tiempopresionado2){
  xSemaphoreGive(xSemaphoreA);
}else{xSemaphoreGive(xSemaphore1);}
}//
}
///Prueba funcion de interrupcion 



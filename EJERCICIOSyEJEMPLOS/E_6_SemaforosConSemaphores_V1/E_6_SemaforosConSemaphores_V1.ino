#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

const int ROJO1 = 4;
const int VERDE1 = 17;
const int AMARILLO1 = 16;
const int ROJO2 = 26;
const int VERDE2 = 25;
const int AMARILLO2 = 27;
int flag = 0;
int estado = 0;
const unsigned long DEBOUNCE_DELAY = 50; // Tiempo de espera para el antirrebote en milisegundos

unsigned long tiempo1 = 0;

// Prototipos de tareas
void taskuno(void *parameters);
void taskdos(void *parameters);
void tasktres(void *parameters);
void taskcuatro(void *parameters);
void FSM(void *parameters);

static SemaphoreHandle_t xSemaphore1, xSemaphore2, xSemaphore3, xSemaphore4;

void setup() {
  Serial.begin(115200);

  // Configurar pines de los LEDs como salidas
  pinMode(ROJO1, OUTPUT);
  pinMode(VERDE1, OUTPUT);
  pinMode(AMARILLO1, OUTPUT);
  pinMode(ROJO2, OUTPUT);
  pinMode(VERDE2, OUTPUT);
  pinMode(AMARILLO2, OUTPUT);
  pinMode(2, INPUT);
  pinMode(5, INPUT);

  // Crear semáforos
  xSemaphore1 = xSemaphoreCreateBinary();
  xSemaphore2 = xSemaphoreCreateBinary();
  xSemaphore3 = xSemaphoreCreateBinary();
  xSemaphore4 = xSemaphoreCreateBinary();
  
  xTaskCreatePinnedToCore(taskuno,
                          "task1",
                          2048,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  xTaskCreatePinnedToCore(taskdos,
                          "task2",
                          2048,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  xTaskCreatePinnedToCore(tasktres,
                          "task3",
                          2048,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  xTaskCreatePinnedToCore(taskcuatro,
                          "task4",
                          2048,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  xSemaphoreGive(xSemaphore1);

  // Crear semáforo
  

  // Configurar interrupción de temporizador en el pin 2
  


  xTaskCreatePinnedToCore(FSM,
                          "FSM",
                          2048,
                          NULL,
                          1,
                          NULL,
                          app_cpu);
}

void loop() {
 
  
}

void taskuno(void *parameters) {
  while (1) {
    xSemaphoreTake(xSemaphore1, portMAX_DELAY);

    if(flag == 0)
    {
      digitalWrite(ROJO1, HIGH);
      digitalWrite(VERDE2, HIGH);
      delay(4000);
      digitalWrite(VERDE2, LOW);
    }
    if(flag == 1)
    {
      digitalWrite(ROJO1, HIGH);
      digitalWrite(ROJO2, HIGH);
      delay(100);
      digitalWrite(ROJO1, LOW);
      digitalWrite(ROJO2, LOW);
      delay(100);
    }

    xSemaphoreGive(xSemaphore2);
  }
}

void taskdos(void *parameters) {
  while (1) {
    xSemaphoreTake(xSemaphore2, portMAX_DELAY);
    if(flag == 0)
    {
      digitalWrite(AMARILLO2, HIGH);
      delay(1000);
      digitalWrite(AMARILLO2, LOW);
      digitalWrite(ROJO1, LOW);
    }
    if(flag == 1)
    {
      digitalWrite(ROJO1, HIGH);
      digitalWrite(ROJO2, HIGH);
      delay(100);
      digitalWrite(ROJO1, LOW);
      digitalWrite(ROJO2, LOW);
      delay(100);
    }
    xSemaphoreGive(xSemaphore3);
  }
}

void tasktres(void *parameters) {
  while (1) {
    xSemaphoreTake(xSemaphore3, portMAX_DELAY);
    if(flag == 0)
    {
      digitalWrite(VERDE1, HIGH);
      digitalWrite(ROJO2, HIGH);
      delay(4000);
      digitalWrite(VERDE1, LOW);
    }
    if(flag == 1)
    {
      digitalWrite(ROJO1, HIGH);
      digitalWrite(ROJO2, HIGH);
      delay(100);
      digitalWrite(ROJO1, LOW);
      digitalWrite(ROJO2, LOW);
      delay(100);
    }

    xSemaphoreGive(xSemaphore4);
  }
}

void taskcuatro(void *parameters) {
  while (1) {
    xSemaphoreTake(xSemaphore4, portMAX_DELAY);
    if(flag == 0)
    {
      digitalWrite(AMARILLO1, HIGH);
      delay(1000);
      digitalWrite(AMARILLO1, LOW);
      digitalWrite(ROJO2, LOW);
    }
    if(flag == 1)
    {
      digitalWrite(ROJO1, HIGH);
      digitalWrite(ROJO2, HIGH);
      delay(100);
      digitalWrite(ROJO1, LOW);
      digitalWrite(ROJO2, LOW);
      delay(100);
    }

   xSemaphoreGive(xSemaphore1);
  }
}


void FSM(void *parameters)
{ 
  while(1)
  {
    switch(estado)
    {
      case 0:
        if(digitalRead(2) == HIGH)
        {
          tiempo1 = millis();
          estado = 1;
          

        }
        else
        {
          estado = 0;
          
        }
      break;

      case 1:
        if(((millis() - tiempo1) > 2000) && digitalRead(2) == HIGH)
        {
          estado = 2;
      
        }
        else
        {
          estado = 1;
      
        }
      break;
      
      case 2:
        if(digitalRead(5) == HIGH)
        {
          tiempo1 = millis();
          estado = 3;
    
        }
        else
        {
          estado = 2;
        }
      break;

      case 3:
        if(millis() - tiempo1 > 2000 && digitalRead(5) == HIGH)
        {
          if(flag == 0)
          {
            flag = 1;
          }
          else
          {
            flag = 0;
          }
          estado = 0;
        }
        else
        {
          estado = 3;
        }
      break;

    }
  }
  
}
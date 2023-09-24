//utilizamos core 1
#if CONGIF_FREERTOS_UNICORE
static const BaseType_t app_cpu =0;
#else 
static const BaseType_t app_cpu =1;
#endif

static const int LED01=2;
static const int LED02=4;
static const int LED03=5;
static const int LED04=18;
static const int LED05=19;
static const int LED06=21;
static const int LED07=22;



const char msg[]="Unidad Profesional Interdisciplinaria de Ingenieria Campus Zacatecas IPN";
static TaskHandle_t Tarea01=NULL;
static TaskHandle_t Tarea02=NULL;
static TaskHandle_t Tarea03=NULL;
static TaskHandle_t Tarea04=NULL;
static TaskHandle_t Tarea05=NULL;
static TaskHandle_t Tarea06=NULL;
static TaskHandle_t Tarea07=NULL;



//Tarea UART 01
void TareaUART01(void *parameter){
int msg_len = strlen(msg);

  while(1){
digitalWrite(LED01, HIGH);
Serial.println();
for(int i=0;i<msg_len; i++){
Serial.print(msg[i]);
                            }
Serial.println();
vTaskDelay(100/portTICK_PERIOD_MS);
digitalWrite(LED01, LOW);
vTaskDelay(600/portTICK_PERIOD_MS);

        }

}

//Tarea UART02
void TareaUART02(void *parameter){

  while(1){
digitalWrite(LED02, HIGH);
Serial.println('1');
vTaskDelay(150/portTICK_PERIOD_MS);
digitalWrite(LED02, LOW);
vTaskDelay(600/portTICK_PERIOD_MS);

          }
}

//Tarea UART03
void TareaUART03(void *parameter){

  while(1){
digitalWrite(LED03, HIGH);
Serial.println('2');
vTaskDelay(200/portTICK_PERIOD_MS);
digitalWrite(LED03, LOW);
vTaskDelay(600/portTICK_PERIOD_MS);
        }
}

//Tarea UART4
void TareaUART04(void *parameter){

  while(1){
digitalWrite(LED04, HIGH);
Serial.println('3');
vTaskDelay(250/portTICK_PERIOD_MS);
digitalWrite(LED04, LOW);
vTaskDelay(600/portTICK_PERIOD_MS);
        }
}

//Tarea UART05
void TareaUART05(void *parameter){

  while(1){
digitalWrite(LED05, HIGH);
Serial.println('4');
vTaskDelay(300/portTICK_PERIOD_MS);
digitalWrite(LED05, LOW);
vTaskDelay(600/portTICK_PERIOD_MS);

        }
}

//Tarea UART06
void TareaUART06(void *parameter){

  while(1){
digitalWrite(LED06, HIGH);
Serial.println('5');
vTaskDelay(350/portTICK_PERIOD_MS);
digitalWrite(LED06, LOW);  
vTaskDelay(600/portTICK_PERIOD_MS);

        }
}

//Tarea UART07
void TareaUART07(void *parameter){

  while(1){
digitalWrite(LED07, HIGH);
Serial.println('6');
vTaskDelay(400/portTICK_PERIOD_MS);
digitalWrite(LED07, LOW);
vTaskDelay(600/portTICK_PERIOD_MS);

        }
}

void setup() {
  Serial.begin(300);
pinMode(LED01, OUTPUT);
pinMode(LED02, OUTPUT);
pinMode(LED03, OUTPUT);
pinMode(LED04, OUTPUT);
pinMode(LED05, OUTPUT);
pinMode(LED06, OUTPUT);
pinMode(LED07, OUTPUT);
xTaskCreatePinnedToCore(//Tarea 1

                  TareaUART01, //Funcion que se mand llamar
                    "UART 01", //nombre de la tarea
                    1024,     //Stack size
                    NULL,     //
                    7,        //Prioridades
                    &Tarea01,     //
                    app_cpu);//core
                  
xTaskCreatePinnedToCore(TareaUART02,"UART 02",1024,NULL,6,&Tarea02,app_cpu);//Tarea 2
xTaskCreatePinnedToCore(TareaUART03,"UART 03",1024,NULL,5,&Tarea03,app_cpu);//Tarea 3
xTaskCreatePinnedToCore(TareaUART04,"UART 04",1024,NULL,4,&Tarea04,app_cpu);//Tarea 4
xTaskCreatePinnedToCore(TareaUART05,"UART 05",1024,NULL,3,&Tarea05,app_cpu);//Tarea 5
xTaskCreatePinnedToCore(TareaUART06,"UART 06",1024,NULL,2,&Tarea06,app_cpu);//Tarea 6
xTaskCreatePinnedToCore(TareaUART07,"UART 07",1024,NULL,1,&Tarea07,app_cpu);//Tarea 7



}

void loop() {
//for(int i=0;i<5;i++){
//vTaskSuspend(Tarea01);//suspendemos la tarea
//vTaskDelay(1000/portTICK_PERIOD_MS);//tiempo de suspension 
//vTaskResume(Tarea01);//reanuda la tarea 
//vTaskDelay(1000/portTICK_PERIOD_MS);}

                      }

//vTaskDelete(Tarea02);//borramos la tarea


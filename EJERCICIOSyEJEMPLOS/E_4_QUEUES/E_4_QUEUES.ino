//Ejercicio con Queues
static const uint8_t msg_queue_longitud = 10;
static QueueHandle_t msg_queue;

void MensajeUART(void *parameters)
{
  int valor;
  while(1)
  {
    if(xQueueReceive(msg_queue, (void*)&valor, 0) == true)
    {
    }
    Serial.println(valor);
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(115200);
  msg_queue = xQueueCreate(msg_queue_longitud, sizeof(int));
  xTaskCreatePinnedToCore(MensajeUART,
                          "MensajeUART",
                          1024,
                          NULL,
                          1,
                          NULL,
                          1);
}


void loop()
{
  static int i=0;
  if(xQueueSend(msg_queue, (void*)&i, 10) != true) 
  {
    Serial.println("Queue lleno");
  }
  i++;
  vTaskDelay(500 / portTICK_PERIOD_MS); 
}

#include <Arduino_FreeRTOS.h>
//TickType_t xTimeInTicks = pdMS_TO_TICKS( 3000 );
#define led 3
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
const int prob = A1;
int olcum_sonucu;
void setup(){
   pinMode(led,OUTPUT);
   Serial.begin(9600);
  xTaskCreate(  vTask1,
              (const portCHAR *)"Task 1",
              100,
              NULL,
              1,
              NULL);
 

xTaskCreate(  vTask2,
              (const portCHAR *)"Task 2",
              100,
              NULL,
              2,
              NULL);
              vTaskStartScheduler();
              
}
void loop()
{  
   
}
void vTask1(void *pvParameters)
{
  (void) pvParameters;
 const char *pcTaskName="Task1 çalıştı";
Serial.begin(9600);
  for(;;)
  {
    Serial.println(pcTaskName);
   olcum_sonucu = analogRead(prob);
  Serial.println("topragin nem seviyesi = ");
  Serial.println(olcum_sonucu);
   

   vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}

void vTask2(void *pvParameters)
{
  (void) pvParameters;
  const char *pcTaskName="Task2 çalıştı";

  for(;;)
  {
    Serial.println(pcTaskName);
   int isik = analogRead(A0);
  Serial.println("işik seviyesi=");
  Serial.println(isik);
  delay(500);

  if(isik > 900){
    digitalWrite(led,LOW);
  }

  if(isik < 850){
    digitalWrite(led,HIGH);
  }
   vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}

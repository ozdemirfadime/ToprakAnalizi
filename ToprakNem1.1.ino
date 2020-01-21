#include <Arduino_FreeRTOS.h>
#include "SerialTransfer.h"
#include <EEPROM.h>
//TickType_t xTimeInTicks = pdMS_TO_TICKS( 3000 );
#define led 3
int buzzerPin = 12;
int notaSayisi = 8;
SerialTransfer myTransfer;

int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_ = 523;
int notalar[] = {C, D, E, F, G, A, B, C_};
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
const int prob = A1;
int olcum_sonucu;
int isik = analogRead(A0);
void setup(){
  /*int eepromBellek = EEPROM.length();
for (int i = 0 ; i < eepromBellek ; i++) {EEPROM.write(i, '\0');
EEPROM.read(i);}*/
Serial1.begin(115200);
myTransfer.begin(Serial1);
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
  if(Serial.available() > 0) {
    char data = Serial.read();
    char str[2];
    str[0] = data;
    str[1] = '\0';
    Serial.print(str);
   /* myTransfer.txBuff[0] = olcum_sonucu;
  myTransfer.txBuff[1] = isik;
  myTransfer.sendData(3);
  delay(100);
  
   if(myTransfer.available())
  {
    Serial.println("New Data");
    for(byte i = 0; i < myTransfer.bytesRead; i++)
      Serial.write(myTransfer.rxBuff[i]);
    Serial.println();
  }
  else if(myTransfer.status < 0)
  {
    Serial.print("ERROR: ");
    Serial.println(myTransfer.status);
  }*/
  }
}
void vTask1(void *pvParameters)
{
  (void) pvParameters;
 const char *pcTaskName="Task1 calisiyor";
Serial.begin(9600);
  for(;;)
  {
    Serial.println(pcTaskName);
   olcum_sonucu = analogRead(prob);
  Serial.println("topragin nem seviyesi = ");
  Serial.println(olcum_sonucu);
  delay(1000);
  if(olcum_sonucu > 600)
  {
   for (int i = 0; i < notaSayisi; i++)
  {
    tone(buzzerPin, notalar[i]);
    delay(500);
    noTone(buzzerPin);
    delay(500);
  }
  noTone(buzzerPin);
  }
 
  }

   vTaskDelay(1000/ portTICK_PERIOD_MS);
  }


void vTask2(void *pvParameters)
{
  (void) pvParameters;
  const char *pcTaskName="Task2 calisiyor";

  for(;;)
  {
    Serial.println(pcTaskName);
   int isik = analogRead(A0);
  Serial.println("isik seviyesi=");
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

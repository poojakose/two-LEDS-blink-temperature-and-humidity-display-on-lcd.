
/* 
  two LEDS blink & temperature and humidity display on lcd.
    modified 2/6/17
  by Pooja Kose  
 */

#include <Adafruit_Sensor.h>
#include <Arduino_FreeRTOS.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11,6, 5, 4, 3);

void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
void TaskBlink1( void *pvParameters );


void setup() {
xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"   
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );


xTaskCreate(
    TaskBlink1
    ,  (const portCHAR *)"Blink"   
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );
    
    
  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead"
    ,500// This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  1  // priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(9, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 200 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 200 / portTICK_PERIOD_MS ); // wait for one second
 
  }
  
}
void TaskBlink1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(10, OUTPUT);


  for (;;) // A Task shall never return or exit.
  {
     digitalWrite(10, HIGH);  
 vTaskDelay( 400 / portTICK_PERIOD_MS );            
  digitalWrite(10, LOW);   
vTaskDelay( 400 / portTICK_PERIOD_MS );

  }
  
}
void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
    

  for (;;)
  {
    #define DHTPIN A0
    #define DHTTYPE DHT11
    DHT dht(DHTPIN, DHTTYPE);
    dht.begin();
  int h = dht.readHumidity();
  int t = dht.readTemperature();

   Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
    
    vTaskDelay(1);  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
    lcd.setCursor(5,0);
  lcd.print(t);
    lcd.setCursor(8,0);
  lcd.print("C");
   lcd.setCursor(0,1);
  lcd.print("Humidity: ");
    lcd.setCursor(10,1);
  lcd.print(h); 
  lcd.setCursor(13,1);
  lcd.print("%");
  
  }
}


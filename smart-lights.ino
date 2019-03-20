//for buzzer
#define bzz 12

//for LED
#define LED 2


//for bluetooth
#include <SoftwareSerial.h>
String value;
int TxD = 10;
int RxD = 9;
int servoposition;
SoftwareSerial bluetooth(TxD, RxD);


//for ultrasonic sensor
#include <NewPing.h>
#define TRIGGER_PIN 5
#define ECHO_PIN 6    
#define MAX_DISTANCE 200  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int distance;
int safe_distance = 10000;

  
//for humidity calculation DHT
#include "DHT.h"
#define DHTPIN 11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int room_check = 0;
int food_check = 0;
int humidity_enabler = 0;
float h = 0;

//for temperature calculation DHT
int temperature_enabler = 0;
float t=0;

void setup() {
  // start serial communication at 9600bps
  Serial.begin(9600);       

  //for LDR
  
  
  //for buzzer
  pinMode(bzz, OUTPUT);
  
  // for LED
  pinMode(LED, OUTPUT);

  //for Bluetooth
  bluetooth.begin(9600);

  //for DHT
  dht.begin();
  
}

void loop() {
    
   //for Ultrasonic Sensor
   delay(500);
   distance = sonar.ping_cm();

   //temperature output
   if(temperature_enabler % 50 == 0)
   {
   delay(3000);
   float t = dht.readTemperature(true);
   if(isnan(h))
    {
     Serial.println(F("Failed to read from the DHT sensor!"));
    }
   if(food_check == 1)
    {
     if(h > 70)
     {
      Serial.print("Temperature is high, save your food");
      digitalWrite(bzz, HIGH);
        delay(3000);
        digitalWrite(bzz, LOW);
     } 
    }
    if(room_check == 1)
    {
     if(h > 70)
     {
      Serial.print("Temperature is high, save yourself");
      digitalWrite(bzz, HIGH);
        delay(3000);
        digitalWrite(bzz, LOW);
     } 
    }
   }
   
   //humidity output
   if(humidity_enabler % 50 == 0)
   {
   delay(3000);
   float h = dht.readHumidity();
   if(isnan(h))
    {
     Serial.println(F("Failed to read from the DHT sensor!"));
     digitalWrite(bzz, HIGH);
        delay(3000);
        digitalWrite(bzz, LOW);
    }
   if(food_check == 1)
    {
     if(h > 70)
     {
      Serial.print("Humidity is high, save your food");
      digitalWrite(bzz, HIGH);
        delay(3000);
        digitalWrite(bzz, LOW);
     } 
    }
    if(room_check == 1)
    {
     if(h > 50)
     {
      Serial.print("Humidity is high, save your food");
      digitalWrite(bzz, HIGH);
        delay(3000);
        digitalWrite(bzz, LOW);
     } 
    }
   }

   //bluetooth responses
   if (bluetooth.available())
    {
        value = bluetooth.readString();

    if (value == "calibrate")
      {
        delay(6000);
        Serial.print("safe distance is:");
        safe_distance = distance + 5;
        Serial.println(safe_distance);
        room_check = 0;
        food_check = 0;
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
        delay(500);
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
        delay(500);
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
      }
    if(value == "calibrate for food")
      {
        delay(6000);
        Serial.print("safe distance is:");
        safe_distance = distance + 5;
        Serial.println(safe_distance);
        Serial.println("calibration for food items done");
        room_check = 0;
        food_check = 1;
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
        delay(500);
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
        delay(500);
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
      }
    
    if (value == "calibrate for room")
      {
        delay(6000);
        Serial.print("safe distance is:");
        safe_distance = distance + 5;
        Serial.println(safe_distance);
        Serial.println("Room calibration done");
        room_check = 1;
        food_check = 0;
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
        delay(500);
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
        delay(500);
        digitalWrite(bzz, HIGH);
        delay(500);
        digitalWrite(bzz, LOW);
      }
    }

  if(room_check == 1)
  {
   
  }



  //checks if the LED should turn on or not
  if(safe_distance < distance)
  {
    digitalWrite(LED, HIGH);
    digitalWrite(bzz, HIGH);
    delay(400);
    digitalWrite(bzz, LOW);
  }
  if(safe_distance > distance)
  {
    digitalWrite(LED, LOW);
  }  
  humidity_enabler++;
  temperature_enabler++;
}

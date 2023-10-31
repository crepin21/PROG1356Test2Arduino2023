/*
  Titre      : ProjetTest2
  Auteur     : Crepin Vardin Fouelefack
  Date       : 30/10/2023
  Description: Envoie des valeurs du capteur(DHT11) au serveur
  Version    : 0.0.1
  Sources    : Requette Post ESP32 https://randomnerdtutorials.com/esp32-http-post-ifttt-thingspeak-arduino/
  
               
*/
#include<Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

//#define  MAX_RANG      (520)//the max measurement vaule of the module is 520cm(a little bit longer than  effective max range)
//#define  ADC_SOLUTION      (1023.0)//ADC accuracy of Arduino UNO is 10bit

const char* ssid = "BELL932";
const char* password = "CMR062023";

const int potPin = 35;    // select the input pin 

// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://192.168.2.44:8000/capteur"; //adresse ip de ma machine physique


unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(9600);

  //pinMode(potPin, INPUT);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("5 seconds before publishing the first reading.");
}
float dist_t, sensity_t;

void loop() {
  //Send an HTTP POST request every 5 seconds
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      // Data to send with HTTP POST
       // read the value from the sensor:
      // +TART sensity_t = analogRead(potPin);

      dist_t = 25;           //Valeur fixe car probleme au niveau du fonctionnement du capteur
      Serial.print(dist_t,0);
      String httpRequestData = "nomUc=ESP32&nomCapteur=DHT11&temperature=" + String(dist_t); 
        

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode); //200 si tout fonctionne bien
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}


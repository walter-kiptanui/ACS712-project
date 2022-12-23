#include <ESP8266WiFi.h>
#include "ACS712.h"

String apiKey = "51OH425Z9DCCXVM9";     //  Enter here your Write API key from ThingSpeak.com
const char *ssid = "DESKTOP-BJFO3FU 4725";     // enter your wifi name
const char *pass = "123456789";      // enter your wifi password
const char* server = "api.thingspeak.com";

ACS712 sensor(ACS712_05B, A0);

WiFiClient client;
const int Current1 = A0;


void setup() {
  Serial.begin(115200);
sensor.calibrate();
  
  pinMode(Current1, INPUT);
  //pinMode(relay1, OUTPUT);
  //pinMode(relay2, OUTPUT);
  delay(10);

  Serial.print("Conecting to...");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {
  float Current1 = sensor.getCurrentAC();
  
  Serial.print("The current value of first lamp is:");
  Serial.println(Current1);
  delay(3000);



                      //api.thingspeak.com    
                      if (client.connect(server,80))
                      {
                        String postStr = apiKey;
                        postStr +="&field1=";
                        postStr += String(Current1);
                        //  and so on number of fields could be add,
                        postStr += "\r\n\r\n";

                        client.print("POST /update HTTP/1.1\n");
                        client.print("Host: api.thingspeak.com\n");
                        client.print("Connection: close\n");
                        client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                        client.print("Content-Type: application/x-www-form-urlencoded\n");
                        client.print("Content-Length: ");
                        client.print(postStr.length());
                        client.print("\n\n");
                        client.print(postStr);

                         Serial.print( "The current value is" );
                         Serial.println(Current1);
                         Serial.println(">>>>>>>>>>Sending to Thingspeak<<<<<<<<<<");
                      }

           client.stop();      
delay(2000);
}

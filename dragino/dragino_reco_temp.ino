
#include <SPI.h>
#include <PubSubClient.h>
#include <YunClient.h>
#include <string.h>
#include "DHT.h"

unsigned long time;
//int out2 = 2;
int out3 = 3;
int out4 = 4;
int out6 = 6;

#define DHTPIN 2
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

char message_buff[100];
char message_buff2[100];

////Please here paste info from "devinfo"////////////////
#define IOTUSERNAME "iiiiiiiii"
#define IOTPASSWORD "ppppppp"
#define IOTDEVICE "dddddddd"
#define USERNAME "uuuuuuuuu"
/////////////////////////////////////////////////////////

String id_sensor = "dragino1";

////from here dont' modify anything///////////////////////////////////////////////

#define TOPIC  "redlibre/iot/"USERNAME"/"IOTDEVICE"/"IOTUSERNAME"/iot/control/"
#define STATUS "redlibre/iot/"USERNAME"/"IOTDEVICE"/"IOTUSERNAME"/status/"
#define IOTID USERNAME"/"IOTDEVICE

IPAddress server(190, 97, 169, 126);


void callback(char* topic, byte* payload, unsigned int length);

YunClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);


void callback(char* topic, byte* payload, unsigned int length) {

  int i = 0;
   for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';
  
  String msgString = String(message_buff);
  
 
/*if (msgString.equals("gpio2on")) {
  digitalWrite(out2, HIGH);}
    
else if (msgString.equals("gpio2off")) {
  digitalWrite(out2, LOW);}

else */

if (msgString.equals("gpio3on")) {
  digitalWrite(out3, HIGH);}

else if (msgString.equals("gpio3off")) {
  digitalWrite(out3, LOW);}

else if (msgString.equals("gpio4on")) {
  digitalWrite(out4, HIGH);}

else if (msgString.equals("gpio3off")) {
  digitalWrite(out4, LOW);}

else if (msgString.equals("gpio6on")) {
  digitalWrite(out6, HIGH);}

else if (msgString.equals("gpio6off")) {
  digitalWrite(out6, LOW);}

 
}

long lastReconnectAttempt = 0;

boolean reconnect() {
  if (client.connect(IOTID, IOTUSERNAME, IOTPASSWORD)) {
    
    client.publish(STATUS,"hello - re-authenticated!!");
     client.subscribe(TOPIC);
  }
  return client.connected();
}


void setup()
{
  client.setServer(server, 1883);
  client.setCallback(callback);
  Bridge.begin();
  lastReconnectAttempt = 0;
  
  //pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out6, OUTPUT);
  
dht.begin();
}

void loop()
{
 float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected



if (millis() > (time + 15000)) {
       time = millis();

String pubString = "" + String(t) + "," + String(h) + "," + id_sensor + "";
   pubString.toCharArray(message_buff2, pubString.length()+1);
   client.publish(STATUS,message_buff2);
 
}
    client.loop();
  }

}

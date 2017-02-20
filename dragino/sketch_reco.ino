//Hello!, this is a sketch to get remote control to your dragino device by bridge mode
//The original source and Pubsubclient code comes from: 
//https://github.com/knolleary/pubsubclient
//this is a modified sketch from those repository
//
//Hola ! Este es un sketch de prueba para tomar control remoto de su dispositivo dragino en modo bridge
//la libreria Pubsubclient.* y el codigo fuente proviene desde:
//https://github.com/knolleary/pubsubclient
//y este es un sketch modificado desde el repositorio origen y adaptado para funcionar con nuestra
//plataforma iot.redlibre.cl

//This sketch_reco.ino use a routine to reconnect to mqtt broker if the connection has gone


#include <SPI.h>
#include <PubSubClient.h>
#include <YunClient.h>
#include <string.h>

int out2 = 2;
int out3 = 3;
int out4 = 4;
int out6 = 6;

char message_buff[100];

////Please here paste info from "devinfo"////////////////
#define IOTUSERNAME "ioioioioio"
#define IOTPASSWORD "pppppppp"
#define IOTDEVICE "iiiiiiiii"
#define USERNAME "uuuuuuuu"
/////////////////////////////////////////////////////////


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
  
 
if (msgString.equals("gpio2on")) {
  digitalWrite(out2, HIGH);}
    
else if (msgString.equals("gpio2off")) {
  digitalWrite(out2, LOW);}

else if (msgString.equals("gpio3on")) {
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
  
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out6, OUTPUT);
  

// if (client.connect(IOTID, IOTUSERNAME, IOTPASSWORD)) {
//   client.publish(STATUS,"hello - authenticated!!");
//   client.subscribe(TOPIC);
//  }
}

void loop()
{
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

    client.loop();
  }

}

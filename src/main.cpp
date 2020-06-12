#include <WiFi.h>
#include "globals.h"
#include "wifi_setup.h"
#include "voltage_reader.h"
#include "engine_stat_stop.h"
#include "pin_handlers.h"
#include "automatic.h"
#include "server.h"


//dsad
WiFiServer server(80);

void setup()
{
  Serial.begin(9600);
  wifiSetup();
  pinMode(startPin, OUTPUT);
  pinMode(stopPin, OUTPUT);
  digitalWrite(stopPin, HIGH);
  digitalWrite(startPin, HIGH);
  server.begin();
}

void loop()
{

  
  pinHandler(startPin,startPinTrunedONAt,startPinTrunedOFFAt);
  pinHandler(stopPin,stopPinTunredONAt,stopPinTunredOFFAt);

  voltagePinHandler(wapdaPin,wapdaTunredONAt,wapdaTunredOFFAt);
  voltagePinHandler(genratorPin,genratorTrunedONAt,genratorTrunedOFFAt);

  //    Serial.println("startPin");
  // Serial.println(startPinTrunedONAt);

 
   automatic();


  WiFiClient client = server.available();
  if (client)
  {
    // String client_ip = client.remoteIP().toString();
    // Serial.print("Client connected. IP address = ");
    // Serial.print(client_ip);
    serverGen(client);
   
  }
}

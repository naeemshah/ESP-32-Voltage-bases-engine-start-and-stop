#include <WiFi.h>
#include "helper.h"
#include "wifi_setup.h"
#include "engine_control.h"
#include "getState.h"
#include "server.h"


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

  automatic(automaticStartEnabled);

  WiFiClient client = server.available();
  if (client)
  {
    // String client_ip = client.remoteIP().toString();
    // Serial.print("Client connected. IP address = ");
    // Serial.print(client_ip);
    serverGen(client);
   
  }
}

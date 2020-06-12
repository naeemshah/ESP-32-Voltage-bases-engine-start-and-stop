//===============================================
//=============  WiFi Setup  ====================
//===============================================

void wifiSetup()
{
  const char *ssid = "Gen Wifi";
  const char *password = "12345678";
  Serial.print("Setting soft access point mode");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}

//===============================================
//=============  WiFi Setup Ends ================
//===============================================

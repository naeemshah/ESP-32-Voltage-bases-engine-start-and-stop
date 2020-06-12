


void serverGen(WiFiClient client)
{
    String html = "";
    String request = client.readStringUntil('\r');

    if (request.indexOf("/start") != -1)
    {
        bool starting = (digitalRead(startPin) == 0) ? true : false;
        bool wapdaON = (readVoltage(wapdaPin) > voltageT) ? true : false;
        bool genON = (readVoltage(genratorPin) > voltageT) ? true : false;
        bool anyLight = (wapdaON == true || genON == true);

        if(starting == false and anyLight == false){
        startGenrator();
        html = "{\"status\":1,\"msg\":\"Starting\"}";
        }else{
            html = "{\"status\":1,\"msg\":\" can not start\"}"; 
        }
    }
    else if (request.indexOf("/stop") != -1)
    {
        stopEngine();
        html = "{\"status\":1,\"msg\":\"Stoping\"}";
    }
    else if (request.indexOf("/auto0") != -1)
    {
        automaticStartEnabled = false;
        html = "{\"status\":1,\"msg\":\"Auto Start Disabled\"}";
    }
    else if (request.indexOf("/auto1") != -1)
    {
        automaticStartEnabled = true;
        html = "{\"status\":1,\"msg\":\"Auto Start Enabled\"}";
    }
    else if (request.indexOf("/read") != -1)
    {
        unsigned long timeNow = millis();
        float genratorTime = (genratorTrunedONAt != 0) ?   (timeNow - genratorTrunedONAt) / 1000 : 0;
        float wapdaTime = (wapdaTunredONAt != 0) ?  (timeNow - wapdaTunredONAt) / 1000 : 0;
    
        html = "{\"status\":1,\"light\":";
        html = html + wapdaTime + ",";
        html = html + "\"genrator\":" + genratorTime + ",";

        html = html + "\"genrator Volts\":" + readVoltage(genratorPin) + ",";
        html = html + "\"Wapda Volts\":" + readVoltage(wapdaPin) + ",";
        html = html + "\"startPin\":" + digitalRead(startPin)  + ",";
        html = html + "\"stopPin\":" + digitalRead(stopPin) + ",";
        html = html + "\"automaticStartEnabled\":" + automaticStartEnabled;
        html = html + "}";
    }
    else
    {
        html = "{\"status\":0,\"msg\":\"Not found\"}";
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json;charset=utf-8");
    client.println("Server: Arduino");
    client.println("Connection: close");
    client.println();
    client.println(html);
    client.println();
    html = "";
    request = "";
}
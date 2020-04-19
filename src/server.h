bool automaticStartEnabled = false;


void serverGen(WiFiClient client)
{
    String html = "";
    String request = client.readStringUntil('\r');

    if (request.indexOf("/start") != -1)
    {
        maybeStartGenrator();
        html = "{\"status\":1,\"msg\":\"Starting\"}";
    }
    else if (request.indexOf("/stop") != -1)
    {
        maybeStopEngine();
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
        float wpda = readVoltage(wapdaInput);
        float genrator = readVoltage(genratorInput);
        int startPin = readStartPin();
        int stopPin = readStopPin();
        html = "{\"status\":1,\"light\":";
        html = html + wpda + ",";
        html = html + "\"genrator\":" + genrator + ",";
        html = html + "\"startPin\":" + startPin + ",";
        html = html + "\"stopPin\":" + stopPin + ",";
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
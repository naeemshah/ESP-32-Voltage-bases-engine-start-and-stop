float readVoltage(int pin)
{

    float vout = 0.0;
    float vin = 0.0;
    float R1 = 100000.0; // resistance of R1 (100K) -see text!
    float R2 = 10000.0;  // resistance of R2 (10K) - see text!

    int value = 0;

    value = analogRead(pin);
    vout = (value * 5.0) / 1024.0; // see text
    vin = vout / (R2 / (R1 + R2));
    if (vin < 0.09)
    {
        vin = 0.0; //statement to quash undesired reading !
    }
    //Serial.print("INPUT V= ");
    //Serial.print(vin);
    ///Serial.println();
    //Serial.println("------");

    return vin;
}

bool isLive(int inputPin)
{
    int voltageThreshold = 5;
    return readVoltage(inputPin) > voltageThreshold ? true : false;
}
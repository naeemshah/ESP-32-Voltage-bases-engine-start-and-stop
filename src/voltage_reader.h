
float vout = 0.0;
float vin = 0.0;
float R1 = 20000.0; // resistance of R1 (100K) -see text!
float R2 = 10000.0;  // resistance of R2 (10K) - see text!

int value = 0;

float readVoltage(int pin)
{

    value = analogRead(pin);
    vout = (value * 5.0) / 1024.0; // see text
    vin = vout / (R2 / (R1 + R2));
    if (vin < 0.09)
    {
        vin = 0; //statement to quash undesired reading !
    }
    //    Serial.print("INPUT V= ");
    //    Serial.print(vin);
    //    Serial.println();
    //    Serial.println("------");

    return vin;
}
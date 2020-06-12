

void startGenrator()
{
    bool genON = (readVoltage(genratorPin) > voltageT) ? true : false;
    if (genON == false)
    {
        genON = (readVoltage(genratorPin) > voltageT) ? true : false;

        if (genON == false)
        {
            genON = (readVoltage(genratorPin) > voltageT) ? true : false;
            if (genON == false)
            {
                digitalWrite(startPin, LOW);
                digitalWrite(stopPin, HIGH);
            }
        }
    }
}

void stopEngine()
{

    digitalWrite(startPin, HIGH);
    digitalWrite(stopPin, LOW);
}

void stopSlip()
{
    digitalWrite(startPin, HIGH);
    digitalWrite(stopPin, HIGH);
}

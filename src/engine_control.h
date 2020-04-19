int startPin = 22;
int stopPin = 23;

int readStartPin()
{
    return digitalRead(startPin);
}

void startEngine()
{
    digitalWrite(stopPin, HIGH);
    digitalWrite(startPin, LOW);
}

void stopEngine()
{
    digitalWrite(stopPin, LOW);
    digitalWrite(startPin, HIGH);
}

void stopSlip()
{
    digitalWrite(startPin, HIGH);
}

void stopStoping()
{
    digitalWrite(stopPin, HIGH);
}




int readStopPin()
{
    return digitalRead(stopPin);
}
void automatic()
{
    unsigned long timeNow = millis();

    bool starting = (digitalRead(startPin) == 0) ? true : false;
    bool stopping = (digitalRead(stopPin) == 0) ? true : false;
    bool wapdaON = (readVoltage(wapdaPin) > voltageT) ? true : false;
    bool genON = (readVoltage(genratorPin) > voltageT) ? true : false;
    bool anyLight = (wapdaON == true || genON == true);

    if (genON == true && wapdaON == false && stopping == true)
    {
        stopSlip();
    }

    if (starting && ((timeNow - startPinTrunedONAt) > slipTime || anyLight))
    {
        if (timeNow - startPinTrunedONAt > 1000)
        {
            Serial.println("slip stop");
            stopSlip();
        }
    }
    else if (starting == false)
    {
        if (wapdaON == false and genON == false)
        {
            bool isFirstSlip2 = (Slips == 1) ? true : false;
            genON = (readVoltage(genratorPin) > voltageT) ? true : false;
            bool shouldSlipMore = (Slips < maxNumberOfSlips and Slips > 1 && startPinTrunedOFFAt != 0 and (timeNow - startPinTrunedOFFAt) > waitTimeBetweenSlips) ? true : false;
            if (genON == false && automaticStartEnabled && (shouldSlipMore || isFirstSlip2))
            {
                Serial.println("Gen should start ");
                Serial.println(Slips);
                startGenrator();
                Slips++;
            }
        }
        else if (wapdaON == true and genON == true)
        {

            if (wapdaON == true and timeNow - wapdaTunredONAt > 60000 && stopping == false)
            {
                Serial.println("Gen should stop ");
                stopEngine();
                Slips = 1;
            }
        }
        else
        {
            /// Serial.println("Nothing 1");
        }
    }
    else
    {
        // Serial.println("Nothing 2");
    }
}
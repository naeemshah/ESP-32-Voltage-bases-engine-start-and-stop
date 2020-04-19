
unsigned long genratorTrunedONAt = 0;
unsigned long wapdaTunredONAt = 0;
unsigned long genratorTrunedOFFAt = 0;
unsigned long wapdaTunredOFFAt = 0;
unsigned long lastSlipStoppedAt = 0;

bool genratorState = false;
bool wapdaState = false;

unsigned long startPinTrunedONAt = 0;
unsigned long stopPinTunredONAt = 0;
int startPinState = 1;
int stopPinState = 1;
;

int slipTime = 4000;
int maxNumberOfSlips = 3;
int Slips = 1; // current slips number
int waitTimeBetweenSlips = 4000;
int wapdaInput = 34;
int genratorInput = 35;

void maybeStartGenrator()
{

    if (isLive(genratorInput) == false and readStartPin() == 1)
    {
        Serial.println("Starting enginee manully");
        startEngine();
        startPinTrunedONAt = millis();
        stopPinTunredONAt = 0;
    }
}

void maybeStopEngine()
{

    Serial.println("stopEngine manully");
    stopEngine();
    stopPinTunredONAt = millis();
    startPinTrunedONAt = 0;
}

void stateManager(bool wapdaStateprev, bool genratorStatePrve, bool wapdaState, bool genratorState)
{
    unsigned long timeNow = millis();

    // is gen trured off
    if (genratorState == true and genratorState != genratorStatePrve)
    {
        genratorTrunedONAt = timeNow;
        genratorTrunedOFFAt = 0;
    }
    else if (genratorState == false and genratorState != genratorStatePrve)
    {
        genratorTrunedONAt = 0;
        genratorTrunedOFFAt = timeNow;
    }

    //=======  us wapda truned of

    if (wapdaState == true and wapdaState != wapdaStateprev)
    {
        wapdaTunredONAt = timeNow;
        wapdaTunredOFFAt = 0;
    }
    else if (wapdaState == false and wapdaState != wapdaStateprev)
    {

        wapdaTunredOFFAt = timeNow;
        wapdaTunredONAt = 0;
    }
}

void automatic(bool automaticStartEnabled)
{

    bool wapdaStateprev = wapdaState;
    bool genratorStatePrve = genratorState;
    wapdaState = isLive(wapdaInput);
    genratorState = isLive(genratorInput);

    stateManager(wapdaStateprev, genratorStatePrve, wapdaState, genratorState);

    // Serial.println("wapdaState");
    // Serial.println(wapdaState);

    // Serial.println("genratorState");
    // Serial.println(genratorState);

    startPinState = readStartPin();
    stopPinState = readStopPin();

    unsigned long timeNow = millis();

    Slips = (genratorState == true) ? 1 : Slips;

    //****************  Adjust startPins *********************
    bool timePassedLastSlip = (startPinTrunedONAt != 0 and (timeNow - startPinTrunedONAt) > slipTime);
    bool timePassedGenrtorOn = (startPinState == 0 and genratorTrunedONAt != 0 and (timeNow - genratorTrunedONAt > 1000)); // to avoid stopping slip prematurely

    if ((startPinState == 0 and timePassedLastSlip == true) or timePassedGenrtorOn or (wapdaState == true and startPinState == 0))
    {
        Serial.println("stopSlip");
        stopSlip();
        startPinTrunedONAt = 0;
        lastSlipStoppedAt = timeNow;
    }

    if ((stopPinState == 0 and stopPinTunredONAt != 0 and (timeNow - stopPinTunredONAt) > 6000))
    {
        Serial.println("stopStoping");
        stopStoping();
        stopPinTunredONAt = 0;
    }
    //********************************************************

    if (wapdaState == true and genratorState == true)
    {
        bool enyoughTimePassed = (genratorTrunedONAt != 0 and (timeNow - genratorTrunedONAt) > 60000);
        bool canStop = (stopPinState == 1 and enyoughTimePassed == true) ? true : false;
        if (canStop == true)
        {
            Serial.println("stopEngine");
            stopEngine();
            stopPinTunredONAt = millis();
            startPinTrunedONAt = 0;
        }
    }
    else if (wapdaState == false and genratorState == false)
    {
        // turn on genrator

        bool timePassed = (Slips == 1 or (lastSlipStoppedAt != 0 and ((timeNow - lastSlipStoppedAt) > waitTimeBetweenSlips)));
        bool canStart = (Slips <= maxNumberOfSlips and startPinState == 1 and timePassed == true) ? true : false;
        canStart = (automaticStartEnabled == true) ? canStart : false;
        if (canStart == true)
        {
            Serial.println("Starting enginee");
            startEngine();
            startPinTrunedONAt = millis();
            lastSlipStoppedAt = 0;
            stopPinTunredONAt = 0;
            Slips++;
        }
    }
}

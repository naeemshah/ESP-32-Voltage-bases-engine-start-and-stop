void pinHandler(int pin, unsigned long &pinNoTime, unsigned long &pinOFFTime)
{
 bool isPinOn = (pinNoTime == 0) ? false : true;
  bool pinCurrentlyOn = (digitalRead(pin)  == 1) ? false : true;
  bool pinJustTurnedOn = (isPinOn == false and pinCurrentlyOn == true) ? true : false;
  bool pinJustTurnedOff = (isPinOn == true and pinCurrentlyOn == false) ? true : false;

  // Serial.println("pinJustTurnedOn");
  //Serial.println(pinCurrentlyOn);
  if (pinJustTurnedOn == true and pinJustTurnedOff == false)
  {
    
    pinNoTime = millis();
    pinOFFTime = 0;
  }
  else if (pinJustTurnedOff == true and pinJustTurnedOn == false)
  {
    pinNoTime = 0;
    pinOFFTime = millis();
  }
}

void voltagePinHandler(int pin, unsigned long &pinNoTime, unsigned long &pinOFFTime)
{

  bool isPinOn = (pinNoTime == 0) ? false : true;
  bool pinCurrentlyOn = (readVoltage(pin) > voltageT) ? true : false;
  bool pinJustTurnedOn = (isPinOn == false and pinCurrentlyOn == true) ? true : false;
  bool pinJustTurnedOff = (isPinOn == true and pinCurrentlyOn == false) ? true : false;

  // Serial.println("pinJustTurnedOn");
  //Serial.println(pinCurrentlyOn);
  if (pinJustTurnedOn == true and pinJustTurnedOff == false)
  {
    
    pinNoTime = millis();
    pinOFFTime = 0;
  }
  else if (pinJustTurnedOff == true and pinJustTurnedOn == false)
  {
    pinNoTime = 0;
    pinOFFTime = millis();
  }
}
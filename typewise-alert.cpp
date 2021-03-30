#include "typewise-alert.h"
#include <iostream>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  double lowerLimit = CoolingLimitsMap[coolingType].first;
  double upperLimit = CoolingLimitsMap[coolingType].second;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert( AlertTarget *alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC);

  alertTarget->sendAlert(breachType);

}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  std::cout << std::hex << header << " : " << std::hex << breachType << std::endl;
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if (breachType != NORMAL)
  {
      std::cout << "To: " << recepient <<"\n" << EmailMsgMap[breachType] << std::endl;
  }
}

void EmailAlert::sendAlert(BreachType breachType)
{
    sendToEmail(breachType);
}

void ControllerAlert::sendAlert(BreachType breachType)
{
    sendToController(breachType);
}

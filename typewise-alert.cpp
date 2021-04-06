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
  std::cout << "To: " << recepient << "\n" << EmailMsgMap[breachType] << std::endl;
}

void sendToConsole(BreachType breachType){
    std::cout << "Breach Detected: " << ConsoleMsgMap[breachType] << std::endl;
}

void EmailAlert::sendAlert(BreachType breachType)
{
    if (breachType != NORMAL)
    {
        sendToEmail(breachType);
        m_EmailAlertSent = true;
    }
}

bool EmailAlert::isAlertSent()
{
    return m_EmailAlertSent;
}

void ControllerAlert::sendAlert(BreachType breachType)
{

    sendToController(breachType);
    m_ControllerAlertSent = true;

}

bool ControllerAlert::isAlertSent()
{
    return m_ControllerAlertSent;
}

void ConsoleAlert::sendAlert(BreachType breachType)
{
    if (breachType != NORMAL)
    {
        sendToConsole(breachType);
        m_ConsoleAlertSent = true;
    }
}

bool ConsoleAlert::isAlertSent()
{
    return m_ConsoleAlertSent;
}

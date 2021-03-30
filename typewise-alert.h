#pragma once
#include<map>
#include<string>

typedef std::pair<double, double> limits;

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

static std::map<CoolingType, limits> CoolingLimitsMap =
{
	{PASSIVE_COOLING , std::make_pair(0,35)},
	{HI_ACTIVE_COOLING , std::make_pair(0,45)},
	{MED_ACTIVE_COOLING , std::make_pair(0,40)}
};

static std::map<BreachType, std::string> EmailMsgMap =
{
	{TOO_LOW , "Hi, the temperature is too low\n"},
	{TOO_HIGH , "Hi, the temperature is too high\n"}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

class AlertTarget
{
public:
	virtual void sendAlert(BreachType) = 0;
};

class EmailAlert : public AlertTarget
{
public:
	void sendAlert(BreachType);
};

class ControllerAlert : public AlertTarget
{
public:
	void sendAlert(BreachType);
};

void checkAndAlert(AlertTarget* alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

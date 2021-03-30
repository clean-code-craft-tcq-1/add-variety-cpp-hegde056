#pragma once
#include<map>

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

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

//typedef enum {
//  TO_CONTROLLER,
//  TO_EMAIL
//} AlertTarget;

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

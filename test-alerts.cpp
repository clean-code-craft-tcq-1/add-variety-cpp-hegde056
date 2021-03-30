#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("check and alert via email") {
	AlertTarget* emailAlertobj = new EmailAlert;
	BatteryCharacter newbattery = { PASSIVE_COOLING , "Voltas"};
	checkAndAlert( emailAlertobj , newbattery , 55) ;
}

TEST_CASE("check and alert via controller") {
	AlertTarget* controllerAlertobj = new ControllerAlert;
	BatteryCharacter newbattery = { MED_ACTIVE_COOLING , "Exide" };
	checkAndAlert(controllerAlertobj, newbattery, 50);
}
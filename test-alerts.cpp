#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits - Test for Low Breach") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits - Test for High Breach") {
	REQUIRE(inferBreach(32, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to limits - Test for No Breach") {
	REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("classifies the temperature breach for passive cooling- Test for Low Breach") {
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1.0) == TOO_LOW);
}

TEST_CASE("classifies the temperature breach - Test for High Breach") {
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
}

TEST_CASE("classifies the temperature breach for high active cooling - Test for Low Breach") {
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1.0) == TOO_LOW);
}

TEST_CASE("classifies the temperature breach for high active cooling - Test for High Breach") {
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("classifies the temperature breach for med active cooling - Test for Low Breach") {
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1.0) == TOO_LOW);
}

TEST_CASE("classifies the temperature breach for med active cooling - Test for High Breach") {
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("check and alert via email - Test for Alert") {
	AlertTarget* emailAlertobj = new EmailAlert;
	BatteryCharacter newbattery = { PASSIVE_COOLING , "Exide"};
	checkAndAlert( emailAlertobj , newbattery , 55) ;
	REQUIRE(emailAlertobj->isAlertSent() == true);
}

TEST_CASE("check and alert via email - Test for No alert") {
	AlertTarget* emailAlertobj = new EmailAlert;
	BatteryCharacter newbattery = { HI_ACTIVE_COOLING , "Amara Raja" };
	checkAndAlert(emailAlertobj, newbattery, 30);
	REQUIRE(emailAlertobj->isAlertSent() == false);
}

TEST_CASE("check and alert via controller - Test for alert") {
	AlertTarget* controllerAlertobj = new ControllerAlert;
	BatteryCharacter newbattery = { MED_ACTIVE_COOLING , "Duracell" };
	checkAndAlert(controllerAlertobj, newbattery, 50);
	REQUIRE(controllerAlertobj->isAlertSent() == true);
}

TEST_CASE("check and alert via controller - Test for No alert??") {
	AlertTarget* controllerAlertobj = new ControllerAlert;
	BatteryCharacter newbattery = { MED_ACTIVE_COOLING , "Duracell" };
	checkAndAlert(controllerAlertobj, newbattery, 30);
	REQUIRE(controllerAlertobj->isAlertSent() == true);
}

TEST_CASE("check and alert via console - Test for Alert") {
	AlertTarget* consoleAlertobj = new ConsoleAlert;
	BatteryCharacter newbattery = { PASSIVE_COOLING , "Exide" };
	checkAndAlert(consoleAlertobj, newbattery, -5);
	REQUIRE(consoleAlertobj->isAlertSent() == true);
}

TEST_CASE("check and alert via console - Test for No alert") {
	AlertTarget* consoleAlertobj = new ConsoleAlert;
	BatteryCharacter newbattery = { HI_ACTIVE_COOLING , "Amara Raja" };
	checkAndAlert(consoleAlertobj, newbattery, 30);
	REQUIRE(consoleAlertobj->isAlertSent() == false);
}
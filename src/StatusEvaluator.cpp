#include "../res/StatusEvaluator.h"

//Ranges for each measurement to be randomized
//These do not match the ranges for a valid reading. Those are in the TelemetryValidator
constexpr double lTemp = 195;
constexpr double hTemp = 220;
constexpr double lPressure = 30;
constexpr double hPressure = 60;
constexpr double lRpm = 2200;
constexpr double hRpm = 2700;
constexpr double lFuel = 25;
constexpr double hFuel = 50;

void StatusEvaluator::EvaluateReading(TelemetryData& reading)
{
	//Any reading that is on the 10% edge of the ranges will be a fail for the device
	//Any reading that is on the 30% edge of the ranges will be a warning for the device

	double tempPercentage = (reading.temperature - lTemp) / (hTemp - lTemp) * 100;
	double pressurePercentage = (reading.pressure - lPressure) / (hPressure - lPressure) * 100;
	double rpmPercentage = (reading.rpm - lRpm) / (hRpm - lRpm) * 100;
	double fuelPercentage = (reading.fuel - lFuel) / (hFuel - lFuel) * 100;

	reading.deviceStatus = NORMAL;

	if (tempPercentage <= 30 || tempPercentage >= 70)
		reading.deviceStatus = WARNING;
	if (pressurePercentage <= 30 || pressurePercentage >= 70)
		reading.deviceStatus = WARNING;
	if (rpmPercentage <= 30 || rpmPercentage >= 70)
		reading.deviceStatus = WARNING;
	if (fuelPercentage <= 30 || fuelPercentage >= 70)
		reading.deviceStatus = WARNING;
	if (tempPercentage <= 10 || tempPercentage >= 90)
		reading.deviceStatus = FAIL;
	if (pressurePercentage <= 10 || pressurePercentage >= 90)
		reading.deviceStatus = FAIL;
	if (rpmPercentage <= 10 || rpmPercentage >= 90)
		reading.deviceStatus = FAIL;
	if (fuelPercentage <= 10 || fuelPercentage >= 90)
		reading.deviceStatus = FAIL;
}

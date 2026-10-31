#include "sim.h"

#include <iostream>
#include <random>
#include <string>

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

std::string DetermineStatus(const TelemetryMessage& tele)
{
	//Any reading that is on the 10% edge of the ranges will be a fail for the device
	//Any reading that is on the 30% edge of the ranges will be a warning for the device
	
	double tempPercentage = (tele.temperature - lTemp) / (hTemp - lTemp) * 100;
	double pressurePercentage = (tele.pressure - lPressure) / (hPressure - lPressure) * 100;
	double rpmPercentage = (tele.rpm - lRpm) / (hRpm - lRpm) * 100;
	double fuelPercentage = (tele.fuel - lFuel) / (hFuel - lFuel) * 100;
	
	if (tempPercentage <= 10 || tempPercentage >= 90)
		return "FAIL";

	if (pressurePercentage <= 10 || pressurePercentage >= 90)
		return "FAIL";

	if (rpmPercentage <= 10 || rpmPercentage >= 90)
		return "FAIL";

	if (fuelPercentage <= 10 || fuelPercentage >= 90)
		return "FAIL";

	if (tempPercentage <= 30 || tempPercentage >= 70)
		return "WARNING";

	if (pressurePercentage <= 30 || pressurePercentage >= 70)
		return "WARNING";

	if (rpmPercentage <= 30 || rpmPercentage >= 70)
		return "WARNING";

	if (fuelPercentage <= 30 || fuelPercentage >= 70)
		return "WARNING";

	return "NORMAL";
}

std::vector<TelemetryMessage> GenerateReadings(int numReadings)
{
	std::vector<TelemetryMessage> teleMessageVector;

	if (numReadings < 1)
	{
		teleMessageVector.clear();
		std::cout << "Readings requested less than 1\n";
		return teleMessageVector;
	}

	//rng setup
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_real_distribution<double> temperatureRange(lTemp, hTemp);
	std::uniform_real_distribution<double> pressureRange(lPressure, hPressure);
	std::uniform_real_distribution<double> rpmRange(lRpm, hRpm);
	std::uniform_real_distribution<double> fuelRange(lFuel, hFuel);
	
	for (int i = 0; i < numReadings; i++)
	{
		TelemetryMessage tele;
		tele.deviceID = "ENGINE" + std::to_string(i + 1);
		tele.temperature = temperatureRange(rng);
		tele.pressure = pressureRange(rng);
		tele.rpm = rpmRange(rng);
		tele.fuel = fuelRange(rng);
		tele.messageDeviceStatus = DetermineStatus(tele);
		teleMessageVector.push_back(tele);
	}
	
	return teleMessageVector;
}
#include "sim.h"

#include <iostream>
#include <random>
#include <string>

std::vector<TelemetryMessage> GenerateReadings(int numReadings)
{
	//rng setup
	std::random_device seed;
	std::mt19937 rng(seed());
	std::uniform_real_distribution<double> temperatureRange(195, 220);
	std::uniform_real_distribution<double> pressureRange(30, 60);
	std::uniform_real_distribution<double> rpmRange(2200, 2700);
	std::uniform_real_distribution<double> fuelRange(25, 50);

	std::vector<TelemetryMessage> teleMessageVector;
	
	for (int i = 0; i < numReadings; i++)
	{
		TelemetryMessage tele;
		tele.deviceID = "ENGINE" + std::to_string(i + 1);
		tele.temperature = temperatureRange(rng);
		tele.pressure = pressureRange(rng);
		tele.rpm = rpmRange(rng);
		tele.fuel = fuelRange(rng);
		tele.deviceStatus = NORMAL;
		teleMessageVector.push_back(tele);
	}
	
	return teleMessageVector;
}
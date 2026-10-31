#pragma once
#include <vector>

#include "../res/TelemetryData.h"

class TelemetryProcessor
{
public:
	//Get average temperature of readings. Can be the same device over time or a bunch of different devices at once
	double AverageTemperature(const std::vector<TelemetryData>& telemetryData);
	//Get average pressure of readings. Can be the same device over time or a bunch of different devices at once
	double AveragePressure(const std::vector<TelemetryData>& telemetryData);
	//Get average rpm of readings. Can be the same device over time or a bunch of different devices at once
	double AverageRpm(const std::vector<TelemetryData>& telemetryData);
	//Get average fuel of readings. Can be the same device over time or a bunch of different devices at once
	double AverageFuel(const std::vector<TelemetryData>& telemetryData);

	//Get lowest temperature of readings. Can be the same device over time or a bunch of different devices at once
	double MinimumTemperature(const std::vector<TelemetryData>& telemetryData);
};
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
	TelemetryData MinimumTemperature(const std::vector<TelemetryData>& telemetryData);
	//Get lowest pressure of readings. Can be the same device over time or a bunch of different devices at once
	TelemetryData MinimumPressure(const std::vector<TelemetryData>& telemetryData);
	//Get lowest RPM of readings. Can be the same device over time or a bunch of different devices at once
	TelemetryData MinimumRpm(const std::vector<TelemetryData>& telemetryData);
	//Get lowest fuel of readings. Can be the same device over time or a bunch of different devices at once
	TelemetryData MinimumFuel(const std::vector<TelemetryData>& telemetryData);

	//Get highest temperature of readings. Can be the same device over time or a bunch of different devices at once
	TelemetryData MaxTemperature(const std::vector<TelemetryData>& telemetryData);
	//Get highest pressure of readings. Can be the same device over time or a bunch of different devices at once
	TelemetryData MaxPressure(const std::vector<TelemetryData>& telemetryData);
	//Get highest RPM of readings. Can be the same device over time or a bunch of different devices at once
	TelemetryData MaxRpm(const std::vector<TelemetryData>& telemetryData);
	//Get highest fuel of readings. Can be the same device over time or a bunch of different devices at once
	TelemetryData MaxFuel(const std::vector<TelemetryData>& telemetryData);
};

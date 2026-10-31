#pragma once
#include <vector>

#include "../res/TelemetryMessage.h"

class TelemetryProcessor
{
public:
	//Get average temperature of readings. Can be the same device over time or a bunch of different devices at once
	double AverageTemperature(const std::vector<TelemetryMessage>& telemetryMessages);
};
#pragma once
#include "../res/TelemetryData.h"

class StatusEvaluator
{
public:
	void EvaluateReading(TelemetryData& reading);
};
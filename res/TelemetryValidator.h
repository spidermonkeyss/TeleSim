#pragma once
#include "../res/TelemetryData.h"

class TelemetryValidator
{
public:
	bool ValidateTelemetry(const TelemetryData& tele);

private:
	bool ValidateDeviceId(const std::string& deviceID);
	bool ValidateTemperature(const double temperature);
	bool ValidatePressure(const double pressure);
	bool ValidateRpm(const double rpm);
	bool ValidateFuel(const double fuel);

	static constexpr double invalidLowTemperature = -20;
	static constexpr double invalidHighTemperature = 300;

	static constexpr double invalidLowPressure = 0;
	static constexpr double invalidHighPressure = 150;

	static constexpr double invalidLowRpm = 0;
	static constexpr double invalidHighRpm = 6000;

	static constexpr double invalidLowFuel = 0;
	static constexpr double invalidHighFuel = 51;

};
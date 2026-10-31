#include "../res/TelemetryValidator.h"

bool TelemetryValidator::ValidateTelemetry(TelemetryMessage tele)
{
	bool validID = ValidateDeviceId(tele.deviceID);
	bool validTemperature = ValidateTemperature(tele.temperature);
	bool validPressure = ValidatePressure(tele.pressure);
	bool validRpm = ValidateRpm(tele.rpm);
	bool validFuel = ValidateFuel(tele.fuel);

	return (validID && validTemperature && validPressure && validRpm && validFuel);
}

bool TelemetryValidator::ValidateDeviceId(const std::string& deviceID)
{
	if (deviceID.empty() || deviceID == "")
	{
		//TODO: log reason
		return false;
	}

	return true;
}

bool TelemetryValidator::ValidateTemperature(const double temperature)
{
	if (temperature <= invalidLowTemperature)
	{
		//TODO: log
		return false;
	}
	
	if (temperature >= invalidHighTemperature)
	{
		//TODO: log
		return false;
	}

	return true;
}

bool TelemetryValidator::ValidatePressure(const double pressure)
{
	if (pressure <= invalidLowPressure)
	{
		//TODO: log
		return false;
	}

	if (pressure >= invalidHighPressure)
	{
		//TODO: log
		return false;
	}

	return true;
}

bool TelemetryValidator::ValidateRpm(const double rpm)
{
	if (rpm <= invalidLowRpm)
	{
		//TODO: log
		return false;
	}

	if (rpm >= invalidHighRpm)
	{
		//TODO: log
		return false;
	}

	return true;
}

bool TelemetryValidator::ValidateFuel(const double fuel)
{
	if (fuel <= invalidLowFuel)
	{
		//TODO: log
		return false;
	}

	if (fuel >= invalidHighFuel)
	{
		//TODO: log
		return false;
	}

	return true;
}

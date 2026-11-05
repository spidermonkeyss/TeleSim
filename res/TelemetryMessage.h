#pragma once

#include <string>


struct TelemetryMessage
{
	std::string deviceID;
	double temperature;
	double pressure;
	double rpm;
	double fuel;
	//std::string messageDeviceStatus;
};
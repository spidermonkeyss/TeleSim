#pragma once

#include <string>

enum DeviceStatus { NORMAL, WARNING, FAIL };

struct TelemetryData
{
	std::string deviceID;
	double temperature;
	double pressure;
	double rpm;
	double fuel;
	DeviceStatus deviceStatus;
};
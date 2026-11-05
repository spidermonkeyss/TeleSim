#pragma once
#include <unordered_map>
#include <string>
#include <optional>
#include <vector>

#include "../res/TelemetryData.h"

class DeviceRegistry
{
public:
	bool HasDevice(const std::string& deviceID) const;
	bool HasDevice(const TelemetryData& data) const;

	//The data must go through TelemetryValidator first
	void UpdateDevice(TelemetryData data);
	
	std::optional<TelemetryData> GetDevice(const std::string& deviceID) const;
	std::vector<TelemetryData> GetAllDevices() const;
	
	void ClearDevices();
	
	void DeleteDevice(const TelemetryData& data);
	void DeleteDevice(const std::string& deviceID);

	size_t DeviceCount();

private:
	//last reading of each device
	std::unordered_map<std::string, TelemetryData> devices;
};
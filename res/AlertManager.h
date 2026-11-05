#pragma once
#include <unordered_map>
#include <optional>

#include "../res/TelemetryData.h"

class AlertManager
{
public:
	struct Alert 
	{ 
		std::string deviceID;
		DeviceStatus deviceStatus;
		std::string description;
	};


	bool HasAlert(const std::string& deviceID) const;
	const std::optional<Alert> GetAlert(const std::string& deviceID) const;
	void ProcessReading(const TelemetryData& reading);
private:
	std::unordered_map<std::string, Alert> alerts;

	void CreateWarningAlert(const std::string& deviceID, const std::string& description);
	void CreateFailAlert(const std::string& deviceID, const std::string& description);
	void ResolveAlert(const std::string& deviceID);
};
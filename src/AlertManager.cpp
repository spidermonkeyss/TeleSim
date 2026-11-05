#include "../res/AlertManager.h"

bool AlertManager::HasAlert(const std::string& deviceID) const
{
	auto alert = alerts.find(deviceID);
	return (alert != alerts.end());
}

std::optional<AlertManager::Alert> AlertManager::GetAlert(const std::string& deviceID) const
{
	auto alert = alerts.find(deviceID);
	if (alert == alerts.end())
		return std::nullopt;
	else
		return alert->second;
}

void AlertManager::ProcessReading(const TelemetryData& reading)
{
	auto alert = alerts.find(reading.deviceID);
	if (alert != alerts.end())
	{
		//has a warning or fail alert
		if (reading.deviceStatus == NORMAL)
			ResolveAlert(reading.deviceID);
		else if (reading.deviceStatus == WARNING)
		{
			if (alert->second.deviceStatus == WARNING)
				return;
			else if (alert->second.deviceStatus == FAIL)
				CreateWarningAlert(reading.deviceID, alert->second.description);
		}
		else if (reading.deviceStatus == FAIL)
		{
			if (alert->second.deviceStatus == WARNING)
				CreateFailAlert(reading.deviceID, alert->second.description);
			else if (alert->second.deviceStatus == FAIL)
				return;
		}
	}
	else
	{
		//no alert
		if (reading.deviceStatus == NORMAL)
			return;
		else if (reading.deviceStatus == WARNING)
			CreateWarningAlert(reading.deviceID, "TEST DESCRIPTION");
		else if (reading.deviceStatus == FAIL)
			CreateFailAlert(reading.deviceID, "TEST DESCRIPTION");
	}
}

void AlertManager::CreateWarningAlert(const std::string& deviceID, const std::string& description)
{
	alerts[deviceID] = { deviceID, WARNING, description };
}

void AlertManager::CreateFailAlert(const std::string& deviceID, const std::string& description)
{
	alerts[deviceID] = { deviceID, FAIL, description };
}

void AlertManager::ResolveAlert(const std::string& deviceID)
{
	alerts.erase(deviceID);
}

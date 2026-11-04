#include "../res/DeviceRegistry.h"

bool DeviceRegistry::HasDevice(const std::string& deviceID)
{
	auto device = devices.find(deviceID);
	return (device != devices.end());
}

bool DeviceRegistry::HasDevice(TelemetryData data)
{
	return HasDevice(data.deviceID);
}

void DeviceRegistry::UpdateDevice(TelemetryData data)
{
	devices[data.deviceID] = data;
}

std::optional<TelemetryData> DeviceRegistry::GetDevice(const std::string& deviceID) const
{
	auto device = devices.find(deviceID);
	if (device == devices.end())
		return std::nullopt;
	else
		return device->second;
}

std::vector<TelemetryData> DeviceRegistry::GetAllDevices() const
{
	std::vector<TelemetryData> data;

	for (const auto& device : devices)
		data.push_back(device.second);

	return data;
}

void DeviceRegistry::ClearDevices()
{
	devices.clear();
}

void DeviceRegistry::DeleteDevice(TelemetryData data)
{
	devices.erase(data.deviceID);
}

void DeviceRegistry::DeleteDevice(const std::string& deviceID)
{
	devices.erase(deviceID);
}

size_t DeviceRegistry::DeviceCount()
{
	return devices.size();
}

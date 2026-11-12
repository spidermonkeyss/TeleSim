#include <iostream>
#include <thread>
#include <chrono>

#include "../sensorsim/sim.h"
#include "../res/TelemetryValidator.h"
#include "../res/TelemetryProcessor.h"
#include "../res/TelemetryData.h"
#include "../res/DeviceRegistry.h"
#include "../res/AlertManager.h"
#include "../res/StatusEvaluator.h"
#include "../res/TelemetryMessageQueue.h"

void DisplayTelemetryMessagesToConsole(std::vector<TelemetryMessage> messages, int tabs)
{
	std::string str = "";
	std::string strTabs = "";
	for (int i = 0; i < tabs; i++)
		strTabs += "\t";

	for (const auto& message : messages)
	{
		str += strTabs + "DeviceID: " + message.deviceID + "\n";
		str += strTabs + "Temp: " + std::to_string(message.temperature) + "\n";
		str += strTabs + "Pressure: " + std::to_string(message.pressure) + "\n";
		str += strTabs + "RPM: " + std::to_string(message.rpm) + "\n";
		str += strTabs + "fuel: " + std::to_string(message.fuel) + "\n";
		//str += strTabs + "Status: " + message.messageDeviceStatus + "\n\n";
	}

	std::cout << str;
}

void DisplayTelemetryDataToConsole(const std::vector<TelemetryData>& telemetryData, int tabs)
{
	std::string str = "";
	std::string strTabs = "";
	for (int i = 0; i < tabs; i++)
		strTabs += "\t";

	for (const auto& data : telemetryData)
	{
		str += strTabs + "DeviceID: " + data.deviceID + "\n";
		str += strTabs + "Temp: " + std::to_string(data.temperature) + "\n";
		str += strTabs + "Pressure: " + std::to_string(data.pressure) + "\n";
		str += strTabs + "RPM: " + std::to_string(data.rpm) + "\n";
		str += strTabs + "fuel: " + std::to_string(data.fuel) + "\n";

		switch (data.deviceStatus)
		{
		case DeviceStatus::NORMAL:
			str += strTabs + "Status: NORMAL\n\n";
			break;
		case DeviceStatus::WARNING:
			str += strTabs + "Status: WARNING\n\n";
			break;
		case DeviceStatus::FAIL:
			str += strTabs + "Status: FAIL\n\n";
			break;
		default:
			str += strTabs + "Status: UNKNOWN\n\n";
			break;
		}
	}

	std::cout << str;
}

void NewProcess()
{
	TelemetryValidator telemetryValidator;
	TelemetryProcessor telemetryProcessor;
	DeviceRegistry deviceRegistry;
	AlertManager alertManager;
	StatusEvaluator statusEvaluator;

	TelemetryMessageQueue tmq;
	std::thread messageProducerThread([&tmq]()
		{
			std::vector<TelemetryMessage> telemetryMessages = GenerateReadings(10);

			//test invalid
			telemetryMessages.at(1).fuel = 522;
			telemetryMessages.at(2).temperature = NAN;
			for (auto& message : telemetryMessages)
				tmq.Push(message);
		});

	bool loop = true;
	while (loop)
	{
		TelemetryMessage telemetryMessage;
		tmq.WaitAndPop(telemetryMessage);

		//Turn message into data
		TelemetryData telemetryData;
		telemetryData.deviceID = telemetryMessage.deviceID;
		telemetryData.temperature = telemetryMessage.temperature;
		telemetryData.pressure = telemetryMessage.pressure;
		telemetryData.rpm = telemetryMessage.rpm;
		telemetryData.fuel = telemetryMessage.fuel;
		telemetryData.deviceStatus = UNKNOWN;

		//Validate telemetry
		bool valid = telemetryValidator.ValidateTelemetry(telemetryData);
		if (!valid)
		{
			//do something with logging
			continue;
		}

		//Evaluate status
		statusEvaluator.EvaluateReading(telemetryData);

		//Handle alerts
		alertManager.ProcessReading(telemetryData);

		//Add or update telemetry to registry
		deviceRegistry.UpdateDevice(telemetryData);

		//Show telemetry from devices
		std::system("cls");
		std::cout << "Display\n";
		DisplayTelemetryDataToConsole(deviceRegistry.GetAllDevices(), 1);
		
		//sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void OldProcess()
{
	TelemetryValidator telemetryValidator;
	TelemetryProcessor telemetryProcessor;
	DeviceRegistry deviceRegistry;
	AlertManager alertManager;
	StatusEvaluator statusEvaluator;

	bool loop = true;
	while (loop)
	{
		std::system("cls");

		std::vector<TelemetryMessage> telemetryMessages = GenerateReadings(10);

		//test invalid
		telemetryMessages.at(1).fuel = 522;
		telemetryMessages.at(2).temperature = NAN;
		
		//TODO: message handling, turn message into data
		std::vector<TelemetryData> telemetryData;
		for (const auto& message : telemetryMessages)
		{
			TelemetryData data;
			data.deviceID = message.deviceID;
			data.temperature = message.temperature;
			data.pressure = message.pressure;
			data.rpm = message.rpm;
			data.fuel = message.fuel;
			data.deviceStatus = UNKNOWN;
			telemetryData.push_back(data);
		}

		//Validate telemetry
		std::vector<TelemetryData> validTelemetry;
		std::vector<TelemetryData> invalidTelemetry;
		for (const auto& data : telemetryData)
		{
			bool valid = telemetryValidator.ValidateTelemetry(data);
			if (valid)
				validTelemetry.push_back(data);
			else
				invalidTelemetry.push_back(data);
		}

		//Evaluate status
		for (auto& data : validTelemetry)
			statusEvaluator.EvaluateReading(data);

		//Handle alerts
		for (const auto& data : validTelemetry)
			alertManager.ProcessReading(data);

		//Add or update telemetry to registry
		for (const auto& data : validTelemetry)
			deviceRegistry.UpdateDevice(data);

		//Show telemetry for testing
		std::cout << "Valid telemetry\n";
		DisplayTelemetryDataToConsole(validTelemetry, 1);
		std::cout << "Invalid telemetry\n";
		DisplayTelemetryDataToConsole(invalidTelemetry, 1);

		//Process telemetry that just came in
		double averageTemperature = telemetryProcessor.AverageTemperature(validTelemetry);
		double averagePressure = telemetryProcessor.AveragePressure(validTelemetry);
		double averageRpm = telemetryProcessor.AverageRpm(validTelemetry);
		double averageFuel = telemetryProcessor.AverageFuel(validTelemetry);
		std::cout << "Average Temperature: " << averageTemperature << "\n";
		std::cout << "Average Pressure: " << averagePressure << "\n";
		std::cout << "Average RPM: " << averageRpm << "\n";
		std::cout << "Average Fuel: " << averageFuel << "\n";

		TelemetryData minTempDevice = telemetryProcessor.MinimumTemperature(validTelemetry);
		std::cout << "Minimun Temperature: " << minTempDevice.deviceID << " " << minTempDevice.temperature << "\n";
		TelemetryData maxTempDevice = telemetryProcessor.MaxTemperature(validTelemetry);
		std::cout << "Max Temperature: " << maxTempDevice.deviceID << " " << maxTempDevice.temperature << "\n";

		//get all devices
		std::vector<TelemetryData> allDevices = deviceRegistry.GetAllDevices();
		std::cout << "Display for GetAllDevices call from device registry\n";
		DisplayTelemetryDataToConsole(allDevices, 1);

		//sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));

		loop = false;
	}
}

int main()
{
	//OldProcess();
	NewProcess();
	return 0;
}
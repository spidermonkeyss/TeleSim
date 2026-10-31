#include <iostream>
#include <thread>
#include <chrono>

#include "../sensorsim/sim.h"
#include "../res/TelemetryValidator.h"
#include "../res/TelemetryProcessor.h"
#include "../res/TelemetryData.h"

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
		str += strTabs + "Status: " + message.messageDeviceStatus + "\n\n";
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

int main()
{
	TelemetryValidator telemetryValidator;
	TelemetryProcessor telemetryProcessor;
	
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
			
			if(message.messageDeviceStatus == "NORMAL")
				data.deviceStatus = NORMAL;
			if (message.messageDeviceStatus == "WARNING")
				data.deviceStatus = WARNING;
			if (message.messageDeviceStatus == "FAIL")
				data.deviceStatus = FAIL;

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

		std::cout << "Valid telemetry\n";
		DisplayTelemetryDataToConsole(validTelemetry, 1);
		std::cout << "Invalid telemetry\n";
		DisplayTelemetryDataToConsole(invalidTelemetry, 1);



		//Process telemetry
		double averageTemperature = telemetryProcessor.AverageTemperature(validTelemetry);
		double averagePressure = telemetryProcessor.AveragePressure(validTelemetry);
		double averageRpm = telemetryProcessor.AverageRpm(validTelemetry);
		double averageFuel = telemetryProcessor.AverageFuel(validTelemetry);
		std::cout << "Average Temperature: " << averageTemperature << "\n";
		std::cout << "Average Pressure: " << averagePressure << "\n";
		std::cout << "Average RPM: " << averageRpm << "\n";
		std::cout << "Average Fuel: " << averageFuel << "\n";

		//sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));

		//loop = false;
	}

	return 0;
}
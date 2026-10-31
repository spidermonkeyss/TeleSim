#include <iostream>
#include <thread>
#include <chrono>

#include "../sensorsim/sim.h"
#include "../res/TelemetryValidator.h"

void DisplayTelemetryMessagesToConsole(std::vector<TelemetryMessage> messages)
{

	for (const auto& message : messages)
	{
		std::cout << "DeviceID: " << message.deviceID;
		std::cout << "\nTemp: " << message.temperature;
		std::cout << "\nPressure: " << message.pressure;
		std::cout << "\nRPM: " << message.rpm;
		std::cout << "\nfuel: " << message.fuel;
		switch (message.deviceStatus)
		{
		case DeviceStatus::NORMAL:
			std::cout << "\nStatus: NORMAL\n\n";
			break;
		case DeviceStatus::WARNING:
			std::cout << "\nStatus: WARNING\n\n";
			break;
		case DeviceStatus::FAIL:
			std::cout << "\nStatus: FAIL\n\n";
			break;
		default:
			std::cout << "\nStatus: UNKNOWN\n\n";
			break;
		}
	}
}

int main()
{
	TelemetryValidator telemetryValidator;
	
	bool loop = true;
	while (loop)
	{
		std::system("cls");

		std::vector<TelemetryMessage> telemetryMessages = GenerateReadings(10);
		
		//test invalid
		telemetryMessages.at(1).fuel = 522;

		//DisplayTelemetryMessagesToConsole(telemetryMessages);

		std::vector<TelemetryMessage> validTelemetry;
		std::vector<TelemetryMessage> invalidTelemetry;
		for (const auto& message : telemetryMessages)
		{
			bool valid = telemetryValidator.ValidateTelemetry(message);
			if (valid)
				validTelemetry.push_back(message);
			else
				invalidTelemetry.push_back(message);
		}

		std::cout << "Valid telemetry\n";
		DisplayTelemetryMessagesToConsole(validTelemetry);
		std::cout << "Invalid telemetry\n";
		DisplayTelemetryMessagesToConsole(invalidTelemetry);

		//sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
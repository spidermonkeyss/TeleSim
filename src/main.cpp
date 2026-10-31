#include <iostream>
#include <thread>
#include <chrono>

#include "../sensorsim/sim.h"
#include "../res/TelemetryValidator.h"
#include "../res/TelemetryProcessor.h"

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

		switch (message.deviceStatus)
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

		std::vector<TelemetryMessage> validTelemetry;
		std::vector<TelemetryMessage> invalidTelemetry;

		//Scoop the inital readings so the vector isnt used after validation. Should be using the validTelemetry vector afterwards
		{
			std::vector<TelemetryMessage> telemetryMessages = GenerateReadings(10);
		
			//test invalid
			telemetryMessages.at(1).fuel = 522;
			telemetryMessages.at(2).temperature = NAN;


			//Validate telemetry
			for (const auto& message : telemetryMessages)
			{
				bool valid = telemetryValidator.ValidateTelemetry(message);
				if (valid)
					validTelemetry.push_back(message);
				else
					invalidTelemetry.push_back(message);
			}
		}

		std::cout << "Valid telemetry\n";
		DisplayTelemetryMessagesToConsole(validTelemetry, 1);
		std::cout << "Invalid telemetry\n";
		DisplayTelemetryMessagesToConsole(invalidTelemetry, 1);



		//Process telemetry
		double averageTemperature = telemetryProcessor.AverageTemperature(validTelemetry);
		std::cout << "Average Temperature: " << averageTemperature << "\n";




		//sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));

		loop = false;
	}

	return 0;
}
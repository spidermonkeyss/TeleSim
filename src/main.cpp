#include <iostream>
#include <thread>
#include <chrono>

#include "../sensorsim/sim.h"

int main()
{
	bool loop = true;
	while (loop)
	{
		std::vector<TelemetryMessage> telemetryMessages = GenerateReadings(4);

		for (const auto& message : telemetryMessages)
		{
			std::cout << "DeviceID: " << message.deviceID;
			std::cout << "\nTemp: " << message.temperature;
			std::cout << "\nPressure: " << message.pressure;
			std::cout << "\nRPM: " << message.rpm;
			std::cout << "\nfuel: " << message.fuel;
			switch (message.deviceStatus)
			{
			case 0:
				std::cout << "\nStatus: NORAML\n\n";
				break;
			case 1:
				std::cout << "\nStatus: WARNING\n\n";
				break;
			case 2:
				std::cout << "\nStatus: FAIL\n\n";
				break;
			default:
				std::cout << "\nStatus: UNKNOWN\n\n";
				break;
			}
		}

		//sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::system("cls");
	}

	return 0;
}
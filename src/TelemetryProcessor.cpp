#include "../res/TelemetryProcessor.h"

double TelemetryProcessor::AverageTemperature(const std::vector<TelemetryMessage>& telemetryMessages)
{
	double sum = 0;
	for (const auto& message : telemetryMessages)
		sum += message.temperature;

	return sum / (double)telemetryMessages.size();
}

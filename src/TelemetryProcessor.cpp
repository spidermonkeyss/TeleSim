#include "../res/TelemetryProcessor.h"

double TelemetryProcessor::AverageTemperature(const std::vector<TelemetryData>& telemetryData)
{
	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.temperature;

	return sum / (double)telemetryData.size();
}

double TelemetryProcessor::AveragePressure(const std::vector<TelemetryData>& telemetryData)
{
	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.pressure;

	return sum / (double)telemetryData.size();
}

double TelemetryProcessor::AverageRpm(const std::vector<TelemetryData>& telemetryData)
{
	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.rpm;

	return sum / (double)telemetryData.size();
}

double TelemetryProcessor::AverageFuel(const std::vector<TelemetryData>& telemetryData)
{
	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.fuel;

	return sum / (double)telemetryData.size();
}

double TelemetryProcessor::MinimumTemperature(const std::vector<TelemetryData>& telemetryData)
{
	//double min = telemetryData.at(0).temperature;
	return 0;
}

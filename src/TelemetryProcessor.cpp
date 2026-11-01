#include "../res/TelemetryProcessor.h"

double TelemetryProcessor::AverageTemperature(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return 0;

	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.temperature;

	return sum / (double)telemetryData.size();
}

double TelemetryProcessor::AveragePressure(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return 0;

	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.pressure;

	return sum / (double)telemetryData.size();
}

double TelemetryProcessor::AverageRpm(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return 0;

	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.rpm;

	return sum / (double)telemetryData.size();
}

double TelemetryProcessor::AverageFuel(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return 0;

	double sum = 0;
	for (const auto& data : telemetryData)
		sum += data.fuel;

	return sum / (double)telemetryData.size();
}

TelemetryData TelemetryProcessor::MinimumTemperature(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int minIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).temperature < telemetryData.at(minIndex).temperature)
			minIndex = i;
	}
	
	return telemetryData[minIndex];
}

TelemetryData TelemetryProcessor::MinimumPressure(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int minIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).pressure < telemetryData.at(minIndex).pressure)
			minIndex = i;
	}

	return telemetryData[minIndex];
}

TelemetryData TelemetryProcessor::MinimumRpm(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int minIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).rpm < telemetryData.at(minIndex).rpm)
			minIndex = i;
	}

	return telemetryData[minIndex];
}

TelemetryData TelemetryProcessor::MinimumFuel(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int minIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).fuel < telemetryData.at(minIndex).fuel)
			minIndex = i;
	}

	return telemetryData[minIndex];
}

TelemetryData TelemetryProcessor::MaxTemperature(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int maxIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).temperature > telemetryData.at(maxIndex).temperature)
			maxIndex = i;
	}

	return telemetryData[maxIndex];
}

TelemetryData TelemetryProcessor::MaxPressure(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int maxIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).pressure > telemetryData.at(maxIndex).pressure)
			maxIndex = i;
	}

	return telemetryData[maxIndex];
}

TelemetryData TelemetryProcessor::MaxRpm(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int maxIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).rpm > telemetryData.at(maxIndex).rpm)
			maxIndex = i;
	}

	return telemetryData[maxIndex];
}

TelemetryData TelemetryProcessor::MaxFuel(const std::vector<TelemetryData>& telemetryData)
{
	if (telemetryData.empty())
		return TelemetryData();

	int maxIndex = 0;
	for (int i = 1; i < telemetryData.size(); i++)
	{
		if (telemetryData.at(i).fuel > telemetryData.at(maxIndex).fuel)
			maxIndex = i;
	}

	return telemetryData[maxIndex];
}
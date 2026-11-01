#include "pch.h"

#include "../res/TelemetryProcessor.h"

TEST(TelemetryProcessorTests, AverageTests)
{
	TelemetryProcessor telemetryProcessor;

	std::vector<TelemetryData> telemetryData(5);
	telemetryData[0].temperature = 80;
	telemetryData[1].temperature = 90;
	telemetryData[2].temperature = 100;
	telemetryData[3].temperature = 70;
	telemetryData[4].temperature = 60;

	EXPECT_EQ(telemetryProcessor.AverageTemperature(telemetryData), (double)80);
	//EXPECT_TRUE(true);
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
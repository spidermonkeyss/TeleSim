#include "pch.h"
#include"../res/AlertManager.h"

TEST(AlertManagerTests, HasAlertTest)
{
	AlertManager alertManager;

	EXPECT_FALSE(alertManager.HasAlert(""));

	TelemetryData data;
	data.deviceID = "testID";
	data.temperature = 100;
	data.pressure = 100;
	data.rpm = 100;
	data.fuel = 100;
	data.deviceStatus = NORMAL;

	//no alert
	alertManager.ProcessReading(data);
	EXPECT_FALSE(alertManager.HasAlert("testID"));

	//first warning alert
	data.deviceStatus = WARNING;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//stays warning
	data.deviceStatus = WARNING;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//elavate to fail;
	data.deviceStatus = FAIL;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//down to warning
	data.deviceStatus = WARNING;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//resolve from warning
	data.deviceStatus = NORMAL;
	alertManager.ProcessReading(data);
	EXPECT_FALSE(alertManager.HasAlert("testID"));

	//elvate to fail from noraml
	data.deviceStatus = FAIL;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//resolve from fail
	data.deviceStatus = NORMAL;
	alertManager.ProcessReading(data);
	EXPECT_FALSE(alertManager.HasAlert("testID"));
}

TEST(AlertManagerTests, GetAlertTest)
{
	AlertManager alertManager;

	//no alert
	auto alert = alertManager.GetAlert("");
	EXPECT_FALSE(alert.has_value());

	TelemetryData data;
	data.deviceID = "testID";
	data.temperature = 100;
	data.pressure = 100;
	data.rpm = 100;
	data.fuel = 100;
	data.deviceStatus = NORMAL;

	alertManager.ProcessReading(data);

	//no alert
	alert = alertManager.GetAlert("testID");
	EXPECT_FALSE(alert.has_value());

	//warning
	data.deviceStatus = WARNING;
	alertManager.ProcessReading(data);
	alert = alertManager.GetAlert("testID");
	if (alert.has_value())
		EXPECT_TRUE(alert->deviceStatus == WARNING);
	else
		EXPECT_TRUE(alert.has_value());

	//fail
	data.deviceStatus = FAIL;
	alertManager.ProcessReading(data);
	alert = alertManager.GetAlert("testID");
	if (alert.has_value())
		EXPECT_TRUE(alert->deviceStatus == FAIL);
	else
		EXPECT_TRUE(alert.has_value());
}

TEST(AlertManagerTests, ProcessReadingTest)
{
	AlertManager alertManager;

	EXPECT_FALSE(alertManager.HasAlert(""));

	TelemetryData data;
	data.deviceID = "testID";
	data.temperature = 100;
	data.pressure = 100;
	data.rpm = 100;
	data.fuel = 100;
	data.deviceStatus = NORMAL;

	//no alert
	alertManager.ProcessReading(data);
	EXPECT_FALSE(alertManager.HasAlert("testID"));

	//first warning alert
	data.deviceStatus = WARNING;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//stays warning
	data.deviceStatus = WARNING;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//elavate to fail;
	data.deviceStatus = FAIL;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//down to warning
	data.deviceStatus = WARNING;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//resolve from warning
	data.deviceStatus = NORMAL;
	alertManager.ProcessReading(data);
	EXPECT_FALSE(alertManager.HasAlert("testID"));

	//elvate to fail from noraml
	data.deviceStatus = FAIL;
	alertManager.ProcessReading(data);
	EXPECT_TRUE(alertManager.HasAlert("testID"));

	//resolve from fail
	data.deviceStatus = NORMAL;
	alertManager.ProcessReading(data);
	EXPECT_FALSE(alertManager.HasAlert("testID"));
}
#include "pch.h"
#include "../res/TelemetryValidator.h"

TEST(TelemetryValidatorTests, ValidateTelemetryTest)
{
    TelemetryValidator telemetryValidator;

    TelemetryData validData;
    validData.deviceID = "ENGINE01";
    validData.temperature = 190;
    validData.pressure = 100;
    validData.rpm = 2500;
    validData.fuel = 45;
    bool valid = telemetryValidator.ValidateTelemetry(validData);
    EXPECT_TRUE(valid);
}

TEST(TelemetryValidatorTests, ValidateTelemetryNANTest)
{
    TelemetryValidator telemetryValidator;

    TelemetryData invalidData;
    invalidData.deviceID = "ENGINE01";
    invalidData.temperature = NAN;
    invalidData.pressure = 100;
    invalidData.rpm = 2500;
    invalidData.fuel = 45;
    bool invalid = telemetryValidator.ValidateTelemetry(invalidData);
    EXPECT_FALSE(invalid);
}

TEST(TelemetryValidatorTests, ValidateTelemetryDeviceIDTest)
{
    TelemetryValidator telemetryValidator;

    TelemetryData invalidData;
    invalidData.deviceID = "";
    invalidData.temperature = 190;
    invalidData.pressure = 100;
    invalidData.rpm = 2500;
    invalidData.fuel = 45;
    bool isInvalid = telemetryValidator.ValidateTelemetry(invalidData);
    EXPECT_FALSE(isInvalid);
}

TEST(TelemetryValidatorTests, ValidateTelemetryTemperatureTest)
{
    TelemetryValidator telemetryValidator;

    TelemetryData invalidData;
    invalidData.deviceID = "ENGINE01";
    invalidData.temperature = -50;
    invalidData.pressure = 100;
    invalidData.rpm = 2500;
    invalidData.fuel = 45;
    bool isInvalid = telemetryValidator.ValidateTelemetry(invalidData);
    EXPECT_FALSE(isInvalid);
}

TEST(TelemetryValidatorTests, ValidateTelemetryPressureTest)
{
    TelemetryValidator telemetryValidator;

    TelemetryData invalidData;
    invalidData.deviceID = "ENGINE01";
    invalidData.temperature = 190;
    invalidData.pressure = 200;
    invalidData.rpm = 2500;
    invalidData.fuel = 45;
    bool invalid = telemetryValidator.ValidateTelemetry(invalidData);
    EXPECT_FALSE(invalid);
}

TEST(TelemetryValidatorTests, ValidateTelemetryRpmTest)
{
    TelemetryValidator telemetryValidator;

    TelemetryData invalidData;
    invalidData.deviceID = "ENGINE01";
    invalidData.temperature = 190;
    invalidData.pressure = 100;
    invalidData.rpm = 6500;
    invalidData.fuel = 45;
    bool invalid = telemetryValidator.ValidateTelemetry(invalidData);
    EXPECT_FALSE(invalid);
}

TEST(TelemetryValidatorTests, ValidateTelemetryFuelTest)
{
    TelemetryValidator telemetryValidator;

    TelemetryData invalidData;
    invalidData.deviceID = "ENGINE01";
    invalidData.temperature = 190;
    invalidData.pressure = 100;
    invalidData.rpm = 2500;
    invalidData.fuel = 55;
    bool invalid = telemetryValidator.ValidateTelemetry(invalidData);
    EXPECT_FALSE(invalid);
}
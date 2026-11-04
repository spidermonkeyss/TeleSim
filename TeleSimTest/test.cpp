#include "pch.h"
#include "../res/TelemetryProcessor.h"
#include "../res/TelemetryValidator.h"

TEST(TelemetryProcessorTests, AverageTemperatureTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].temperature = 80;
    telemetryData[1].temperature = 90;
    telemetryData[2].temperature = 100;

    EXPECT_DOUBLE_EQ(telemetryProcessor.AverageTemperature(telemetryData), 90.0);

    telemetryData.clear();
    EXPECT_DOUBLE_EQ(telemetryProcessor.AverageTemperature(telemetryData), 0.0);
}

TEST(TelemetryProcessorTests, AveragePressureTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].pressure = 30;
    telemetryData[1].pressure = 60;
    telemetryData[2].pressure = 90;

    EXPECT_DOUBLE_EQ(telemetryProcessor.AveragePressure(telemetryData), 60.0);

    telemetryData.clear();
    EXPECT_DOUBLE_EQ(telemetryProcessor.AveragePressure(telemetryData), 0.0);
}

TEST(TelemetryProcessorTests, AverageRpmTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].rpm = 1000;
    telemetryData[1].rpm = 2000;
    telemetryData[2].rpm = 3000;

    EXPECT_DOUBLE_EQ(telemetryProcessor.AverageRpm(telemetryData), 2000.0);

    telemetryData.clear();
    EXPECT_DOUBLE_EQ(telemetryProcessor.AverageRpm(telemetryData), 0.0);
}

TEST(TelemetryProcessorTests, AverageFuelTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].fuel = 10;
    telemetryData[1].fuel = 20;
    telemetryData[2].fuel = 30;

    EXPECT_DOUBLE_EQ(telemetryProcessor.AverageFuel(telemetryData), 20.0);

    telemetryData.clear();
    EXPECT_DOUBLE_EQ(telemetryProcessor.AverageFuel(telemetryData), 0.0);
}

TEST(TelemetryProcessorTests, MinimumTemperatureTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].temperature = 80;
    telemetryData[1].temperature = 50;
    telemetryData[2].temperature = 90;
    telemetryData[1].deviceID = "ENGINE_002";

    EXPECT_EQ(telemetryProcessor.MinimumTemperature(telemetryData).deviceID, "ENGINE_002");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MinimumTemperature(telemetryData).temperature, 50.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MinimumTemperature(telemetryData).deviceID.empty());
}

TEST(TelemetryProcessorTests, MinimumPressureTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].pressure = 70;
    telemetryData[1].pressure = 90;
    telemetryData[2].pressure = 20;
    telemetryData[2].deviceID = "ENGINE_003";

    EXPECT_EQ(telemetryProcessor.MinimumPressure(telemetryData).deviceID, "ENGINE_003");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MinimumPressure(telemetryData).pressure, 20.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MinimumPressure(telemetryData).deviceID.empty());
}

TEST(TelemetryProcessorTests, MinimumRpmTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].rpm = 1500;
    telemetryData[1].rpm = 500;
    telemetryData[2].rpm = 2500;
    telemetryData[1].deviceID = "ENGINE_002";

    EXPECT_EQ(telemetryProcessor.MinimumRpm(telemetryData).deviceID, "ENGINE_002");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MinimumRpm(telemetryData).rpm, 500.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MinimumRpm(telemetryData).deviceID.empty());
}

TEST(TelemetryProcessorTests, MinimumFuelTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].fuel = 30;
    telemetryData[1].fuel = 15;
    telemetryData[2].fuel = 40;
    telemetryData[1].deviceID = "ENGINE_002";

    EXPECT_EQ(telemetryProcessor.MinimumFuel(telemetryData).deviceID, "ENGINE_002");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MinimumFuel(telemetryData).fuel, 15.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MinimumFuel(telemetryData).deviceID.empty());
}

TEST(TelemetryProcessorTests, MaxTemperatureTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].temperature = 80;
    telemetryData[1].temperature = 120;
    telemetryData[2].temperature = 90;
    telemetryData[1].deviceID = "ENGINE_002";

    EXPECT_EQ(telemetryProcessor.MaxTemperature(telemetryData).deviceID, "ENGINE_002");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MaxTemperature(telemetryData).temperature, 120.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MaxTemperature(telemetryData).deviceID.empty());
}

TEST(TelemetryProcessorTests, MaxPressureTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].pressure = 50;
    telemetryData[1].pressure = 75;
    telemetryData[2].pressure = 100;
    telemetryData[2].deviceID = "ENGINE_003";

    EXPECT_EQ(telemetryProcessor.MaxPressure(telemetryData).deviceID, "ENGINE_003");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MaxPressure(telemetryData).pressure, 100.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MaxPressure(telemetryData).deviceID.empty());
}

TEST(TelemetryProcessorTests, MaxRpmTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].rpm = 1000;
    telemetryData[1].rpm = 4000;
    telemetryData[2].rpm = 2500;
    telemetryData[1].deviceID = "ENGINE_002";

    EXPECT_EQ(telemetryProcessor.MaxRpm(telemetryData).deviceID, "ENGINE_002");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MaxRpm(telemetryData).rpm, 4000.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MaxRpm(telemetryData).deviceID.empty());
}

TEST(TelemetryProcessorTests, MaxFuelTest)
{
    TelemetryProcessor telemetryProcessor;
    std::vector<TelemetryData> telemetryData(3);
    telemetryData[0].fuel = 10;
    telemetryData[1].fuel = 20;
    telemetryData[2].fuel = 45;
    telemetryData[2].deviceID = "ENGINE_003";

    EXPECT_EQ(telemetryProcessor.MaxFuel(telemetryData).deviceID, "ENGINE_003");
    EXPECT_DOUBLE_EQ(telemetryProcessor.MaxFuel(telemetryData).fuel, 45.0);

    telemetryData.clear();
    EXPECT_TRUE(telemetryProcessor.MaxFuel(telemetryData).deviceID.empty());
}

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

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

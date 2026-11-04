#include "pch.h"

#include "../res/DeviceRegistry.h"

TEST(DeviceRegistryTests, HasDeviceTest)
{
    DeviceRegistry deviceRegistry;

    //empty registry
    EXPECT_FALSE(deviceRegistry.HasDevice(""));

    //normal usage
    TelemetryData data;
    data.deviceID = "testID";
    data.temperature = 100;
    data.pressure = 100;
    data.rpm = 100;
    data.fuel = 100;
    data.deviceStatus = NORMAL;
    deviceRegistry.UpdateDevice(data);
    EXPECT_TRUE(deviceRegistry.HasDevice(data));
    EXPECT_TRUE(deviceRegistry.HasDevice(data.deviceID));

    //wrong id
    EXPECT_FALSE(deviceRegistry.HasDevice("testttID"));
}

TEST(DeviceRegistryTests, UpdateDeviceTest)
{
    DeviceRegistry deviceRegistry;

    //add to empty
    TelemetryData data;
    data.deviceID = "testID";
    data.temperature = 100;
    data.pressure = 100;
    data.rpm = 100;
    data.fuel = 100;
    data.deviceStatus = NORMAL;
    deviceRegistry.UpdateDevice(data);

    //update same device
    data.fuel = 90;
    deviceRegistry.UpdateDevice(data);
}

TEST(DeviceRegistryTests, GetDeviceTest)
{
    DeviceRegistry deviceRegistry;

    TelemetryData data;
    data.deviceID = "testID";
    data.temperature = 100;
    data.pressure = 100;
    data.rpm = 100;
    data.fuel = 100;
    data.deviceStatus = NORMAL;

    //empty registry
    auto device1 = deviceRegistry.GetDevice("testID");
    EXPECT_TRUE(device1 == std::nullopt);

    //empty string
    deviceRegistry.UpdateDevice(data);
    auto device2 = deviceRegistry.GetDevice("");
    EXPECT_TRUE(device2 == std::nullopt);

    //has device
    auto device3 = deviceRegistry.GetDevice("testID");
    EXPECT_TRUE(device3 != std::nullopt);

    //doesnt have device
    auto device4 = deviceRegistry.GetDevice("testttttID");
    EXPECT_TRUE(device4 == std::nullopt);
}
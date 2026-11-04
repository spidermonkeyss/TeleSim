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

    auto device = deviceRegistry.GetDevice(data.deviceID);

    //got a device
    ASSERT_TRUE(device.has_value());

    //check device count is 1
    EXPECT_EQ(deviceRegistry.DeviceCount(), 1);

    //check fuel is correct
    EXPECT_DOUBLE_EQ(device->fuel, 90);
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

TEST(DeviceRegistryTests, GetAllDevicesTest)
{
    DeviceRegistry deviceRegistry;

    TelemetryData data1;
    data1.deviceID = "testID1";
    data1.temperature = 100;
    data1.pressure = 100;
    data1.rpm = 100;
    data1.fuel = 100;
    data1.deviceStatus = NORMAL;

    TelemetryData data2;
    data2.deviceID = "testID2";
    data2.temperature = 100;
    data2.pressure = 100;
    data2.rpm = 100;
    data2.fuel = 100;
    data2.deviceStatus = NORMAL;

    //empty registry
    std::vector<TelemetryData> data = deviceRegistry.GetAllDevices();
    EXPECT_EQ(data.size(), 0);

    //one device
    deviceRegistry.UpdateDevice(data1);
    data = deviceRegistry.GetAllDevices();
    EXPECT_EQ(data.size(), 1);
    EXPECT_TRUE(data.at(0).deviceID == "testID1");

    //two devices
    deviceRegistry.UpdateDevice(data2);
    data = deviceRegistry.GetAllDevices();
    EXPECT_EQ(data.size(), 2);
}

TEST(DeviceRegistryTests, ClearDevicesTest)
{
    DeviceRegistry deviceRegistry;

    TelemetryData data1;
    data1.deviceID = "testID1";
    data1.temperature = 100;
    data1.pressure = 100;
    data1.rpm = 100;
    data1.fuel = 100;
    data1.deviceStatus = NORMAL;

    TelemetryData data2;
    data2.deviceID = "testID2";
    data2.temperature = 100;
    data2.pressure = 100;
    data2.rpm = 100;
    data2.fuel = 100;
    data2.deviceStatus = NORMAL;

    deviceRegistry.UpdateDevice(data1);
    deviceRegistry.UpdateDevice(data2);

    EXPECT_TRUE(deviceRegistry.DeviceCount() == 2);

    deviceRegistry.ClearDevices();

    EXPECT_TRUE(deviceRegistry.DeviceCount() == 0);
}

TEST(DeviceRegistryTests, DeleteDeviceTests)
{
    DeviceRegistry deviceRegistry;

    TelemetryData data1;
    data1.deviceID = "testID1";
    data1.temperature = 100;
    data1.pressure = 100;
    data1.rpm = 100;
    data1.fuel = 100;
    data1.deviceStatus = NORMAL;

    TelemetryData data2;
    data2.deviceID = "testID2";
    data2.temperature = 100;
    data2.pressure = 100;
    data2.rpm = 100;
    data2.fuel = 100;
    data2.deviceStatus = NORMAL;

    deviceRegistry.UpdateDevice(data1);
    deviceRegistry.UpdateDevice(data2);

    deviceRegistry.DeleteDevice(data1);
    EXPECT_TRUE(deviceRegistry.DeviceCount() == 1);
    EXPECT_FALSE(deviceRegistry.HasDevice(data1));
    EXPECT_TRUE(deviceRegistry.HasDevice(data2));

    deviceRegistry.DeleteDevice(data2);
    EXPECT_TRUE(deviceRegistry.DeviceCount() == 0);
    EXPECT_FALSE(deviceRegistry.HasDevice(data1));
    EXPECT_FALSE(deviceRegistry.HasDevice(data2));
}

TEST(DeviceRegistryTests, DeviceCountTests)
{
    DeviceRegistry deviceRegistry;

    TelemetryData data1;
    data1.deviceID = "testID1";
    data1.temperature = 100;
    data1.pressure = 100;
    data1.rpm = 100;
    data1.fuel = 100;
    data1.deviceStatus = NORMAL;

    TelemetryData data2;
    data2.deviceID = "testID2";
    data2.temperature = 100;
    data2.pressure = 100;
    data2.rpm = 100;
    data2.fuel = 100;
    data2.deviceStatus = NORMAL;

    deviceRegistry.UpdateDevice(data1);
    EXPECT_TRUE(deviceRegistry.DeviceCount() == 1);
    
    deviceRegistry.UpdateDevice(data2);
    EXPECT_TRUE(deviceRegistry.DeviceCount() == 2);
}
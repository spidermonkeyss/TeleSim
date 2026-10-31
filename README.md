# TeleSim

A C++ telemetry simulator that generates randomized engine sensor readings for multiple devices and displays them in a continuously running console application.

## Current Features

- Simulates telemetry for multiple engine devices.
- Generates randomized temperature, pressure, RPM, and fuel readings.
- Assigns device status classifications.
- Updates sensor readings every second.
- Automatic device status classification based on sensor thresholds.

## Technologies

- C++
- Visual Studio 2022
- C++ Standard Library (`<random>`, `<vector>`, `<thread>`, `<chrono>`)

## Planned Features

- Additional simulated sensors and devices.
- Telemetry data validation and processing.
- Multithreaded data generation and processing.
- Telemetry logging and unit testing.
## Tracer System Implementation

## Objective

Designing an embedded/IoT product for real-time tracking using components like ESP32, STM8, UBLOX NEO-6M V2 GPS Module, and LoRaWAN module.

## Components Used
- ESP32 microcontrollers
- STM8 microcontroller
- UBLOX NEO-6M V2 GPS Module
- LoRaWAN module
- GSM module
- camera module (future)

## Abstraction
The Tracer device utilizes ESP32 microcontroller and UBLOX NEO-6M V2 GPS Module for real-time tracking. And controlling with sensor, auto-switches and camera . Communication between GPS and ESP32 is achieved via UART protocol. GPS coordinates can be converted into a map location using mapping APIs like Google Maps, OpenStreetMap, or Mapbox.

## Communication without Internet
For communication without internet, consider Bluetooth or LoRa. Bluetooth Low Energy (BLE) connects to nearby devices, while LoRa enables long-range communication without internet dependency.

Network Connection Options
1. **Local Wi-Fi Network:** Connect ESP32 to a local Wi-Fi network for communication.
2. **Ad-Hoc Wi-Fi Network:** Create a direct Wi-Fi connection between devices.
3. **Offline Map Data:** Pre-load map data onto devices for offline map viewing.

## Range Limit of Offline Map Data
There's no inherent range limit, but it depends on device storage capacity, map resolution, compression, and updates.

## Mapbox and LoRaWAN
Mapbox offers mapping tools, while LoRaWAN facilitates long-range IoT communication. They can be used together for real-time tracking and visualization.

## Methodologies
Utilize Arduino framework in platform-io for development. In future Security configurations include WPA3, PMF for Wi-Fi.

## Monitoring Unit
Installed in remote areas for real-time monitoring and vehicle control, Wi-Fi configured for data transfer to web/mobile apps.

## Moving Unit
Installed in vehicles to transmit encrypted sensor data to the monitoring unit for processing.

## Map JavaScript APIs
Refer to Google Maps JavaScript API documentation for map integration.

## Implementation
Refer to the provided links for integrating map APIs and implementing the Tracer system.
## README Summary
- Objective: Real-time tracking and controlling device.
- Components: ESP32, GPS Module, LoRaWAN.
- Communication: UART, Bluetooth, LoRa.
- **Network:** Local Wi-Fi, Ad-Hoc Wi-Fi, Offline Maps.
- **Map Integration:** Google Maps API, Mapbox.
- **Methodologies:** ESP-IDF, Security Configurations.
- **Units:** Monitoring Unit, Moving Unit.




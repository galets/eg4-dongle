# EG4 Dongle Programming

Goal of this repository is to summarize the knowledge and techniques for re-programming EG4 dongles used in inverters such that they are useful with Home Assistant.

Original source of information is in [this thread](https://diysolarforum.com/threads/eg4-wifi-ethernet-dongle-installing-esphome.119275/).

## Overview

This project focuses on reflashing the stock EG4 WiFi and Ethernet dongles with custom firmware to enable local, high-frequency monitoring and control of solar inverters. By replacing the proprietary factory firmware, users can bypass cloud dependencies and integrate their hardware directly into their local smart home ecosystems.

## What is being done

The community has successfully identified the hardware architecture of the EG4 dongles and developed a method to flash them with **ESPHome**.

* **Hardware Access:** Using a female HDMI breakout board and a standard ESP32 programmer, users can interface with the dongle's
  internal pins via the HDMI connector.
* **Firmware Backup:** The stock firmware is backed up using `esptool` to preserve the unique serial numbers and PINs required for factory cloud services.
* **Reflashing:** The dongles are flashed with a custom ESPHome YAML configuration that enables Ethernet/WiFi connectivity and Modbus RTU communication with the inverter.

## Why it is done

The primary motivations for this modification include:

* **Local Control:** Removing the dependency on the EG4 Web Monitor cloud service. This ensures that monitoring and control remain functional even if the internet connection is lost.
* **Faster Data Updates:** The stock cloud integration typically updates roughly once per minute. ESPHome allows for near real-time data polling
* **Privacy and Reliability:** Keeping data within the local network and avoiding "rate limiting" or lag issues associated with third-party servers.
* **Granular Control:** Enabling the ability to adjust inverter settings (like charging modes or smart port configurations) directly from Home Assistant without using the official app.

## Hardware Specifications

It has been confirmed that both the **WiFi** and the **WiFi + Ethernet** versions of the dongles are based on the **ESP32** microcontroller.

* **WiFi + Ethernet Dongle:** Features an **ESP32-WROOM-32UE** module, an SN65176B RS485 transceiver, and an IP101GR Ethernet controller.
* **WiFi Dongle:** While simpler, it also utilizes an **ESP32-C3** chip, making the flashing process virtually identical across both hardware versions.

## Role of ESPHome and Home Assistant

* **ESPHome:** Acts as the bridge between the inverter's hardware (via Modbus) and the network. It handles the low-level communication
  protocols and allows the user to define sensors and switches using simple YAML configuration files. Once flashed, ESPHome supports
  **OTA (Over-The-Air) updates**, meaning the dongle never needs to be plugged into a programmer again.
* **Home Assistant:** Serves as the central dashboard and automation engine. Because ESPHome uses a native API for Home Assistant, 
  the modified dongles are **auto-discovered**. All inverter metrics (PV production, battery SOC, load, etc.) appear instantly as 
  entities that can be used in automations, energy dashboards, and long-term statistics.

## Required Tools for Flashing

* Will require USB to TTL adapter with 5V power, such as [this one](https://www.amazon.com/dp/B00LODGRV8).
* HDMI breakout board, [this one](https://www.amazon.com/dp/B0D91KHZJM), or [this one](https://www.amazon.com/dp/B0CKN298QF)

Connections are as follows:

| **HDMI Pin** | **Function** | **Wiring Connection** | **Description**                        |
| ------------ | ------------ | --------------------- | -------------------------------------- |
| **18**       | **VCC**      | **+5V**               | Main power supply for the dongle       |
| **17**       | **GND**      | **Ground**            | Common ground reference                |
| **10**       | **TXD**      | **Adapter RX**        | Transmit Data (from Dongle to PC)      |
| **9**        | **RXD**      | **Adapter TX**        | Receive Data (from PC to Dongle)       |
| **12**       | **BOOT**     | **NC or GND**         | GND on boot to flash                   |
| **5**        | **RST**      | **NC or GND**         | Reset; Short to GND to reboot the chip |
| **14**       | **RS485 B**  | **NC**                | Use to debug RS485 comms               |
| **15**       | **RS485 A**  | **NC**                | Use to debug RS485 comms               |

## Internal GPIO Assignments

[EG4 Wi-Fi + Ethernet Dongle](https://eg4electronics.com/categories/communication/eg4-wi-fi-ethernet-dongle/). See
[example config](./dongle-variants/wifi-ethernet-dongle.yaml)

| **GPIO** | **Function**                     |
| -------- | -------------------------------- |
| GPIO-15  | 'IP' LED                         |
| GPIO-13  | 'Cloud' LED                      |
| GPIO-33  | 'Inv' LED                        |
| GPIO-14  | 'Reset' BUTTON                   |
| GPIO-17  | 'D' on RS485 (OUT)               |
| GPIO-4   | 'R' on RS485 (IN)                |
| GPIO-32  | !RE & DE on RS485                |
| GPIO-18  | MDIO (Ethernet)                  |
| GPIO-23  | MDC (Ethernet)                   |
| GPIO-5   | RESET_N aka power-pin (Ethernet) |

[EG4 Wi-Fi only Dongle](https://eg4electronics.com/wp-content/uploads/2024/07/EG4-Wifi-Dongle-Troubleshooting-Guide.pdf). See
[example config](./dongle-variants/wifi-dongle.yaml)

| **GPIO** | **Function**                 |
| -------- | ---------------------------- |
| GPIO0    | !RE & DE on RS485 (inverted) |
| GPIO2    | RX on RS485                  |
| GPIO3    | TX on RS485                  |
| GPIO5    | Wifi LED                     |
| GPIO6    | INV LED                      |
| GPIO7    | Cloud LED                    |

## Sample Configs

TODO: Add more

* [GridBOSS](./devices/gridboss.yaml) 

# Dongle Flashing Notes

## Programmer Board

Hardware required:

* Will require USB to TTL adapter with 5V power, such as [this one](https://www.amazon.com/dp/B00LODGRV8).
* HDMI breakout board, [this one](https://www.amazon.com/dp/B0D91KHZJM), or [this one](https://www.amazon.com/dp/B0CKN298QF)

Connections:

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

## EG4 Wi-Fi + Ethernet Dongle

https://eg4electronics.com/categories/communication/eg4-wi-fi-ethernet-dongle/

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

## EG4 Wi-Fi only Dongle

https://eg4electronics.com/wp-content/uploads/2024/07/EG4-Wifi-Dongle-Troubleshooting-Guide.pdf

| **GPIO** | **Function**                 |
| -------- | ---------------------------- |
| GPIO0    | !RE & DE on RS485 (inverted) |
| GPIO2    | RX on RS485                  |
| GPIO3    | TX on RS485                  |
| GPIO5    | Wifi LED                     |
| GPIO6    | INV LED                      |
| GPIO7    | Cloud LED                    |



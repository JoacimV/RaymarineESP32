### Intro
<img width="1920" height="1080" alt="billede" src="https://github.com/user-attachments/assets/769d572b-4528-464a-9b68-38c7eee1a444" />

I wanted an extra way to control my boat's Raymarine autopilot, so I built a simple remote control using an ESP32, MCP2515 CAN Bus module, and some buttons. The remote sends commands to the autopilot over the NMEA2000 network.

The remotes capabilities are basic, but it gets the job done. It has buttons for AUTO, STANDBY, +10 degrees, and -10 degrees. The remote connects to the NMEA2000 network using a MCP2515 CAN Bus module.

This remote costs around 15€ to build, which is significantly cheaper than buying a commercial remote (730€ as of writing this).

The remote connects to the NMEA2000 network, so you need to connect your SeaTalkNG network to your NMEA2000 network, with a NMEA2000 adapter cable.

It currently only works with Raymarine autopilots that support the NMEA2000 protocol, such as the EV-100 and EV-200 series. (I have tested it with EV-100).


### Hardware
- ESP32 + Expansion board - [Amazon affiliate Link](https://amzn.to/46IAd6L)

- MCP2515 CAN Bus Module - [Amazon affiliate Link](https://amzn.to/4nZz4yW)

- Jumper wires [Amazon affiliate Link](https://amzn.to/4pUqzHe)
- DC Cable [Amazon affiliate Link](https://amzn.to/4nsR4Sa)
- NMEA2000 Cable (Cut the female port off) - [Amazon affiliate Link](https://amzn.to/46G0wfn)
- Buttons - [Amazon affiliate Link](https://amzn.to/3IAz6OH)

### 3D Printed Case
I designed the case using blender and printed it with BambuLab PLA Matte. You can find the STL files in the `case` directory of this repository.

### Pins

| ESP32 Pin | MCP2515 Pin | Description         |
| --------- | ----------- | ------------------- |
| GPIO5     | CS          | Chip Select         |
| GPIO18    | SCK         | Serial Clock        |
| GPIO19    | SO          | Master In Slave Out |
| GPIO23    | SI          | Master Out Slave In |

To power the MCP2515 module, connect the VCC and GND pins to a 5V power on the expansion board.
NMEA2000 power goes to the expansion board through a type b connector.

NMEA white and blue wire go to the MCP2515 module, blue wire to CANL and white wire to CANH.

Wiring for buttons:


| Button  | ESP32 Pin | Description  |
| ------- | --------- | ------------ |
| AUTO    | GPIO13    | Button Input |
| STANDBY | GPIO12    | Button Input |
| +10     | GPIO14    | Button Input |
| -10     | GPIO26    | Button Input |

### Software
This project is built using [PlatformIO](https://platformio.org/).

The raymarine pilot commands are greatly inspired by [this project](https://github.com/matztam/raymarine-evo-pilot-remote).

### Libraries
- Timo Lappalainen NMEA2000 library and MCP library: [GitHub Link](https://github.com/ttlappalainen)
- Seeed-Studio CAN library: [GitHub Link](https://github.com/Seeed-Studio/Seeed_Arduino_CAN)

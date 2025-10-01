### Intro
I wanted an extra way to control my boat's Raymarine autopilot, so I built a simple remote control using an ESP32, MCP2515 CAN Bus module, and some buttons. The remote sends commands to the autopilot over the NMEA2000 network.

The remotes capabilities are basic, but it gets the job done. It has buttons for AUTO, STANDBY, +10 degrees, and -10 degrees. The remote connects to the NMEA2000 network using a MCP2515 CAN Bus module.

This remote costs around 15€ to build, which is significantly cheaper than buying a commercial remote (730€ as of writing this).

The remote connects to the NMEA2000 network, so you need to connect your SeaTalkNG network to your NMEA2000 network, with a NMEA2000 adapter cable.

It currently only works with Raymarine autopilots that support the NMEA2000 protocol, such as the EV-100 and EV-200 series. (I have tested it with EV-100).


### Hardware
- ESP32 - [Amazon Link](https://www.amazon.de/APKLVSR-ESP-32S-udviklingsboard-str%C3%B8mforsyningskort-Bluetooth/dp/B0CQNCGVKM/ref=sr_1_8_sspa?crid=157F5NKS2WYJ2&dib=eyJ2IjoiMSJ9.wLRADyRoyeR2s6vqHTGry7QMBY8ZXUlel1aBJtWTnddCheZKRcjnThHXdT1NJG-2nCVJ4asu0Dzg8uejYnVLczWsI7xl7nQ_AWQQNtnJ6Xc862KcwAc4HAiHupAEV7sLtvEUcDK_j679_gtx_AzqYLS-odK_MuJGc8ni9yhnzrsLvDVAO6oSgiQap1S5uc7Zi76ICIjX04mRxioljERGHOV-YkpwxttXSQI5SUCi0ic.afFXyL4tCUZm0WGrz5JXD0rZxOZs8mNgvxDRSIcAT3c&dib_tag=se&keywords=esp32&qid=1758743039&sprefix=esp32%2Caps%2C177&sr=8-8-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9tdGY&psc=1)

- ESP32 Expansion board - [Amazon Link](https://www.amazon.de/APKLVSR-ESP-32S-udviklingsboard-str%C3%B8mforsyningskort-Bluetooth/dp/B0CQNCGVKM/ref=sr_1_8_sspa?crid=157F5NKS2WYJ2&dib=eyJ2IjoiMSJ9.wLRADyRoyeR2s6vqHTGry7QMBY8ZXUlel1aBJtWTnddCheZKRcjnThHXdT1NJG-2nCVJ4asu0Dzg8uejYnVLczWsI7xl7nQ_AWQQNtnJ6Xc862KcwAc4HAiHupAEV7sLtvEUcDK_j679_gtx_AzqYLS-odK_MuJGc8ni9yhnzrsLvDVAO6oSgiQap1S5uc7Zi76ICIjX04mRxioljERGHOV-YkpwxttXSQI5SUCi0ic.afFXyL4tCUZm0WGrz5JXD0rZxOZs8mNgvxDRSIcAT3c&dib_tag=se&keywords=esp32&qid=1758743039&sprefix=esp32%2Caps%2C177&sr=8-8-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9tdGY&psc=1)
- MCP2515 CAN Bus Module - [Amazon Link](https://www.amazon.de/dp/B0CTF7PX4S?ref=ppx_yo2ov_dt_b_fed_asin_title)

- Jumper wires
- DC Cable [Amazon Link](https://www.amazon.de/RUNCCI-YUN-monteringsadapters%C3%A6t-adapter-mobiltelefon-overv%C3%A5gningskameraer-5-mm-x-2-1-hult-stik-s%C3%A6t-R326/dp/B089DXQDS9/ref=sr_1_8_sspa?crid=1LS18SSET92UQ&dib=eyJ2IjoiMSJ9.0MvcZq4FL9tukzkbNL8Kc_O2Dy5I_OLsphuZPs0Y8dO5VbAqFcNuC3cBiQl5JEUXXQfYeXM9Cyvab0MEV-0dDMpUVL9RiPQk2GMMuN5eq1Iu54aWbxtYVN-b5YDzOtQFNuuPZEG47eYEXUVEkmVus8O-_54m3TIYmPdritAhwBFFpLomeNHKvadal9eXJEm1cQXohz4b252p92A1Fkh9j9tTcoiB_aPzKvB3okbrwVM.0yXLbzv-yiR9L1d_2io-0TS9p48OUVYizj15owr5iT8&dib_tag=se&keywords=dc+cable&qid=1758743749&sprefix=dc+cable%2Caps%2C95&sr=8-8-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9tdGY&psc=1)
- NMEA2000 Cable (Cut the female port off) - [Amazon Link](https://www.amazon.de/NMEA2000-backbone-kabel-drop-kabel-marinebl%C3%A5-GPS-tilbeh%C3%B8r/dp/B0BBS2L8PD/ref=sr_1_1_sspa?crid=2UFT86MVB7YBA&dib=eyJ2IjoiMSJ9.QW_mtvHLf6kRCkO8CFeVHJm7VVASIcKvsNfWnPs7ycZl7X45wUgbT0JkGKALCxjt00jjCCO40WvVnbHnueS-T2mCKkzXBup89CO1E_YbPYyKCfNnv6fhzpgHz0wNJJNAUS5bY0NbkZgPPbtqUuQMsOfGeC8XTrsxxOol8b7vsLyZUrrSJez_EmtWQFeYpJqnOTwOCpej3PEsk4Tr6KpYHkg_I4j13zVsO9lTqGIBpTId28NoBnXcmbXXF3AznUbyLrIWxeX1rd6trBVDHPdK1FlLwXsX1NHqjqImUxp1_c8.J9a2Eu1v-KSy1V8Vmfkl-yIs91VMnOnlRwJJXzUw978&dib_tag=se&keywords=nmea2000+cable&qid=1758744504&sprefix=nmea2000+cable%2Caps%2C83&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1)
- Buttons - [Amazon Link](https://www.amazon.de/dp/B08L49F7DV?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)

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
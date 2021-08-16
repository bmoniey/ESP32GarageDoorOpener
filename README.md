# ESP32GarageDoorOpener

A simple Garage Door Opener Application for the ESP32. Point your phone or browser directly at the device. No MQTT.

 ![MainPage](https://github.com/bmoniey/ESP32GarageDoorOpener/blob/main/gallery/MainPage.png?raw=true)

## Features
- Key Pad Code Entry
- Lamp Control
- WiFiManager
- OTA Over the Air Updates
- Admin Page
- Info Page

## Notes:
- Access Point default IP address: 192.168.4.1
- mDNS default url: http://garage-test.local
- mDNS will not work on Android Phones.

## Build Evironment
- Platform IO

## 3D
Small housing and lid for a 50x70 proto board. In this example an ESP32-WROOM-DevKit V1 is used. Any ESP32 should work.

## PINS
- OPEN_PIN 32
- LAMP_ON 23

## Security
- Use at your own risk!
- Does not use https so others on your network can see all credentials and code.

## Version

1.1.264 The intial version released to GitHub
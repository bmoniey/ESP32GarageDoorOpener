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

## Build Evironment
- Platform IO

## 3D
Small housing and lid for a 50x70 proto board. In this example an ESP32-WROOM-DevKit V1 is used. Any ESP32 should work.

![3D](https://github.com/bmoniey/ESP32GarageDoorOpener/blob/main/gallery/housing50x70-rendered.JPG?raw=true)


## ECAD

![ECAD](https://github.com/bmoniey/ESP32GarageDoorOpener/blob/main/ecad/ESP32GarageDoorOpener/ESP32GarageDoorOpener.svg?raw=true)

## PINS
- OPEN_PIN 32
- LAMP_ON 23

## Security
- Use at your own risk!
- Does not use https so others on your network can see all credentials and code.

## Flashing Firmware and Filesystem
- This project uses Little FS. This project is setup for windows using the mklittlefs.exe utility. See platformio.ini.
- Flash binary using platformio->upload
- Build File System Image platformio->Build File System Image
- Upload FIle System Image platformio->Upload File System Image

## Default Settings and links:
- Device Name:garage-test
- Access Point default IP address: 192.168.4.1
- mDNS default url: http://garage-test.local
- Admin page: http://garage-test/admin
- OTA: http://garage-test/update
- Reset Wifi Setting: http://garage-test/reset
- Door Open Code: 161974

## Version

1.1.264 The intial version released to GitHub
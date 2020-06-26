# Handheld Gaming console

This project is a handheld gaming console for retro-gaming on Raspberry Pi.\
It also contains a media centre for watching Movies/ Playing music ..etc

## System Overview

The game console is based on 2 units of control:

1. The secondary controller, which acts as a gamepad (Here we used Arduino Leonardo, an alternative would be Arduino Micro).

2. The main controller, which acts as a game emulator (Here we used Raspberry Pi).


![BlockDiagram](../../media/ConsoleMedia/GameConsole_BlockDiagram.png)

## Tutorial

**Preparing Raspberry Pi Image**

There are plenty of Pi images that support retro-gaming (RetroPie, RecalBox, Lakka ..etc).\
For this project we used RetroPie, and Kodi port for the media centre.

Installing the image is straightforward:\
1. Download a suitable image for your Pi version [here](https://retropie.org.uk/download/)
2. Unzip the image, and copy the unzipped .img file your SD card using *dd* command as follows:

> dd bs=4M if=**retropie.img** of=**/dev/mmcblk0** status=progress conv=fsync

**Note**: You can use lsblk -p to discover the SD card name for using as of in the command above. (this name should be /dev/mmcblk0 or /dev/sdX)

Now, we need to edit some configurations (Enable WiFi, Setup Kodi).

3. Connect your Pi to a HDMI screen, and any input device to control (Keyboard, mouse, gamepad ..), then boot.
4. Use any of the methods mentioned [here](https://retropie.org.uk/docs/Wifi/) to enable WiFi connection.

**Note**: You can edit /etc/network/interfaces file to add a static IP for your wifi (to use ssh for example).\
You can find a sample in this repo.

5. Now, follow [this tutorial](https://thepi.io/how-to-install-kodi-on-retropie/) to setup Kodi.\
Kodi may not work with your gamepad at first, you can attach a mouse and configure your Gamepad using System Settings as prompted by Kodi.\
or you can manually add you gamepad as mentioned [here](https://retropie.org.uk/docs/KODI/).

Now, your image is ready.\
Another way to add Kodi to your image is to use dualboot (NOOBS or BerryBoot),\
and add an image that supports Kodi (LibreELEC for example, or a customized image using buildroot) alongside your gaming image.

**Using Arduino as a Gamepad**

For this purpose, [Joystick library](https://github.com/MHeironimus/ArduinoJoystickLibrary) was used.
The gamepad also supports tilt control. So, we used a gyroscope with [Adafruit_MPU6050 library](https://github.com/adafruit/Adafruit_MPU6050) and [Adafruit_Sensor library](https://github.com/adafruit/Adafruit_Sensor).

The idea is simple, a switch is used to turn on/off tilt control. When turned on, Arduino will read left/right acceleration and send normal left/right button signal to the Raspberry Pi.

**Assembling Hardware**

*Automatic Audio Redirection*

The console has built-in speakers, and an external audio jack for the user.\
To switch off the built-in speakers when headphones are attached, we used the following circuit:

Circuit image will be added.

*Case*

The **Hardware Design** folder contains files for 3D printing. Both faces (Top and Down) are divided into 2 parts that should be joined together.\
It is greatly recommended to use heat sinks for the Pi and position it to face the fan.
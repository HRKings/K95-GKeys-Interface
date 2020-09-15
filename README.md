# K95 GKeys Interface
This repository holds the code to a wrapper for the K95 GKeys using hidapi. I've created it because the software from Corsair to configure the extra keys was consuming too much RAM and was not working as I intended.

## How it works
This software works by reading the hid of the keyboard and identifying the presses on the gkeys and sending back to the system a ghost key with an aditional code. This can be later used by other softwares

## How to use
After cloning the repository, you can buid it with Visual Studio 2019+ and launch the software. A command prompt will appear briefly and will disappear. After that, you can remap the keys using specific software, such as AutoHotkey.

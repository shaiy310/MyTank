#!/bin/bash
# using tutorial from: elinux.org/RPi-Cam-Web-Interface
sudo apt-get update
sudo apt-get dist-upgrade
sudo apt-get upgrade

git clone https://github.com/silvanmelchior/RPi_Cam_Web_Interface.git
cd RPi_Cam_Web_Interface/
./install.sh

sudo reboot

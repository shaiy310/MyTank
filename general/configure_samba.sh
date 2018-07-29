#!/bin/bash
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install samba samba-common-bin
sudo mkdir -m 1777 /share

sudo echo -e """\n[share]\ncomment = Rasp Pi Share\npath = /share\nbrowseable = yes\nwriteable = yes\nonly guest = no\ncreate mask = 0777\ndirectory mask = 0777\npublic = yes\nguest ok = yes\n""" >> /etc/samba/smb.conf


echo "run 'sudo smbpasswd -a pi'"
sudo /etc/init.d/samba restart

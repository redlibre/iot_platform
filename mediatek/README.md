Hello!, with this script you can get remote control of your linkit smart device using python and mqtt

:one: update db list package inside openwrt linux

> opkg update

:two: install paho-mqtt libraries

> pip install paho-mqtt

:three: copy&paste script 

> copy python code from https://github.com/redlibre/iot_platform/blob/master/mediatek/linkit7688.py in your openwrt linkit linux eg. remote.py, makes changes on # ----- CHANGE THESE FOR YOUR SETUP -----# from "devinfo" website section, save changes and execute script.

>python remote.py


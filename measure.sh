#!/bin/bash
make
strength=$(./strength)
speed=$(./speed)

cd ./Raspberry-ssd1306
./oled r
./oled +1 "WIFI ANALYZER"
./oled +2 "Strength:$strength"
./oled +3 "Speed: $speed"
sudo ./oled s
cd ..

# WiFi-Analyzer
Developers: Siddhartha Bajracharya and Josh Wilbur.

A handheld device that displays real-time statistics about a user's WiFi including speed and signal strength.

Prior to first run, you must do the following.
* Install libcurl4 library using: sudo apt-get install libcurl4-openssl-dev
* Install WiringPi library
* Ensure I2C support is enabled in settings (for RPi)

A bash script will compile and execute the programs. Run using: bash ./measure.sh

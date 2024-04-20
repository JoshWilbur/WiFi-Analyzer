# WiFi-Analyzer
Developers: Siddhartha Bajracharya and Josh Wilbur.

Display library written by "nopnop2002" and is publicly shared on Github. No license is posted with the code, however section D-5 of the Github terms of service 
states: "By setting your repositories to be viewed publicly, you agree to allow others to view and "fork" your repositories" 

A handheld device that displays real-time statistics about a user's WiFi including speed and signal strength.

Prior to first run, you must do the following.
* Install libcurl4 library using: sudo apt-get install libcurl4-openssl-dev
* Install WiringPi library
* Ensure I2C support is enabled in settings (for RPi)

A bash script will compile and execute the programs. Run using: bash ./measure.sh

# Benchmarking
Distance | Device RSSI | iPhone RSSI | Device Speed | iPhone Speed
  <1 M	 |    -9 dBm   |    -8 dBm   |   2.57 Mbps  |  3.31 Mbps
  5 M    |   -54 dBm   |   -51 dBm   |   2.56 Mbps  |  2.60 Mbps
  10 M   |   -58 dBm   |   -57 dBm   |   2.40 Mbps  |  2.71 Mbps
  50 M   |   -72 dBm   |   -68 dBm   |   2.31 Mbps  |  2.17 Mbps

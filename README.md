# Arduino Bluetooth Relay w/ Light Sensor

### Personal project that uses an Arduino, BLE board, photoresistor, and relay assembly. 

Started as a project that would toggle a relay on and off given an empty string being sent from phone using UART.

Added photoresistor that toggles relay on and off with different light levels. When BLE receives an empty string it disables the photoresistor and toggles the relay to the opposite state that it was in.

--  Photoresistor sensor can be turned back on if 'r' or 'R' is sent to BLE.


Photoresistor can be ignored and state toggled for varying amounts of time given different inputs, 1 minute, 2 minutes, 4 minutes, 8 minutes and 10 seconds if the BLE receives a predetermined character. Whatever current state the relay is in is switched and the Arduino runs through a FOR loop to to count down for the given time before reinitiating the photoresistor.


The next steps of this project will be refining the code to error handle input and then switch gears and create a native app with buttons for each bit of functionality.

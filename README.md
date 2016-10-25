# Arduino Bluetooth Relay w/ Light Sensor

### Small personal project that uses an Arduino, BLE board, photoresistor, and relay assembly. 

Started as a project that would toggle a relay on and off given an empty string being sent from phone using UART.

Added photoresistor that toggles relay on and off with different light levels. When BLE receives an empty string it disables the photoresistor and toggles the relay to the opposite state that it was in.

--  Photoresistor sensor can be turned back on if 'l' or 'L' is sent to BLE.


Photoresistor can be ignored and state toggled for 10 seconds if the BLE receives '10'. Whatever current state the relay is in is switched and the Arduino runs through a FOR loop to to count down 10 seconds before reinitiating the photoresistor.

--  This was intended to sit as a proof of concept for toggling the relay and locking out the photoresistor for x amount of time. The next step will be taking any number sent from phone and using that as a parameter for the timeout.


The next steps of this project will be refining the code to lock out the photoresistor for x amount of time, error handle for input that contains something other then just numbers, and then switch gears and create a native app with buttons for each bit of functionality.

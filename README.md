# neatobotvacwebinterface
This is the simplest webinterface for a Neato Botvac with a serial adapter - ESP 8266 or ESP 32 Code. 

- For connecting the ESP to the Botvac, for example D85 please visit: https://github.com/sstadlberger/botvac-wifi
- For possible commands see: https://github.com/jeroenterheerdt/neato-serial/blob/master/XV-ProgrammersManual-3_1.pdf

Before compiling enter your SSID and PW to the code. The CLIENT_ID is for mdns in your home network. Fill in whatever you like. If the ESP is connected to the network the API is:

- http://IP-ADDRESS/  => if everything is running, the return value is OK
- http://IP-ADDRESS/exec?command=COMMAND => replace COMMAND with a actual command from the possible command list. For example: http://IP-ADDRESS/exec?command=getcharger will return the current values for charging and docking state. 

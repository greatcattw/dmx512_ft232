# dmx512_ft232
Using FTDI ft232 as host controller to control DMX512 device in Ubuntu<br>
# In progress
## Discription
DMX512 protocol includes a status of break.<br>
In order to make status of break, I use DTR to carry out it.<br>
<br>
![pic](pic/protocol.jpg)<br>
<br>
![pic](pic/schematic.jpg)<br>
<br>
![pic](pic/1.jpg) <br>
<br>
![pic](pic/2.jpg) <br>
<br>
![pic](pic/3.jpg) <br>
<br>
# Test sample code
## Test par light
<br>
Datasheet of channel 
<br>
<br>
![pic](pic/par_ch_function.jpg) <br>
<br>
Make sure /dev/ttyUSB0 is a+rw<br>
Make sure address of par light is 001.<br>
Test red light.<br>
Test green light.<br>
Test blue light.<br>
Test off light.<br>

## Test magic ball light
Make sure /dev/ttyUSB0 is a+rw<br>
Make sure address of par light is 001.<br>

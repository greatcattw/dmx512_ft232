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
![pic](pic/box_id.jpg) <br>
<br>
# Test sample code
## Test par light
<br>
Datasheet of channel <br>

![pic](pic/par_ch_function.jpg) <br>
<br>
Make sure /dev/ttyUSB0 is a+rw<br>
Make sure address of par light is 001.<br>
### Test red light.<br>
./a.out 255 255 0 0 0 0 0 0 0 0 <br>

### Test green light.<br>
./a.out 255 0 255 0 0 0 0 0 0 0 <br>

### Test blue light.<br>
./a.out 255 0 0 255 0 0 0 0 0 0 <br>


## Test magic ball light
<br>

![pic](pic/ball_ch_function.jpg) <br>
Make sure /dev/ttyUSB0 is a+rw<br>
Make sure address of par light is 001.<br>
### Test red light.<br>
./a.out 39 0 0 0 0 0 0 0 0 0 <br>

### Test green light.<br>
./a.out 59 0 0 0 0 0 0 0 0 0 <br>

### Test blue light.<br>
./a.out 79 0 0 0 0 0 0 0 0 0 <br>

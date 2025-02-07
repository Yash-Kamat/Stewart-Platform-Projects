# How to get roll and pitch values from the joystick

Note: These instructions are specific to linux, and might need to be modified for different platforms. You might need to install numpy as np, pyserial, asyncio, websockets and json python packages for the code to work.

## Connecting the ESP32 Hardware

The motors 1,2,3,4,5,6 have to be connected to pins 5,18,19,21,22,23.

## Connect to Hotspot

Connect your device(where the server will be hosted) and phone(where the joystick will be opened) on the same WiFi hotspot.

## Modify the codes to suit your use case

In ```joystick.html```, find the line:

```javascript:
const socket = new WebSocket("ws://192.168.1.100:8765");
```

and replace ```192.168.1.100``` with your device's ip address.

In ```Maze_Code.py```, ```'/dev/ttyUSB0'``` has to be replaced with the serial port your ESP32 Microcontroller is connected to.

Also, change the values of
```python:
r_B = 68.6      # Base radius
r_P = 70.3      # Platform radius
lhl = 50.0      # Upper leg length
ldl = 128.0     # Lower leg length
gamma_B = 0.2204  # Base offset angle
gamma_P = 0.3681  # Platform offset angle
```
according to Yeok-C's inverse kinematics requirements.

## Launching the website and running the code.

Open two terminals and ```cd``` into the folder ```web_joystick``` in both of them.

In one terminal run:
```bash:
python3 -m http.server 8000
```
And in the other, run:
```bash:
python3 Maze_Code.py
```
Now, open the website ```http://<ip-address-of-server-device>:8000/joystick.html``` on your phone.

If everything goes correctly, after powering everything on, and moving the joystick on you phone, you should see the roll and pitch values printed to the terminal running Maze_Code.py, and the servos should move accordingly to change the orientation of the platform.

## Testing and Calibration

Test how it's working in your case and calibrate the values in the code.

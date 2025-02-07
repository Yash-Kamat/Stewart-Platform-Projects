# How to get roll and pitch values from the joystick

Note: These instructions are specific to linux, and might need to be modified for different platforms.
You might need to install the packages asyncio, websockets and json for the code be executed.

## Connect to Hotspot

Connect your device(where the server will be hosted) and phone(where the joystick will be opened) on the same WiFi hotspot.

## Modify the code to suit your use case

In ```joystick.html```, find the line:

```javascript:
const socket = new WebSocket("ws://192.168.1.100:8765");
```

and replace ```192.168.1.100``` with your device's ip address.

## Launching the website and starting the server

Open two terminals and ```cd``` into the folder ```web_joystick``` in both of them.

In one terminal run:
```bash:
python3 -m http.server 8000
```
And in the other, run:
```bash:
python3 server.py
```
Now, open the website ```http://<ip-address-of-server-device>:8000/joystick.html``` on your phone.

After moving the joystick on you phone, you should see the roll and pitch values printed to the terminal running server.py.

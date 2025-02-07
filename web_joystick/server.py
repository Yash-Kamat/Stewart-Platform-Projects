# import asyncio
# import websockets

# async def handler(websocket):
#     print("✅ Client connected!")  # Debugging message
#     async for message in websocket:
#         print(f"🎮 Received: {message}")  # Show joystick data

# async def main():
#     async with websockets.serve(handler, "0.0.0.0", 8765):
#         await asyncio.Future()  # Keep server running

# asyncio.run(main())

import asyncio
import websockets
import json  # Import JSON module

async def handler(websocket):
    print("✅ Client connected!")
    async for message in websocket:
        try:
            data = json.loads(message)  # Convert JSON string to dictionary
            roll = float(data["roll"])   # Extract roll
            pitch = float(data["pitch"]) # Extract pitch
            print(f"🎮 Roll: {roll}, Pitch: {pitch}")  # Print raw values
        except (json.JSONDecodeError, KeyError, ValueError) as e:
            print(f"⚠️ Error processing message: {message} → {e}")

async def start_server():
    async with websockets.serve(handler, "0.0.0.0", 8765):
        await asyncio.Future()

asyncio.run(start_server())


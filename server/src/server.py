import asyncio
import websockets
import json
import subprocess


async def handle_client(websocket):
    print("New Client connected.")
    
    while True:
        msg = await websocket.recv()
        print(f"server Recieved: {msg}")
        
        data = json.loads(msg)
        print(data, type(data))
        with open("script.py", 'w') as file:
            file.write(data['code'])
        run_output = subprocess.run(['python', 'script.py'], capture_output=True, text=True).stdout
        print('output:', run_output)
        response = json.dumps({'output': run_output})

        await websocket.send(response)
        print(f"Server Sent: {response}")


async def main():
    async with websockets.serve(handle_client, "localhost", 8765):
        print("Server up and running.")
        await asyncio.Future()  # run forever


if __name__ == "__main__":
    asyncio.run(main())
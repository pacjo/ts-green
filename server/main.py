import json
import socket
from threading import Thread

from prometheus_client import Gauge
from prometheus_client.exposition import start_http_server

HOST = "0.0.0.0"
PLANT_PORT = 6000
PROMETHEUS_PORT = 8000

# make sure this is kept in sync with sensor_reading.h definitions
METRICS = {
    "temperature": Gauge("temperature", "Temperature sensor value"),
    "humidity": Gauge("humidity", "Humidity sensor value"),
    "light": Gauge("light", "Light sensor value"),
    "soil_moisture": Gauge("soil_moisture", "Soil moisture sensor value"),
}


def start_plant_receiver(host: str, port: int):
    print(f"Listening on {host}:{port}")
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((host, port))
    server.listen()

    print("Waiting for connection...")
    conn, addr = server.accept()

    with conn:
        print(f"Connected by {addr}")

        buffer = b""
        delimiter = b"\r\n"  # caused by WiFiClient.println()

        while True:
            data = conn.recv(1024)
            if not data:
                print(f"Connection from {addr} closed.")
                break

            buffer += data

            # process all complete messages
            while delimiter in buffer:
                message, buffer = buffer.split(delimiter, 1)

                message_str = message.decode("utf-8")
                message = json.loads(message_str)

                handle_message(message)


def handle_message(message: dict):
    print(f"message: {json.dumps(message)}")

    sensor: str = message["sensor"]
    value: float = message["value"]
    METRICS[sensor].set(value)


THREADS = [
    Thread(target=start_plant_receiver, args=(HOST, PLANT_PORT)),
    Thread(target=start_http_server, args=(PROMETHEUS_PORT,)),
]

if __name__ == "__main__":
    for thread in THREADS:
        thread.start()

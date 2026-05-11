import json
import socket

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
    "pressure": Gauge("pressure", "Pressure sensor value"),
}


def start_plant_receiver(host: str, port: int):
    server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    print(f"Listening on UDP {host}:{port}")

    while True:
        data, addr = server.recvfrom(1024)
        process_payload(data, addr)


def process_payload(data: bytes, addr):
    try:
        message_str = data.decode("utf-8").strip()
    except UnicodeDecodeError:
        print(f"Ignored invalid UTF-8 payload from {addr}.")
        return

    # ignore empty
    if not message_str:
        return

    # try parse
    try:
        message = json.loads(message_str)
    except json.JSONDecodeError:
        print(f"Failed to parse JSON from {addr}: {message_str}")
        return

    # make sure message is what we expect
    if not isinstance(message, dict):
        print(f"Payload is not a JSON object from {addr}: {message}")
        return

    sensor = message.get("sensor")
    value = message.get("value")

    if sensor is None or value is None:
        print(f"Missing 'sensor' or 'value' in message from {addr}: {message}")
        return

    if sensor not in METRICS:
        print(f"Unknown sensor type '{sensor}' from {addr}. Ignoring.")
        return

    # cast value
    try:
        numeric_value = float(value)
    except (ValueError, TypeError):
        print(f"Invalid numeric value for {sensor} from {addr}: {value}")
        return

    # and update metric
    METRICS[sensor].set(numeric_value)


if __name__ == "__main__":
    # start prometheus client (in background)
    start_http_server(PROMETHEUS_PORT)
    print(f"Prometheus metrics available on port {PROMETHEUS_PORT}")

    # run client on main thread
    try:
        start_plant_receiver(HOST, PLANT_PORT)
    except KeyboardInterrupt:
        # catch ctrl+c
        print("\nShutting down server.")

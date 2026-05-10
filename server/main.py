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
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # reuse socket after script restart
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind((host, port))
    server.listen()
    print(f"Listening on {host}:{port}")

    # handle accepting new (re)connections
    while True:
        print("Waiting for connection...")
        conn, addr = server.accept()

        with conn:
            print(f"Connected by {addr}")
            handle_connection(conn, addr)


def handle_connection(conn: socket.socket, addr):
    buffer = b""
    delimiter = b"\r\n"

    # handle one specific connection
    while True:
        try:
            data = conn.recv(1024)
        except ConnectionResetError:
            print(f"Connection from {addr} reset by peer.")
            break
        except Exception as e:
            print(f"Unexpected error reading from {addr}: {e}")
            break

        if not data:
            print(f"Connection from {addr} gracefully closed.")
            break

        buffer += data

        # process only complete messages
        while delimiter in buffer:
            message_raw, buffer = buffer.split(delimiter, 1)
            process_payload(message_raw)


def process_payload(message_raw: bytes):
    # try decode
    try:
        message_str = message_raw.decode("utf-8").strip()
    except UnicodeDecodeError:
        print("Ignored invalid UTF-8 payload.")
        return

    # ignore empty
    if not message_str:
        return

    # try parse
    try:
        message = json.loads(message_str)
    except json.JSONDecodeError:
        print(f"Failed to parse JSON: {message_str}")
        return

    # make sure message is what we expect
    if not isinstance(message, dict):
        print(f"Payload is not a JSON object: {message}")
        return

    sensor = message.get("sensor")
    value = message.get("value")

    if sensor is None or value is None:
        print(f"Missing 'sensor' or 'value' in message: {message}")
        return

    if sensor not in METRICS:
        print(f"Unknown sensor type '{sensor}'. Ignoring.")
        return

    # cast value
    try:
        numeric_value = float(value)
    except (ValueError, TypeError):
        print(f"Invalid numeric value for {sensor}: {value}")
        return

    # and update metric
    print(f"Updating {sensor}: {numeric_value}")
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

import json
import socket

HOST = "0.0.0.0"
PORT = 8000

if __name__ == "__main__":
    print(f"Listening on {HOST}:{PORT}")
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
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
                print(f"message: {json.dumps(message)}")

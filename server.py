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

        while True:
            data = conn.recv(1024)
            if not data:
                break
            print(data)

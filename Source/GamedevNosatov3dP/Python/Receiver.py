#!/usr/bin/env python3

import socket
from io import BufferedWriter, BytesIO
from dataclasses import dataclass

HOST = '127.0.0.1'  # Standard loopback interface address(localhost)
PORT = 65432        # Port to listen on (non - privileged ports are > 1023)

class HighscoreTable:
    name = ''
    scores = 0

    def __init__(self, inname, inscores):
        self.name = inname
        self.scores = inscores

    def GetData(self):
        writer = BufferedWriter(BytesIO())
        writer.write(int.to_bytes(self.scores, length=4, byteorder='little', signed=True))
        writer.write(self.name.encode('utf-8'))
        writer.flush()
        return writer.raw.getvalue()

highscorelist = []

while True:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print('Server listening...')
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                data = conn.recv(4)
                if not data:
                    continue

                requestid = int.from_bytes(data, byteorder='little')
                if requestid == 1:
                    data = conn.recv(5)
                    name = str(data, encoding='utf-8', errors='replace')
                    data = conn.recv(4)
                    scores = int.from_bytes(data, byteorder='little')
                    highscorelist.append(HighscoreTable(name, scores))
                    print('Player name: ', name, 'Player scores: ', scores)
                if requestid == 2:
                    entries = len(highscorelist)
                    conn.send(int.to_bytes(entries, length=4, byteorder='little', signed=True))
                    print('Entries to load: ', entries)
                    for x in highscorelist:
                        senddata = x.GetData()
                        conn.send(senddata)
                        print('Line sent')

                if requestid == 9:
                    s.close()
                    break

import json
from socket import *
from threading import Thread
from turtle import delay


def clientListen(): # This function is used for calling a thread to sit and wait for data to be received. It then prints the message, as the message from the server comes pre-parsed to the correct recipients
    while True:
        data = clientSocket.recv(1024).decode()
        print(data)
        print()

def clientTalk(): # This function is used for calling a thread to constantly gather an input and then send it to the encoding function to parse into a JSON and send it to the server
    while True:
        data = input("Type here: ")
        encodeJSON(data)

def encodeJSON(str): # This function parses the given input into a JSON for eaasy parsing on the server side. Further comments on each specific part
    n=0
    length = len(str)

    if (str[0] != '/'): # This is a check to see if the given input has a command, ie create, join, group, or private commands. If no slash is found, it is assumed to not be a command and sent as a public message
        file = {
            "status": 'public',
            "sender": username,
            "receiver": '',
            "text": str
        }
    else:
        while (str[n] != ' ' | str[n] == ''): # Gathers the format part of the string, ie the command to be given
            format = format + str[n]
            m = n + 1
        m=0
        while (str[n] != ' '): # Gather the name of the person/group the message is sent to, ie the receiver
            name = name + str[n]
            m = m + 1
        for x in range(m+n, length): # The rest of the message is read and stored for the text portion of the JSON
            message = message + str[x]
        file = { # Consolidating the data
            "status":format,
            "sender":username,
            "receiver":name,
            "text":message
        }
    data = json.dumps(file) # Encoding the JSON file to be sent through the sockets and then sent
    clientSocket.send(data.encode())





serverName = 'localhost' # Connecting to the server
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName,serverPort))
print(clientSocket.recv(1024).decode()) # Receiving the welcome and username prompts from the server
print(clientSocket.recv(1024).decode())
username = input("Type Username here: ") # input username and sends it to the server to be stored with the client's connection info
clientSocket.send(username.encode())
delay(500) # a wait because it sometimes overlaps the type here: and welcome messages
threadListen =Thread(target=clientListen) # constant listening thread to receive messages from the server and printing them
threadListen.start()
clientTalk() # using the main thread to constantly listen for inputs from the user, calling the talk function to run indefinitely


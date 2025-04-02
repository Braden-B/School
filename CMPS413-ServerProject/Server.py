import json
from threading import Thread
import queue
usernameList = []
groupList = []
clients = []
messageQueue = queue.Queue(maxsize=0)

def clientThreadListen(connectionSocket, addr):
   print(str(addr))
   connectionSocket.send(("Welcome to the chat!").encode())
   connectionSocket.send(('What is your username?').encode())
   username = connectionSocket.recv(1024).decode()
   usernameList.append(username)
   clients.append(connectionSocket)
   connectionSocket.send(('Welcome, ' + username).encode())
   while True:
      try:
         message = connectionSocket.recv(1024).decode()
         messageQueue.put(message)
      except:
         continue

def serverListen():
   while True:
      (connectionSocket, addr) = serverSocket.accept()
      clients.append(connectionSocket)
      thread = Thread(target=clientThreadListen, args=(connectionSocket, addr))
      thread.start()


from socket import * # basic server set up, supports a max of 10 clients at once
serverPort = 12000
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))
serverSocket.listen(10)
print('The server is ready to receive') # setup complete!
thread = Thread(target=serverListen, args=()) # sets up a listen thread to listen for incoming clients, and starts a listen thread for that specific client that not only adds it to a username and client list, but
thread.start()                                # will also allow for a client to send a message that is queued up for the server to process, meaning clients shouldn't run into sending issues on a busy server
while True:
   try:
      messageParse = messageQueue.get() # parses the JSON file sent to determine the command used, the sender, receiver, and the message itself
      status = messageParse["status"]
      name = messageParse["name"]
      receiver = messageParse["receiver"]
      text = messageParse["text"]
      toSendList = []
      if (status == "public"):
         for client in clients:
            client.send((name + ': ' + text).encode())
         break
      elif (status == "/private"):
         toSendList.append(receiver)
         for client in clients:
            if client in toSendList:
               client.send(("<Private> " + name + ': ' + text).encode())
         break
      elif


   except:
      continue












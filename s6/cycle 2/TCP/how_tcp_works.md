# How TCP Works

The basic idea is to make a server and a client. The client can connect to the server to exchange messages

> Always add the required header files for the methods used

## Some basic definitions

1.  **Socket :** <a id="socket"></a> You can think of a socket as something (a structure), maybe a virtual connector which can be used to connect to another socket.<br> Imagine it like a plug that can fit into a matching outlet to establish a connection.

    In C, `socket()` can be used to create a socket. <br>

    > `int socket(int domain, int type, int protocol);`

    For now you can leave the `domain` as `AF_INET`, `type` as `SOCK_STREAM` for TCP and `protocol` as `0` for the default protocol.<a id="sock-des"></a> The function returns the file descriptor for the socket created. (-1 is bad as it means error) <br>
    [Manual entry for socket](https://man7.org/linux/man-pages/man2/socket.2.html)

2.  **Port :** Port is like a doorway through which data can pass through on a computer. _Port number_ is just a number which can identify this door. Think of it like this, the IP address can identify the computer and port address can identify the specific process or application in that computer.

3.  **Bind :** When a socket is created, it does not have any address assigned to it. To make other sockets find and connect to our socket we can **bind** this socket with an address. Bind is typically done on the server so that clients can find and connect to this server socket.

    In C, we can use `bind()` to assign an address to a socket. <br>

    > `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

    `sockfd` is the file desciptor of the socket, `*addr` is the pointer to the [address](), `addrlen` is the length of `addr`. Returns an `int`, 0 (success) or -1 (you guessed it! error) <br>
    [Manual entry for bind](https://man7.org/linux/man-pages/man2/bind.2.html)

4.  **Listen :** Well it's obvious. The server is listening for incoming connections.

    In C we can use `listen()` to make a server listen for `connect()` requests. <br>

    > `int listen(int sockfd, int backlog);`

    `sockfd` is the [file descriptor](#sock-des) of the socket,
    `backlog` is the max length of the queue of pending connections (you don't need to worry about this, just set it as `5` or `10`)

    [Manual entry for listen](https://man7.org/linux/man-pages/man2/listen.2.html)

## Creation of a server

The first part of creating a server or a client is the creation of a socket.<br>
Creating a [socket](#socket) in C is as easy as <br>
`server_sock = socket(AF_INET, SOCK_STREAM, 0);` [view code](./simple_tcp/server.c#L20)

If all went well, we would now have a file descriptor which is just an integer (>2), assigned to `server_sock`

> File descriptor 0, 1, 2 are reserved <br>
> 0 : standard input <br>
> 1 : standard output <br>
> 2 : standard error <br>

So we got a socket whose `domain` is `AF_INET` (AF is address family and INET is the internet), `type` is `SOCK_STREAM` (which is used for TCP) and has the default `protocol` for this type (since `0` is given as the protocol argument).

Now What? <br>
This socket should be accessible from other sockets, right?<br>
The way we connect to a socket is by providing its address. So in order to make this socket accessible for connection from clients, we should assign an address to it.

### Creating an address structure

Thanks to `<arpa/inet.h>` we don't have to create any structure, instead we just have to use the predefined `struct sockaddr_in`. Create a variable of type `struct sockaddr_in`, clear its existing junk contents using `memset()` and edit 3 of its parameters (`sin_family`,`sin_port` and `sin_addr.s_addr`) and we are good to go! [View code](./simple_tcp/server.c#L28)

```
struct sockaddr_in server_addr; // creating the variable
memset(&server_addr, '\0', sizeof(server_addr)); // clear the server_addr
server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);
```

The socket is ready, the address structure is ready but there seems to be a slight problem.<br>
They are not linked or _binded_ by any mechanism.

### Bind

`bind()` just assigns an address to a socket. Once an address is _"binded"_ to a socket, this socket can be accessed from other sockets using this address.

> Address simply refers to the IP address and port number

the `bind()` method takes in the file descriptor of the socket, a pointer to the address variable and the length of the address variable and binds them (you dont need to worry on what glue is used to bind them :p )

`bind_val = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));` [View code](./simple_tcp/server.c#L33)

It is a good practice to check the return value of `bind()` to see if it was successful or not (`0` is success, `-1` is error).

Well, the server is ready to listen for incoming connections. But how does it know that it should listen for incoming connections?<br> That's where `listen()` comes into play.

### Listen

`listen()` is used to make the server listen for incoming connections. It takes in the file descriptor of the socket and the maximum length of the queue of pending connections.

`listen(server_sock, 10);` [View code](./simple_tcp/server.c#L41)

The server is now up and running, waiting for incoming connections.

---

## Creation of a client

The client is a bit simpler than the server. The client just has to connect to the server and exchange messages.

The first step is to create a socket. The client socket is created in the same way as the server socket. We are using the same options as we used for the server socket.

`client_sock = socket(AF_INET, SOCK_STREAM, 0);` [View code](./simple_tcp/client.c#L19)

### Creation of an address structure

Now, you could wonder why we require an address structure since there is need to bind the client to an address. <br>
This address structure variable is not for holding the address of the client, instead it is to hold the address of the server which we wish to connect. <br>
Creation of this variable for the client is similar to that of the server. <br>

1. Initialise the variable
2. Clear the initial junk values using `memset()`
3. Change the 3 parameters as we did before. [View Code](./simple_tcp/client.c#L27)

```
struct sockaddr_in addr;
memset(&addr, '\0', sizeof(addr)); // clear the addr
addr.sin_family = AF_INET;
addr.sin_port = port;
addr.sin_addr.s_addr = inet_addr(ip);
```

**Yay! We have our server listening for connections and a client ready to connect to the server**

<!-- ## Connecting the client and exchanging messages -->

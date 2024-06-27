# How TCP Works

The basic idea is to make a server and a client. The client can connect to the server to exchange messages

## Some basic definitions

1.  **Socket :** You can think of a socket as something (a structure), maybe a virtual connector which can be used to connect to another socket.<br> Imagine it like a plug that can fit into a matching outlet to establish a connection.

    In C, `socket()` can be used to create a socket. <br>

    > `int socket(int domain, int type, int protocol);`

    For now you can leave the `domain` as `AF_INET`, `type` as `SOCK_STREAM` for TCP and `protocol` as `0` for the default protocol. The function returns the file descriptor for the socket created. (-1 is bad as it means error) <br>
    [Manual entry for socket](https://man7.org/linux/man-pages/man2/socket.2.html)

2.  **Port :** Port is like a doorway through which data can pass through on a computer. _Port number_ is just a number which can identify this door. Think of it like this, the IP address can identify the computer and port address can identify the specific process or application in that computer.

3.  **Bind :** When a socket is created, it does not have any address assigned to it. To make other sockets find and connect to our socket we can **bind** this socket with an address. Bind is typically done on the server so that clients can find and connect to this server socket.

    In C, we can use `bind()` to assign an address to a socket. <br>

    > `int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`

    `sockfd` is the file desciptor of the socket, `*addr` is the pointer to the [address](), `addrlen` is the length of `addr`. Returns an `int`, 0 (success) or -1 (you guessed it! error) <br>
    [Manual entry for bind](https://man7.org/linux/man-pages/man2/bind.2.html)

4.  **Listen :**

## Creation of a server

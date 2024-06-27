# How TCP Works

The basic idea is to make a server and a client. The client can connect to the server to exchange messages

## Some basic definitions

1.  **Socket :** You can think of a socket as something (a structure), maybe a virtual connector which can be used to connect to another socket.<br> Imagine it like a plug that can fit into a matching outlet to establish a connection.

        In C, socket() can be used to create a socket <br>
        `int socket(int domain, int type, int protocol);`<br>
        For now you can leave the `domain` as `AF_INET`, `type` as `SOCK_STREAM` for TCP and `protocol` as `0` for the default protocol. The function returns the file descriptor for the socket created

    > ! is bad

</details>

<details>
<summary> Port </summary>
edit later
</details>

<details>
<summary> Bind </summary>
edit later
</details>

<details>
<summary> Listen </summary>
edit later
</details>

<details>
<summary> Connect </summary>
edit later
</details>

<details>
<summary> Accept </summary>
edit later
</details>

<details>
<summary> Send </summary>
edit later
</details>

<details>
<summary> Recv </summary>
edit later
</details>

<details>
<summary> Bind </summary>
edit later
</details>

## Creation of a server

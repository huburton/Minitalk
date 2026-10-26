# Minitalk

*[Version française](README.fr.md)*

A client sends text to a server using nothing but two UNIX signals, `SIGUSR1` and `SIGUSR2`.
School 19 (42 network) project, in C.

```text
$ ./server
PID: 2110260

$ ./client 2110260 "Bonjour 42 ! é ✓"      # in another terminal
                                           # the server prints: Bonjour 42 ! é ✓
```

## How it works

- The client sends each byte as 8 signals, most significant bit first: `SIGUSR2` for 1, `SIGUSR1` for 0.
  A final `'\0'` marks the end of the message.
- The server rebuilds the byte bit by bit in its signal handler and writes it as soon as the 8 bits are in.
- **Every bit is acknowledged.** The server answers each signal with `SIGUSR1` to the sender, whose PID it
  reads from `siginfo_t` (`SA_SIGINFO`). The client waits for that answer before sending the next bit, so
  no signal is lost when the server is busy, without guessing a delay.
- Text is sent as raw bytes, so UTF-8 characters (`é`, `✓`) arrive intact.

## Measured

On the home server, a 10,000-character message arrived complete in 0.31 s: about 260,000 bits per second,
each one acknowledged by the server.

## Build

```bash
make                         # builds ./server and ./client (with the bundled libft)
./server                     # prints its PID
./client <server_pid> "message"
```

`tester.sh` runs a series of sends, up to 5,300-character messages repeated ten times.

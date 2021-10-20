# Fuzzing a TCP socket

This folder contains a small network application written in C, that can be used as an example project to test the CI Fuzz socket fuzzer.

## Introducing the simple note server

The simple note server is a ~~very useful~~ application that allows a client to connect via TCP (port 5000) and perform several actions with notes, like saving a note, showing the note or deleting it. To use this functionality, the client has to navigate through a menu with commands like `setnote`, `getnote`, `back` and so on.

## There is a twist

Okay, "twist" is just an euphemism for a bug here. But it's a deliberately placed bug, that we will use to demonstrate how fuzzing can be useful for finding programmer mistakes. In order to trigger this bug, you need to navigate to a "secret" password protected menu. Since we don't want anyone to know the password, it is encrypted with the old (but proven) Caesar cipher. With the correct password, we could go ahead and delete a note twice, to trigger a double-free:

```
$ nc 127.0.0.1 5000
Please enter your name:
> Henrik
Welcome Henrik!

[MAIN MENU]
setnote: Save a note in the system
getnote: Print the saved note
secret: Access the super secret special menu
quit: Exit the system
> setnote

Please enter your note:
> something something
Note saved!

[MAIN MENU]
setnote: Save a note in the system
getnote: Print the saved note
secret: Access the super secret special menu
quit: Exit the system
> secret

Please enter the password for the secret menu:
> N0TSo5Ecr3T
Correct!

[SECRET MENU]
delnote: Delete a saved note
back: Go back to main menu
> delnote

Really delete? (y/n)
> y
It's gone!

[SECRET MENU]
delnote: Delete a saved note
back: Go back to main menu
> delnote

Really delete? (y/n)
> y
```

```
free(): double free detected in tcache 2
Aborted
```

## Trying it yourself

You can build the simple note server and test it yourself by entering the following commands in the top level directory of this repository:

```
mkdir build
cd build
cmake ..
make simple_note_server
```

After that, you can execute the binary you just built: `build/c_cpp/network_socket/tcp_server/simple_note_server` and connect to it with netcat `nc 127.0.0.1 5000`.

## Can a fuzzer find this bug?

Let's go ahead and find out. If you're using CI Fuzz, you can simply create a new project and enter the build commands above for "Build Script Content". Then create a new fuzz test and select "Network Socket Fuzz Test". Choose an arbitrary name and the following settings:
- Binary: simple_note_server
- Socket Type: TCP
- Socket Port: 5000

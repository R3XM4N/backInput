## Temporary Description
# Purpose:
BackInput is a linux only "virtual device process" made using uinput on linux. It enables another app or a process to request to manage virtual devices and make them provide input to the host operating system. Can be used for something like user interaction in systems or even games. 
# How:
"Background process" that runs in background and after recieving a "formated" unix socket does what it is ordered to do.
## Visualization of unix socket format full:
!["Protocol" Diagram](images/protocol.svg)
## Visualization of unix socket system section:
!["System bytes" Diagram](images/system_bytes.svg)
## Visualization of unix socket for keyboard device:
!["Keyboard byte" Diagram](images/keyboard.svg)
## Visualization of unix socket for mouse device:
!["Mouse bytes" Diagram](images/mouse.svg)
## Visualization of unix socket for controller device:
!["Controller bytes" Diagram](images/controller.svg)

## All of readme and codebase is subject to change project is major work in progress
## Some if not all of a protocol may be changed in a future to reduce or increase amount of data transfered

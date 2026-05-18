## Temporary Description
# Purpose:
BackInput is a linux only "virtual device process" made using uinput on linux. It enables another app or a process to request or manage virtual devices. These virtual devices can provide input to the host operating system. Can be used for something like user interaction inside a system or even automated game interaction. 
# How:
This program/process by default runs in the background after getting started/launched and waits/listens for unix sockets formated in the programs "format" which it takes as instructions
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

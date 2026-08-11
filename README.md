# BackInput
BackInput is a linux background service/process that allows to make fake devices and make them input data.

### Currently supported
* Basic input support for keyboards/mice/controllers with hold support

### Planned not yet implemented

🟡 Implementing ability to queue inputs on devices  
🟠 Implementing system instructions for device management  
🟠 Macro mode  
🟠 Keyboard shift flag support  
🟠 Custom device creation support  
🔴 Allowing multiple devices at the same time  
🔴 Allowing multiple clients at the same time  

## Technical side

### Structuring

BackInput is built by using linux uinput.h contents and uses C++ classes to represent devices for easy management of multiple devices

### Instruction formating
instructions are formatted as 2 "messages" header and instructions allowing dynamic size of instruction messages (currently 0-255 bytes of instruciton data)  
🚧 Here will be an example on a specific instruction  
Document with visual and exact information about each message formatting wil be avaible 🚧 [here](https://docs.google.com/spreadsheets/d/11CYEagxPeg7P89zb0fGu7jK0ob86kyr2BpnqTimfETE/edit?usp=sharing)

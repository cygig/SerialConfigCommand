# SerialConfigCommand
SerialConfigCommand for Arduino allows user to issue commands, with or without values via the Serial Monitor easily. Example: "LED=255", "Lock=1", "Start". Uses Arduino String() class instead of character array, which will be useful for beginners.
The library checks the Serial buffer every x interval defined by the user, and parse the input into commands and values.

Users can enter an assigment or non-assigment command.
Assignment command: <command>=<value> (eg num1=10). 
Non-assignment command: just <command> (eg sum), getValue returns 0, hasValue() returns false.

User can then compare the command string or value integer in the callback function to dictate further actions.

New Line and Carriage Return from the Serial Monitor will be filtered out so no need to fiddle with the Serial Monitor line ending settings

# Installation
Download the codes, unzip it, copy `SerialConfigCommand` folder into your Arduino library folder, for example `C:\Users\you\Documents\Arduino\libraries`.

# Public Functions
## SerialConfigCommand()
Constructor.

## void set(void (*myFunction)())
Setup the instance by defining the name of the callback function. The period is by default set to 300ms (ie the instance check for updates in the Serial Monitor every 300ms.

## void set(unsigned long myPeriod,void (*myFunction)())
Setup the instant by definining the period (how often the instance checks for updates from the Serial Monitor) and the name of the callback function.

## void set(unsigned long myTimer,unsigned long myPeriod,void (*myFunction)())
Similar to the above two, but you get to set the starting time used to compared to how many milliseconds passed while running the program.

## void reset()
Resets the timer.

## void disable()
Disables core functionalities of this instance of SerialConfigCommand.

## void enable()
Enables core functionalities of this instance of SerialConfigCommand.

## void update()
This function has to be put in loop();

## void setInterval(unsigned long myPeriod)
Set the period.

## String getCmd()
Returns a string of the current command.

## String getValue()
Returns a string of the value of the current command. Default to 0 if command has no value.

## int getValueInt()
Returns the value of the current command as an integer.

## bool hasValue()
Returns true if the current command has a value.

/*
SerialConfigCommand 0.4 by cygig
SerialConfigCommand is an easy way to adjust configurations via the Serial monitor. 
The library checks the Serial buffer every x interval defined by the user, and parse the input into commands and values.
Users can enter an assigment or non-assigment command.
Assignment command: <command>=<value> (eg num1=10). 
Non-assignment command: just <command> (eg sum), getValue returns 0, hasValue() returns false.
Checks by comparing Strings and Int can be done in the callback function using the parsed commands and values to dictate further actions.
*/

#ifndef SERIALCONFIGCOMMAND
#define SERIALCONFIGCOMMAND

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


class SerialConfigCommand {
  
  public:
    SerialConfigCommand();
    void set(void (*myFunction)());	
  	void set(unsigned long myPeriod,void (*myFunction)());
  	void set(unsigned long myTimer,unsigned long myPeriod,void (*myFunction)());
  	void reset();
  	void disable();
  	void enable();
  	void update();
	  void setInterval(unsigned long myPeriod);
    String getCmd();
    String getValue();
    int getValueInt();
    bool hasValue();

    

  private:
    (*callback_Function)(); 
    bool active;
    unsigned long timer;
    unsigned long period;
    String trimNLCR (String input);
    void parseCmd(String input);
    void clearSetting();
    String cmd="";
    String value="";
    int valueInt=0; // Stores the int version of the string 
    bool cmdHasValue=false; // Decides if the command is assigment(has value) or non-assignment(no value)
    
    
};

#endif

#include "SerialConfigCommand.h"

SerialConfigCommand::SerialConfigCommand(){
// Empty Constructor
}

void SerialConfigCommand::set(void (*myFunction)()){
  // Assigns user input into privates
  active = true;
  timer = 0;
  period = 300; //Defaults to 300ms if period is not set
  callback_Function = myFunction; 
}

void SerialConfigCommand::set(unsigned long myPeriod,void (*myFunction)()){
  // Assigns user input into privates
  active = true;
	timer = 0;
	period = myPeriod;
	callback_Function = myFunction;	
}



void SerialConfigCommand::set(unsigned long myTimer,unsigned long myPeriod,void (*myFunction)()){
  // Assigns user input into privates
  active = true;
	period = myPeriod;
	timer = myTimer;  // Custom starting time
	callback_Function = myFunction;	
}



void SerialConfigCommand::reset(){
  timer = millis();
}



void SerialConfigCommand::disable(){
  active = false;
}



void SerialConfigCommand::enable(){
  active = true;
}



void SerialConfigCommand::setInterval(unsigned long myPeriod){
  period = myPeriod;
}



String SerialConfigCommand::getCmd(){
  return cmd;  
}



String SerialConfigCommand::getValue(){
  return value;  
}



int SerialConfigCommand::getValueInt(){
  return valueInt;  
}



bool SerialConfigCommand::hasValue(){
  return cmdHasValue;  
}


void SerialConfigCommand::update(){

  // Make sure active and timer overflowed millis()
  if ( active && ((unsigned long)(millis()-timer) >= period) ) {

    // Do not check for input if nothing is available on Serial
    if (Serial.available() > 0){
      
      // Reset all settings to default 
      clearSetting();
      
      // Empty string to store incoming message
      String msg = "";

      // Convert each incoming btye to char and add to string till no longer avail
      while (Serial.available()){
        msg += char(Serial.read());
      }
      
      // Parse msg then executes user specified function (ie do stuff on certain commands or values)
      parseCmd(msg);
      callback_Function();

    }
    
	  timer = millis(); // Reset timer
    
  }
}



String SerialConfigCommand::trimNLCR(String input){
  // Find positions of NL and CR, -1 if no string found
  int CR = input.indexOf("\r");
  int LN = input.indexOf("\n");

  // If both found, delete two chars
  if (CR>=1 && LN >=1) {
    //Serial.println("Trimmed CR and LN");
    return input.substring(0, input.length()-2);
  }

  // If only one found, delete one char
  else if (CR>=1 || LN >=1){
    //Serial.println("Trimmed CR or LN");
    return input.substring(0, input.length()-1); 
  }

  // If none found, just return the original string
  else {
    return input;
  } 

  /* Substring Reference
   * 0 1 2 3 4 5 6 7
   * H E L L O r n
   * len=7
   */
}



void SerialConfigCommand::parseCmd(String input){
    // Find the position of the equal sign
    int sep = input.indexOf("=");

    // If there is an equal sign, assign command and value    
    if (sep>0){
      input=trimNLCR(input); // Trim away NL and RC from serial monitor
      cmd=input.substring(0, sep); //Extract part from beginning before equal sign
      
      int len = input.length(); // Find the length of input
      value = input.substring(sep+1, len); // Extract the part from equal sign to end
      
      valueInt = value.toInt(); //value but in int
      
      cmdHasValue=true; //Indicate this command has value;
    } 

    // if not, command is the the input after trimming. Value remainds default(0).
    else {
      cmd=trimNLCR(input);
    }
    
/* Substring Reference
 *  0 1 2 3 4 5 6 7 8
 *  H E L L 0 = 1 0
 *  len=8, sep=5  
 */ 
}


// Resets everything to default
void SerialConfigCommand::clearSetting(){
  cmd="";
  value="";
  valueInt=0;
  cmdHasValue=false;
}

#include <ShiftRegister74HC595.h>
#include "RTClib.h"

RTC_DS1307 rtc;

// Parameters: <number of shift registers> (data pin, clock pin, latch pin)
ShiftRegister74HC595<1> srHrs(3, 4, 5);
ShiftRegister74HC595<1> srMins(6, 7, 8);
 
void setup() {
  
  while (!Serial); // wait for serial port to connect. Needed for native USB
  Serial.begin(57600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //Set RTC time
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void displayBinaryHours(int lDigit, int rDigit){
  for (int i =0;i<4;i++) {
    //Set left Digit
    if (bitRead(lDigit, i) == 1) { //Read digit[i] as bit
      srHrs.set(i + 4, 1); // Shift 4 bits for left digit
    } else {
      srHrs.set(i + 4, 0); // Shift 4 bits for left digit
    }
    //Set right digit
    if (bitRead(rDigit, i) == 1) { //Read digit[i] as bit
      srHrs.set(i, 1); 
    } else {
      srHrs.set(i, 0);
    }
   }
}

void displayBinaryMinutes(int lDigit, int rDigit){
  for (int i =0;i<4;i++) {
    //Set left Digit
    if (bitRead(lDigit, i) == 1) { //Read digit[i] as bit
      srMins.set(i + 4, 1); // Shift 4 bits for left digit
    } else {
      srMins.set(i + 4, 0); // Shift 4 bits for left digit
    }
    //Set right digit
    if (bitRead(rDigit, i) == 1) { //Read digit[i] as bit
      srMins.set(i , 1);
    } else {
      srMins.set(i, 0);
    }
   }
}
  
void loop() {
  DateTime now = rtc.now();

  srHrs.setAllLow();
  srMins.setAllLow();
  
  // Seperate digits and convert to binary
  if (now.hour() >= 10) {
    displayBinaryHours(now.hour() / 10, now.hour() % 10); // Seperate digits and convert to binary
  } else {
    displayBinaryHours(0, now.hour());
  }
  // Seperate digits and convert to binary
  if (now.minute() >= 10) {
    displayBinaryMinutes(now.minute() / 10, now.minute() % 10); 
  } else {
    displayBinaryMinutes(0, now.minute());
  }

  // Clock to serial for debugging
  Serial.print(srHrs.get(7));
  Serial.print(srHrs.get(6));
  Serial.print(srHrs.get(5));
  Serial.print(srHrs.get(4));
  Serial.print(" ");
  Serial.print(srHrs.get(3));
  Serial.print(srHrs.get(2));
  Serial.print(srHrs.get(1));
  Serial.print(srHrs.get(0));

  Serial.print(" : ");

  Serial.print(srMins.get(7));
  Serial.print(srMins.get(6));
  Serial.print(srMins.get(5));
  Serial.print(srMins.get(4));
  Serial.print(" ");
  Serial.print(srMins.get(3));
  Serial.print(srMins.get(2));
  Serial.print(srMins.get(1));
  Serial.println(srMins.get(0));

   delay(500);
}

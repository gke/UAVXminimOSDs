/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * Please see eeprom_iteration for a more in depth
 * look at how to traverse the EEPROM.
 *
 * This example code is in the public domain.
 */
 
 #include <EEPROM.h>

void setup() {
  
     Serial.begin(57600);
     
  // initialize the LED pin as an output.
  pinMode(13, OUTPUT);
 
  /***
    Iterate through each byte of the EEPROM storage.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - Arduno Duemilanove: 512b EEPROM storage.
    - Arduino Uno:        1kb EEPROM storage.
    - Arduino Mega:       4kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/

  for (int i = 0 ; i < 1024 ; i++) {
    EEPROM.write(i, 0);
    Serial.println( i);
  }

  // turn the LED on when we're done
  digitalWrite(13, HIGH);
}

void loop() {
  Serial.println("Done ");
  /** Empty loop. **/
}
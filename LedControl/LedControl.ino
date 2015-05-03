#include "LedControl.h" 

int fsrPin = 4;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider

// Arduino Pin 7 to DIN, 6 to Clk, 5 to LOAD, no.of devices is 1 
LedControl lc=LedControl(7,6,5,1); 

void setup() 
{ 
	// Initialize the MAX7219 device 
	lc.shutdown(0,false); 	// Enable display 
	lc.setIntensity(0,15); 	// Set brightness level (0 is min, 15 is max) 
	lc.clearDisplay(0); 	// Clear display register 
	Serial.begin(9600);   	// Using the serial monitor

} 

void loop() 
{ 
	fsrReading = analogRead(fsrPin);  
	Serial.print(fsrReading);     // the raw analog reading;
 	Serial.print('\n');
 

	lc.setDigit(0,0,fsrReading / 1000,true); // Display 4 to Digit 4, and turn DP on 
	fsrReading = fsrReading % 1000;
	lc.setDigit(0,1,fsrReading/100,true); // Display 3 to Digit 3, " " 
	fsrReading = fsrReading % 100;
	lc.setDigit(0,2,fsrReading/10,true); // Display 2 to Digit 2, " " 
	fsrReading = fsrReading % 10;
	lc.setDigit(0,3,fsrReading/1,true); // Display 1 to Digit 1, " " 
	lc.setDigit(0,4,3,true); // Turns L1, L2, and L3 on 
	delay(1000); 
} 
// What is the 
// FAT structure 
// Mass storage systems 
// rate  0 1 4 5 6
// What are the key things rate should deliver 
// DMA
// Protection/ access matrix
// Pay attention to memory and storage part

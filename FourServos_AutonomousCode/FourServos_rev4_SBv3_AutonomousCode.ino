
// Definet the libaries to use 
#include <Servo.h>

/// Link the Servos to the servo lib
Servo base;
Servo arm;
Servo wrist;
Servo clamp;

/// Input handelers
int  base_val  = 60;
int  arm_val   = 50;    
int  wrist_val = 0;
int  clamp_stop = 90; // Should be set to no motion position
int  clamp_val = clamp_stop; 

String read_str;            // Char array to store the input
int  str_pos      = 0;       // Position on the index
long new_val      = 0;       // The value to read from
int  max_angle    = 180;     // Limit the range of motion
int  motor_select = 0;       // Select the servo to rotate
int i = 0;

/// Switch & sensors handelers
int  FSR          = 0;       // Select the input pin for the pressure sensor
int  limitS3      = 3;       // Input for the analog switch 
int  limitS4      = 4;       // Input for the analog switch


//TODO: check is switch_pressed can go? nope

bool switch_pressed = false; // Help to release the switch 

// Allocate memory to remember the previous values and reset to starting point

//Initialize Current Position Variables
int BasePos = base_val;
int ArmPos = arm_val;
int WristPos = wrist_val;


/// Initialize the program 
// Runs only once
void setup() {
    Serial.begin(9600); // Startup the serial interface

    // Attach the servos
    base. attach(6);
    arm.  attach(8);
    wrist.attach(9);
    clamp.attach(10);
}

/// The main loop, runs as long as the Arduino is connected
void loop() {
    /// continuesly reading the input from the switchs
    int FSRread = analogRead(FSR);
    //int ls1     = analogRead(limitS1); 
    //int ls2     = analogRead(limitS2); 
    int ls3     = analogRead(limitS3); 
    int ls4     = analogRead(limitS4); 
    
    int del = 3000/50;
    
    base.write(base_val);
    arm.write(arm_val);
    wrist.write(wrist_val);
    clamp.write(clamp_stop);
    
  if( i < 1 ){
    
    
   while (arm_val < 155){
     arm_val = arm_val + 1;
     arm.write(arm_val);
     delay(del);
   }
   
   while (base_val > 0){
     base_val = base_val - 1;
     base.write(base_val);
     delay(del);
   }
   
   while (wrist_val < 50){
     wrist_val = wrist_val + 1;
     wrist.write(wrist_val);
     delay(del);
   }
   
   while (base_val < 45){
     base_val = base_val +1;
     base.write(base_val);
     delay(del);
   }
    
   while (arm_val > 50){
     arm_val = arm_val - 1;
     arm.write(arm_val);
     delay(del);
   }
               ls3     = analogRead(limitS3);
              if (ls3 > 300) { 
                 Serial.println("Lower");
                 clamp.write(70);
                 digitalWrite(3, HIGH);
                 delay(1000);
                 clamp.write(clamp_stop);
                 clamp_val = clamp_stop;       
                 
             ls4     = analogRead(limitS4);  
            }else if (ls4 > 300) {   // Lower switchs are pressed
                 clamp.write(110);
                 digitalWrite(3, HIGH);
                 delay(1000);
                 clamp.write(clamp_stop);
                 clamp_val = clamp_stop; 
            }
   clamp.write(80);
   
               ls3     = analogRead(limitS3);
              if (ls3 > 300) { 
                 Serial.println("Lower");
                 //Serial.println(ls3);
                 clamp.write(70);
                 digitalWrite(3, HIGH);
                 delay(1000);
                 clamp.write(clamp_stop);
                 clamp_val = clamp_stop;   
                 
              ls4     = analogRead(limitS4);   
            }else if (ls4 > 300) {   // Lower switchs are pressed
                //Serial.println("Upper");1:90
                //Serial.println(ls4);
                 clamp.write(110);
                 digitalWrite(3, HIGH);
                 delay(1000);
                 clamp.write(clamp_stop);
                 clamp_val = clamp_stop; 
            }
   delay(4000);
   
   
   
   while(arm_val < 100){
     arm_val = arm_val + 1;
     arm.write(arm_val);
     delay(del);
   }
   
   while(base_val < 100) {
     base_val = base_val + 1;
     base.write(base_val);
     delay(del);
   }
   
       clamp.write(100);
       delay(3000);
  i++;
    
  }
 
               ls3     = analogRead(limitS3);
              if (ls3 > 300) { 
                 Serial.println("Lower");
                 //Serial.println(ls3);
                 clamp.write(70);
                 digitalWrite(3, HIGH);
                 delay(1000);
                 clamp.write(clamp_stop);
                 clamp_val = clamp_stop;   
                 
              ls4     = analogRead(limitS4);   
            }else if (ls4 > 300) {   // Lower switchs are pressed
                //Serial.println("Upper");1:90
                //Serial.println(ls4);
                 clamp.write(110);
                 digitalWrite(3, HIGH);
                 delay(1000);
                 clamp.write(clamp_stop);
                 clamp_val = clamp_stop; 
            }
 
 
    base.write(base_val);
    arm.write(arm_val);
    wrist.write(wrist_val);
    clamp.write(clamp_val);
    
    
    // Serial.print("FSR Value: "); Serial.print(FSRread); Serial.print('\n');
    delay(25);  

}



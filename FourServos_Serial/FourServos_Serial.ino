
// Definet the libaries to use 
#include <Servo.h>

/// Link the Servos to the servo lib
Servo base;
Servo arm;
Servo wrist;
Servo clamp;

/// Input handelers
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
//int  base_val  = 90;
//int  arm_val   = 50;    
//int  wrist_val = 0;
int  base_val  = 0;
int  arm_val   = 140;    
int  wrist_val = 0;
int  clamp_stop = 90; // Should be set to no motion position
int  clamp_val = clamp_stop; 

//Initialize Current Position Variables
int BasePos = base_val;

/// Initialize the program 
// Runs only once
void setup() {
    Serial.begin(9600); // Startup the serial interface

    // Attach the servos
    base. attach(6);
    arm.  attach(8);
    wrist.attach(9);
    clamp.attach(10);

    Serial.println("Select desired servo, followed by the angle: \n1)Base \n2)Arm \n3)Wrist \n4)Clamp ");
    Serial.println("For example: '1:130' will move servo #1 in 130 degrees\n");
}

/// The main loop, runs as long as the Arduino is connected
void loop() {
    /// continuesly reading the input from the switchs
    int FSRread = analogRead(FSR);
    //int ls1     = analogRead(limitS1); 
    //int ls2     = analogRead(limitS2); 
    int ls3     = analogRead(limitS3); 
    int ls4     = analogRead(limitS4); 

    /// Input handler
    /* We expect a string of form #:###, where the first number is the servo
     * number and the digits are the position of the servo. The sequence is
     * terminated by a single newline or carriage return.
     */
    if (Serial.available()) {
        bool valid = true;
        int servoId = Serial.parseInt(); //Read Servo
        if (Serial.read() != '.') valid = false; //Read separator
        Serial.print("Motor ID: "); Serial.println(servoId);
        int position = Serial.parseInt(); //Read Position
        if (Serial.read() != '\n') valid = false; //Read Terminator
        Serial.print("Position: "); Serial.println(position);
        
        
        //Do something with the input:
        if (valid && (position >= 0 && position <= 180)) {
          switch (servoId) {
            case 1:     
              BasePos = base.read();
           
               if (BasePos < position){
                  while(BasePos < position){
                        BasePos = BasePos + 1;
                        Serial.println(BasePos);
                        base_val = BasePos;
                        delay(25); 
                        base.write(base_val);
                  }
               }
               if (BasePos > position){
                  while(BasePos > position){
                       BasePos = BasePos - 1;
                       Serial.println(BasePos);
                       base_val = BasePos; 
                       delay(25); 
                       base.write(base_val);

                 }
                        }
               break;
            case 2:
              arm_val = position;
              break;
            case 3:
              position=position/4;
              wrist_val = position;
              break;
            case 4:
              if (position == 90)
              //digitalWrite(3, HIGH);
              digitalWrite(3, LOW);
              else
              digitalWrite(3, HIGH);
              //digitalWrite(3, LOW);
              clamp_val = position;
              break;
            default:
              //Error! Invalid servo
              break;
          }
        }
    }
    if (ls3 > 300) { 
         Serial.println("Lower");
         //Serial.println(ls3);
         clamp.write(70);
         digitalWrite(3, HIGH);
         delay(1000);
         clamp.write(clamp_stop);
         clamp_val = clamp_stop;         
         
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
    

    //Serial.println();    
    
    
    // Serial.print("FSR Value: "); Serial.print(FSRread); Serial.print('\n');
    delay(25);  

}



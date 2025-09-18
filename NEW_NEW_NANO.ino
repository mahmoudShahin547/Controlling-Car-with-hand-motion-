#include <SoftwareSerial.h>
#include "MPU9250.h"
#include <Wire.h>

SoftwareSerial btSerial(2, 3); // RX=2 (unused), TX=3 → HC-05 RX
MPU9250 mpu;

// Movement command codes
#define FORWARD_LEFT     0
#define FORWARD_RIGHT    1
#define BACKWARD_LEFT    2
#define BACKWARD_RIGHT   3
#define FORWARD          4
#define BACKWARD         5
#define STOP             6
#define FLEX             A3
int Direction = 0;
int Move = 0;
int speed = 0;
int last_spd = -1 ;
int last_cmd = -1 ;
void setup() {
  Serial.begin(38400);   // Debug monitor
  btSerial.begin(38400); // HC-05 data mode baud rate
  Serial.println("Nano BT Master ready @ 38400");
  pinMode (FLEX, INPUT);
  Wire.begin();  
  delay(2000);
  
  if (!mpu.setup(0x68)) {
    while (1) {
      Serial.println("MPU connection failed.");
      delay(5000);
    }
  }
}
void loop() {
  speed = analogRead(FLEX);  
  speed = map(speed, 720 , 900 , 0, 255); // scale 0–1023 → 0–255

  if (mpu.update()) {
    static uint32_t prev_ms = millis();
    if (millis() - prev_ms > 25) {
      int cmd = getMovementCommand();  

      // --- Send packet: [0xFF, cmd, speed] ---
  // start marker'

    
   if (last_cmd != cmd || last_spd >= (speed + 15) || last_spd <= (speed - 15))
      {
        btSerial.write(cmd);   // command
      btSerial.write(speed); // speed 
      Serial.print("Sent cmd: ");
      Serial.print(cmd);
      Serial.print(" | speed: ");
      Serial.println(speed);
      last_spd=speed;
      last_cmd=cmd;
      }
      prev_ms = millis();
    }
  }
}


int getMovementCommand() {
  Direction = mpu.getRoll();
  Move = mpu.getPitch();
  int command = STOP;

  if (Move > 30) { 
    if (Direction > 30) command = FORWARD_RIGHT;
    else if (Direction < -30) command = FORWARD_LEFT;
    else if (Direction > -10 && Direction < 10) command = FORWARD;
  } 
  else if (Move < -30) { 
    if (Direction > 30) command = BACKWARD_RIGHT;
    else if (Direction < -30) command = BACKWARD_LEFT;
    else if (Direction > -10 && Direction < 10) command = BACKWARD;
  }
  return command;
}
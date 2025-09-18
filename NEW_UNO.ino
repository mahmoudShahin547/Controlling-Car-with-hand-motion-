#include <SoftwareSerial.h>

SoftwareSerial btSerial(10, 11); // RX=10 ← HC-05 TX, TX=11 unused
// Movement command codes
#define FORWARD_LEFT     0
#define FORWARD_RIGHT    1
#define BACKWARD_LEFT    2
#define BACKWARD_RIGHT   3
#define FORWARD          4
#define BACKWARD         5
#define STOP             6

//MOTOR I/O
#define IN1              7
#define IN2              6
#define IN3              4
#define IN4              5
#define ENA              3
#define ENB              9

 int speed = 0 ;
 int flex_speed =100;
 int command = -1;
 int value = -1;

void setup() {
  Serial.begin(38400);   // Debug monitor
  btSerial.begin(38400); // HC-05 data mode baud rate
  Serial.println("Uno BT Slave ready @ 38400");
pinMode (ENA, OUTPUT); // pwm signal en a     right tires
pinMode (ENB, OUTPUT); // pwm signal en b     left tires 
pinMode (IN1, OUTPUT);   //in1 left tires
pinMode (IN2, OUTPUT);   //in2 left tires
pinMode (IN3, OUTPUT);   //in3 right tires
pinMode (IN4, OUTPUT);   //in4 right tires



}

void loop() {
  while (btSerial.available()) {

      value = btSerial.read();   // second byte = command
      // flex_speed = btSerial.read();// third byte = speed
      if(value > 6){
        flex_speed = value;
      }else if(value <= 6 && value >= 0){
        command = value;
      }

      Serial.print("Received cmd: ");
      Serial.print(command);
      Serial.print(" | speed: ");
      Serial.println(flex_speed);
    
  }

  switch (command) {
    case FORWARD_LEFT:   left();    break;
    case FORWARD_RIGHT:  right();   break;
    case BACKWARD_LEFT:  left();    break;
    case BACKWARD_RIGHT: right();   break;
    case FORWARD:        forward(); break;
    case BACKWARD:       back();    break;
    case STOP:           stop();    break;
    default: break;
  }
}


void printCommand(int cmd) {
 switch (cmd) {
    case FORWARD_LEFT:   Serial.println(FORWARD_LEFT); break;
    case FORWARD_RIGHT:  Serial.println(FORWARD_RIGHT); break;
    case BACKWARD_LEFT:  Serial.println(BACKWARD_LEFT); break;
    case BACKWARD_RIGHT: Serial.println(BACKWARD_RIGHT); break;
    case FORWARD:        Serial.println(FORWARD); break;
    case BACKWARD:       Serial.println(BACKWARD); break;
    case STOP:           Serial.println(STOP); break;
    default:             Serial.print("Unknown: "); Serial.println(cmd); break;
  }
  
}

void forward() 
{
  digitalWrite (IN1 , LOW);
  digitalWrite (IN2 , HIGH);
  digitalWrite (IN3 , LOW);
  digitalWrite (IN4 , HIGH);
  analogWrite (ENA , flex_speed );
  analogWrite (ENB , flex_speed );
}

void back() 
{
  digitalWrite (IN1 , HIGH);
  digitalWrite (IN2 , LOW);
  digitalWrite (IN3 , HIGH);
  digitalWrite (IN4 , LOW);
  analogWrite (ENA , flex_speed );
  analogWrite (ENB , flex_speed );
}

void left() 
{
  digitalWrite (IN1 , HIGH);
  digitalWrite (IN2 , LOW);
  digitalWrite (IN3 , LOW);
  digitalWrite (IN4 , HIGH);
  analogWrite (ENA , flex_speed );
  analogWrite (ENB , flex_speed );
}



void right() 
{
  digitalWrite (IN1 , LOW);
  digitalWrite (IN2 , HIGH);
  digitalWrite (IN3 , HIGH);
  digitalWrite (IN4 , LOW);
  analogWrite (ENA , flex_speed );
  analogWrite (ENB , flex_speed );
}

void stop() 
{
  digitalWrite (IN1 , LOW);
  digitalWrite (IN2 , LOW);
  digitalWrite (IN3 , LOW);
  digitalWrite (IN4 , LOW);
  analogWrite (ENA , flex_speed );
  analogWrite (ENB , flex_speed );
}

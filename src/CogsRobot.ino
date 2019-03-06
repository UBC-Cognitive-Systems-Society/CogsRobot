/*
 * Project CogsRobot
 * Description: Driver code for COGS/EML Workshop
 * Author: Abel Waller
 * Date: March 2, 2019
 */
#include <HC_SR04/HC_SR04.h>


#define MOTOR_A_1A 0
#define MOTOR_B_1A 1
#define MOTOR_A_1B 2
#define MOTOR_B_1B 3

#define LEFT_ECHO 4
#define LEFT_TRIG 5

#define FRONT_ECHO 6
#define FRONT_TRIG 7

HC_SR04 leftRange = HC_SR04(LEFT_TRIG, LEFT_ECHO);
HC_SR04 frontRange = HC_SR04(FRONT_TRIG, FRONT_ECHO);

int rInit = 160;
int lInit = 160;

int rSpeed = rInit;
int lSpeed = lInit;

double ratio = rInit/lInit;

int ldistance;
int fdistance;


// setup() runs once, when the device is first turned on.
void setup() {
   pinMode(MOTOR_A_1A, OUTPUT);
   pinMode(MOTOR_A_1B, OUTPUT);
   pinMode(MOTOR_B_1A, OUTPUT);
   pinMode(MOTOR_B_1B, OUTPUT);

   Particle.variable("left distance", &ldistance, INT);
   Particle.variable("front distance", &fdistance, INT);
   Particle.variable("speed", &lSpeed, INT);

   Particle.function("move", moverobot);
   Particle.function("sonar", sonarbehavior);
   Particle.function("set speed", setSpeed);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  ldistance = leftRange.getDistanceCM();
  fdistance = frontRange.getDistanceCM();

}

int sonarbehavior(String extra){
  sonarMovement();
  return 0;
}

int setSpeed(String speed){
  lSpeed = atoi(speed);
  rSpeed = (int) lSpeed * ratio;
}

int moverobot(String command){
  if(command == "forward"){
    forward();
    return 0;
  } else if(command == "back"){
    back();
    return 0;
  } else if(command == "left"){
    left();
    return 0;
  } else if(command == "right"){
    right();
    return 0;
  } else{
    stop();
    return 0;
  }
}

void sonarMovement(){
   ldistance = leftRange.getDistanceCM();
   fdistance = frontRange.getDistanceCM();
   if(fdistance < 15){   // something in front
    if(ldistance < 25){ //wall on the left side
      stop();
      delay(500);
      back();
      delay(500);
      right();
      delay(1000);
    }else{              //no wall on the left side
      back();
      delay(500);
      left();
      delay(1000);
    }
  }else{ // nothing in front
    if(ldistance > 30){
        stop();
        delay(500);
        right();
        delay(1000);
        forward();
        delay(1000);
    }else{
       forward();
    }
  }
}

void back() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, rSpeed);
          analogWrite(MOTOR_A_1B, 0);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, lSpeed);
          analogWrite(MOTOR_B_1B, 0);
}
void forward() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, 0);
          analogWrite(MOTOR_A_1B, rSpeed);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, 0);
          analogWrite(MOTOR_B_1B, lSpeed);
}
void left() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, 0);
          analogWrite(MOTOR_A_1B, rSpeed);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, lSpeed);
          analogWrite(MOTOR_B_1B, 0);
}
void right() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, rSpeed);
          analogWrite(MOTOR_A_1B, 0);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, 0);
          analogWrite(MOTOR_B_1B, lSpeed);
}
void stop() {
          //LEFT MOTOR
          analogWrite(MOTOR_A_1A, 0);
          analogWrite(MOTOR_A_1B, 0);
          //RIGHT MOTOR
          analogWrite(MOTOR_B_1A, 0);
          analogWrite(MOTOR_B_1B, 0);
}

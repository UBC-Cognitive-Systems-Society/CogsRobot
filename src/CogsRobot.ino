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

#define RIGHT_ECHO 6
#define RIGHT_TRIG 7

HC_SR04 leftRange = HC_SR04(LEFT_TRIG, LEFT_ECHO);
HC_SR04 rightRange = HC_SR04(RIGHT_TRIG, RIGHT_ECHO);

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}

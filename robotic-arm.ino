
#include <VarSpeedServo.h>


const byte DEFAULT_SPEED = 30;

const int crawServoPin = 6;
const int baseServoPin = 9;
const int elevatorServoPin = 10;
const int armServoPin = 11;
VarSpeedServo crawServo;
VarSpeedServo baseServo;
VarSpeedServo elevatorServo;
VarSpeedServo armServo;

void setup() {
  Serial.begin(9600);
  crawServo.attach(crawServoPin);
  baseServo.attach(baseServoPin);
  elevatorServo.attach(elevatorServoPin);
  armServo.attach(armServoPin);

  crawServo.write(50, DEFAULT_SPEED, false);
  baseServo.write(90, DEFAULT_SPEED, false);
  elevatorServo.write(140, DEFAULT_SPEED, false);
  armServo.write(70, DEFAULT_SPEED, false);
}

void loop() {
  if (Serial.available()) {
    // axis  angle  speed  block
    // B     090    030    0
    // B0900300 -> move Base 90 degree assynchronous

    char axis = Serial.read();
    // skip end of line and space
    if (axis != '\n' && axis != ' ') {
      int angle = readInt();
      int speed = readInt();
      boolean block = readBoolean();

      VarSpeedServo *servo;

      if ('B' == axis) {
        servo = &baseServo;
      } else if ('E' == axis) {
        servo = &elevatorServo;
      } else if ('C' == axis) {
        servo = &crawServo;
      } else if ('A' == axis) {
        servo = &armServo;        
      }

      servo->write(angle, speed, block);
      Serial.print('1');
    }
  }
}

int readInt() {
  while (!Serial.available());
  int v1 = Serial.read();
  while (!Serial.available());
  int v2 = Serial.read();
  while (!Serial.available());
  int v3 = Serial.read();
  
  int value = (v1 - 48) * 100;
  value += (v2 - 48) * 10;
  value += (v3 - 48);

  return value;
}

boolean readBoolean() {
  while (!Serial.available());
  return '1' == Serial.read();
}

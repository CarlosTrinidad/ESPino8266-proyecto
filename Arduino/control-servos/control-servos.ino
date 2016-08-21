#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int pos1 = 0;    // variable to store the servo position1
int pos2 = 0;    // variable to store the servo position2
int pos3 = 0;    // variable to store the servo position3

void controlServo1(int angle) {
  servo1.write(angle);
  delay(15);
}
void controlServo2(int angle) {
  servo2.write(angle);
  delay(15);
}
void controlServo3(int angle) {
  servo3.write(angle);
  delay(15);
}

void setup() {
// FALTA MIN y MAX
  servo1.attach(9);  // attaches the servo1 on pin 10 to the servo object. HS-645mg /cafe
  servo2.attach(10);  // attaches the servo2 on pin 11 to the servo object /verde 
  servo3.attach(11);  // attaches the servo3 on pin 12 to the servo object /azul: 45 - 160

  // TEMP
  Serial.begin(115200);

}

void loop(){
  while (Serial.available() == 0);
  int val = Serial.parseInt(); //read int or parseFloat for ..float...
  Serial.println(val);

  //controlServo1(val);
  //controlServo2(val);
  controlServo1(val);

}

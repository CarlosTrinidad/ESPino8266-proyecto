#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

int pos1 = 0;    // variable to store the servo position1
int pos2 = 0;    // variable to store the servo position2
int pos3 = 0;    // variable to store the servo position3

// Request disponibles http://192.168.173.115/?pin=13

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
  servo1.attach(10);  // attaches the servo1 on pin 10 to the servo object
  servo2.attach(11);  // attaches the servo2 on pin 11 to the servo object
  servo3.attach(12);  // attaches the servo3 on pin 12 to the servo object

  // TEMP
  Serial.begin(115200);

}

void loop(){
// TEMP
	while (Serial.available() == 0);
	int val = Serial.parseInt(); //read int or parseFloat for ..float...
	Serial.println(val);

	//controlServo1(val);
	//controlServo2(val);
	controlServo3(val);



 // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
	int start, end;
	start = req.indexOf('?');
	end = req.indexOf('=');

	if(req.substring(start,end == "?motor1=")){
		pos1 = req.substring(end+1).toInt();
		controlServo1(pos1);
	}else if(req.substring(start,end == "?motor2=")){
		pos2 = req.substring(end+1).toInt();
		controlServo2(pos2);
	}else if(req.substring(start,end == "?motor3=")){
		pos3 = req.substring(end+1).toInt();
		controlServo2(pos3);
	}  else {
	    Serial.println("invalid request");
	    client.stop();
	    return;
	}
  
  client.flush(); //Discard any bytes that have been written to the client but not yet read.

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");


}
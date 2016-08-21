#include <Servo.h>
#include <ESP8266WiFi.h>

const char* ssid = "your-ssid";
const char* password = "your-password";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);


Servo servo1;
Servo servo2;
Servo servo3;

int pos1 = 0;    // variable to store the servo position1
int pos2 = 0;    // variable to store the servo position2
int pos3 = 0;    // variable to store the servo position3
String dir4 = "";    // variable to store the direction of motor 4
String dir5 = "";    // variable to store the  direction of motor 5

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
void controlMotor4(String dir) {
  if (dir == "izq")
  {
    // Establece direccion
    digitalWrite(3, 1);
    digitalWrite(4, 0);
    // Habilita el puente H
    digitalWrite(2, 1);
    delay(15);
    // Deshabilita el puente H
    digitalWrite(2, 0);
  }else{
    // Establece direccion
    digitalWrite(3, 0);
    digitalWrite(4, 1);
    // Habilita el puente H
    digitalWrite(2, 1);
    delay(15);
    // Deshabilita el puente H
    digitalWrite(2, 0);
  }
}
void controlMotor5(String dir) {
  if (dir == "izq")
  {
    // Establece direccion
    digitalWrite(6, 1);
    digitalWrite(7, 0);
    // Habilita el puente H
    digitalWrite(5, 1);
    delay(15);
    // Deshabilita el puente H
    digitalWrite(5, 0);
  }else{
    // Establece direccion
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    // Habilita el puente H
    digitalWrite(5, 1);
    delay(15);
    // Deshabilita el puente H
    digitalWrite(5, 0);
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);
// FALTA MIN y MAX
  servo1.attach(10);  // attaches the servo1 on pin 10 to the servo object CAFE 
  servo2.attach(11, 553, 2520);  // attaches the servo2 on pin 11 to the servo object VERDE
  servo3.attach(12, 553, 2520);  // attaches the servo3 on pin 12 to the servo object AZUL 45-160
// Prepara pin Enable
  pinMode(2, OUTPUT); //Enable Motor 4
  pinMode(5, OUTPUT); //Enable Motor 5
// Prepara pin direction for motor 4
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT);
// Prepara pin direction for motor 5
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT);
  //Inicializa todo en 0 logico
  digitalWrite(2, 0);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);
  digitalWrite(7, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop(){

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

  if(req.substring(start,end) == "?motor1="){
    pos1 = req.substring(end+1).toInt();
    controlServo1(pos1);
  }else if(req.substring(start,end) == "?motor2="){
    pos2 = req.substring(end+1).toInt();
    controlServo2(pos2);
  }else if(req.substring(start,end) == "?motor3="){
    pos3 = req.substring(end+1).toInt();
    controlServo3(pos3);
  }else if(req.substring(start,end) == "?motor4="){
    dir4 = req.substring(end+1);
    controlMotor4(dir4);
  }else if(req.substring(start,end) == "?motor5="){
    dir5 = req.substring(end+1);
    controlMotor5(dir5);
  }  else {
      Serial.println("invalid request");
      client.stop();
      return;
  }
  
  client.flush(); //Discard any bytes that have been written to the client but not yet read.

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");


}

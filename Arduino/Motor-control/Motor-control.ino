#include <Servo.h>
#include <ESP8266WiFi.h>

const char* ssid = "TRINIDAD";
const char* password = "Trinidad428";

// Create an instance of the server
// specify the port to listen on as an argument


 Servo servo1;
 Servo servo2;
 Servo servo3;

WiFiServer server(80);

int pinServo1 = 16;
int pinServo2 = 14;
int pinServo3 = 12;
int enable1 = 5;
int enable2 = 2;
int dirm4_1 = 3;
int dirm4_2 = 15;
int dirm5_1 = 13;
int dirm5_2 = 4;

int pos1 = 0;    // variable to store the servo position1
int pos2 = 0;    // variable to store the servo position2
int pos3 = 0;    // variable to store the servo position3
String dir4 = "";    // variable to store the direction of motor 4
String dir5 = "";    // variable to store the  direction of motor 5

// // Request disponibles http://192.168.173.115/?pin=13

void controlServo1(int angle) {
  servo1.write(angle);
  delay(15);
  return;
}
void controlServo2(int angle) {
  servo2.write(angle);
  delay(15);
  return;
}
void controlServo3(int angle) {
  servo3.write(angle);
  delay(15);
  return;
}
void controlMotor4(String dir) {
  if (dir == "izq")
  {
    // Establece direccion
    digitalWrite(dirm4_1, HIGH);
    digitalWrite(dirm4_2, LOW);
    // Habilita el puente H
    digitalWrite(enable1, HIGH);
    delay(500);
    // Deshabilita el puente H
    digitalWrite(enable1, LOW);
    digitalWrite(dirm4_1, LOW);
    digitalWrite(dirm4_2, LOW);
  }else{
    // Establece direccion
    digitalWrite(dirm4_1, LOW);
    digitalWrite(dirm4_2, HIGH);
    // Habilita el puente H
    digitalWrite(enable1, HIGH);
    delay(500);
    // Deshabilita el puente H
    digitalWrite(enable1, LOW);
    digitalWrite(dirm4_1, LOW);
    digitalWrite(dirm4_2, LOW);
  }
  return;
}
void controlMotor5(String dir) {
  if (dir == "izq")
  {
    // Establece direccion
    digitalWrite(dirm5_1, HIGH);
    digitalWrite(dirm5_2, LOW);
    // Habilita el puente H
    digitalWrite(enable2, HIGH);
    delay(500);
    // Deshabilita el puente H
    digitalWrite(enable2, LOW);
    digitalWrite(dirm5_1, LOW);
    digitalWrite(dirm5_2, LOW);
  }else{
    // Establece direccion
    digitalWrite(dirm5_1, LOW);
    digitalWrite(dirm5_2, HIGH);
    // Habilita el puente H
    digitalWrite(enable2, HIGH);
    delay(500);
    // Deshabilita el puente H
    digitalWrite(enable2, LOW);
    digitalWrite(dirm5_1, LOW);
    digitalWrite(dirm5_2, LOW);
  }
  return;
}

void setup() {

// FALTA MIN y MAX
  servo1.attach(pinServo1);  // attaches the servo1 on pin 10 to the servo object CAFE 
  servo2.attach(pinServo2, 553, 2520);  // attaches the servo2 on pin 11 to the servo object VERDE
  servo3.attach(pinServo3, 553, 2520);  // attaches the servo3 on pin 12 to the servo object AZUL 45-160
// Prepara pin Enable
  pinMode(enable1, OUTPUT); //Enable Motor 4
  pinMode(enable2, OUTPUT); //Enable Motor 5
// Prepara pin direction for motor 4
  pinMode(dirm4_1, OUTPUT); 
  pinMode(dirm4_2, OUTPUT);
// Prepara pin direction for motor 5
  pinMode(dirm5_1, OUTPUT); 
  pinMode(dirm5_2, OUTPUT);
// Inicializa todo en 0 logico
  digitalWrite(enable1, LOW);
  digitalWrite(enable1, LOW);
  digitalWrite(dirm4_1, LOW);
  digitalWrite(dirm4_2, LOW);
  digitalWrite(dirm5_1, LOW);
  digitalWrite(dirm5_2, LOW);
  

   Serial.begin(115200);
   delay(10);
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
  int startR, endR;
  startR = req.indexOf('?');
  endR = req.indexOf('=')+1;
  Serial.println(req.substring(startR,endR));

  if(req.substring(startR,endR) == "?motor1="){
    pos1 = req.substring(endR).toInt();
    controlServo1(pos1);
      Serial.println(pos1);

  }else if(req.substring(startR,endR) == "?motor2="){
    pos2 = req.substring(endR).toInt();
    controlServo2(pos2);
          Serial.println(pos2);

  }else if(req.substring(startR,endR) == "?motor3="){
    pos3 = req.substring(endR).toInt();
    controlServo3(pos3);
          Serial.println(pos3);

  }else if(req.substring(startR,endR) == "?motor4="){
    dir4 = req.substring(endR);
              Serial.println(dir4);

    controlMotor4(dir4);

  }else if(req.substring(startR,endR) == "?motor5="){
    dir5 = req.substring(endR);
          Serial.println(dir5);

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

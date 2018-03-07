//include libraries
#include <SoftwareSerial.h>

SoftwareSerial esp8266(1,0); //RX pin = 3, TX pin = 2

#define DEBUG true //show messages between ESP8266 and Arduino in serial port

//define motor pins
const int motor1Pin1 = 5;
const int motor1Pin2 = 6;
const int motor2Pin1 = 10;
const int motor2Pin2 = 11;

const int enable1 = 4;
const int enable2 = 9;

int motorSpeed1 = 150; //motor speed (PWM)
int motorSpeed2 = 250; // tried to balance the power of the motors 

//*****
//SETUP
//*****
void setup()
{
  //set pin modes
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable1,OUTPUT);
  pinMode(enable2,OUTPUT);
  analogWrite(enable1,motorSpeed1);
  analogWrite(enable2,motorSpeed2);
  
  
  //start communication
  //Serial.begin(9600);
  esp8266.begin(9600); 
  
  sendData("AT+RST\r\n", 2000, DEBUG); //reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //set station mode
  sendData("AT+CWJAP=\"UPCFD83269\",\"dwxpjvx8vRkr\"\r\n", 2000, DEBUG); //connect wi-fi network (replace XXXXX by your Wi-Fi router SSID and YYYYY by its password
  
  delay(2000); //wait for connection

  sendData("AT+CIFSR\r\n", 1000, DEBUG); //show IP address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //allow multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // start web server on port 80
}

//*********
//MAIN LOOP
//*********
void loop()
{
  
  if (esp8266.available())  //verify incoming data
  {
    if (esp8266.find("+IPD,")) //if there is a message
    {
      String command = getCommand();
      changeDirection(command);
    }
  }
}
   
String getCommand()
{
  esp8266.find("?"); // look for the message
  String msg = esp8266.readStringUntil(' '); // read the message
  String command = msg.substring(0,3); // first 3 characers = command;
  esp8266.println(command);
  return command;
}
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout ) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
void changeDirection(String command)
{     // move forward
    if(command == "cm1") {
      digitalWrite(motor1Pin1,HIGH);
      digitalWrite(motor2Pin1,HIGH);
      digitalWrite(motor1Pin2,LOW);
      digitalWrite(motor2Pin2,LOW);
      }

      //move backward
    if(command == "cm2") {
      digitalWrite(motor1Pin1,LOW);
      digitalWrite(motor2Pin1,LOW);
      digitalWrite(motor1Pin2,HIGH);
      digitalWrite(motor2Pin2,HIGH);
      }

      //turn right
    if(command == "cm3") {
      digitalWrite(motor1Pin1,HIGH);
      digitalWrite(motor2Pin1,LOW);
      digitalWrite(motor1Pin2,LOW);
      digitalWrite(motor2Pin2,LOW);
       }
       
       //turn left
    if(command == "cm4") {
      digitalWrite(motor1Pin1,LOW);
      digitalWrite(motor2Pin1,HIGH);
      digitalWrite(motor1Pin2,LOW);
      digitalWrite(motor2Pin2,LOW);
       }

       //do nothing       
    if(command == "cm5") {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
       }
}

  





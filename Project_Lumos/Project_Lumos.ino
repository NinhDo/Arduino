#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

Servo myservo;

int pos = 0;

char ssid[15];
char password[15];
IPAddress ip(192,168,1,151);
IPAddress gateway(129,241,136,1);
IPAddress subnet(255,255,255,0);

//int status = WL_IDLE_STATUS;

unsigned int localPort = 2390;
char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "RogerRoger";       // a string to send back
char pa[] = "on";
char av[] = "off";
WiFiUDP Udp;

void setup(void){
  myservo.attach(D2);
  delay(1000);
  Serial.begin(115200);
  Serial.println("\nChange network?");
  delay(5000);
  if (Serial.available()){
    String ans = Serial.readString();
    Serial.println(ans);
    Serial.println("SSID:");
    while (Serial.available()==0){
      //wait
    }
    String ssidTmp = Serial.readString();
    Serial.println("Password:");
    while (Serial.available()==0){
      //wait
    }
    String passwordTmp = Serial.readString();
    Serial.print("SSID:"+ssidTmp+"Passord:"+passwordTmp);

    ssidTmp.trim();
    passwordTmp.trim();
    
    ssidTmp.toCharArray(ssid, sizeof(ssidTmp));
    passwordTmp.toCharArray(password, sizeof(passwordTmp));
  }
  WiFi.begin(ssid, password);
  //WiFi.config(ip, gateway, subnet);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("....Connecting.....");
  }
  Serial.println("");
  Serial.print("Connected to ");
  //String str(ssid);
  Serial.println(WiFi.SSID()); //ssid
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Port: ");
  Serial.println(+localPort);

  
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  Udp.begin(localPort);
}

void loop(void){
int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();

    if (strcmp(packetBuffer,pa) == 0){
      myservo.write(45);
      delay (1000);
      myservo.write(90);
    }
    if (strcmp(packetBuffer,av) == 0){ 
      myservo.write(135);
      delay (1000);
      myservo.write(90);
    }
    if (strcmp(packetBuffer,"test") == 0){ 
      myservo.write(135);
      delay (1000);
      myservo.write(90);
      delay (1000);
      myservo.write(45);
      delay (1000);
      myservo.write(90);
    }
    /*if (strcmp(packetBuffer,av) == 0){
      //change ssid and password
      //divide strcmp?
      //include this via serial, wifi may not work
    }
    */
  }
 
}




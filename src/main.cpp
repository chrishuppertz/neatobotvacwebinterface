#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//#define CONNECT_TIMEOUT_SECS 30 // Timeout time for connecting to the access point

#define SSID "SSID_OF_YOUR_NETWORK"
#define SSID_PASSWORD "PASSWORD_OF_YOUR_NETWORK"
#define CLIENT_ID "NAME_OF_THE_BOTVAC"

ESP8266WebServer server (80); // WebServer to connect to

/**
 * @brief: Will answer if the node is up an running
 * 
 * If an enpoint is triggerd that is not implemented an error page is displayed showing the wrong input paramters. 
 */
void status()
{
  server.send(200, "text/html", "OK");
}

/**
 * @brief: Send a command to the robot and reads an incomming serial from the reboot
 * 
 * After a command is send to the robot a return value is send to the serial interface. 
 * This function reads outgoing message and sends it as answer as text/html. 
 */
void execCommand()
{
  if (server.args() == 1)
  {
    if (server.argName(0) == "command")
    {
      Serial.println(server.arg(0));
      String answer = Serial.readString();
      server.send(200, "text/html", answer);
    }
    else
    {
      status();
    }
  }
  else
  {
    status();
  }
}

void setup()
{
  // botvac serial console is 115200 baud, 8 data bits, no parity, one stop bit (8N1)
  Serial.begin(115200);

  /*
  * SETUP WIFI
  */
  WiFi.begin(SSID, SSID_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  /*
  * SETUP MDS
  */
  if (!MDNS.begin(CLIENT_ID))
  {
    ESP.reset(); // if MDNS fail => restart and try over
  }

  /*
  * SETUP SERVER
  */
  server.on("/", HTTP_GET, status);
  server.on("/exec", HTTP_GET, execCommand);
  server.onNotFound(status);
  server.begin();
}

// General Arduino loop  routine
void loop()
{
  server.handleClient();
  delay(1);
}

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <confidential.h>
#include <AsyncUDP_WT32_ETH01.h>

#define UDP_REMOTE_PORT 60000

const char *ssid = confidential::ssid;         // Change this to your WiFi SSID
const char *password = confidential::password; // Change this to your WiFi password
const int udpServerPort = 60000;

// char magicmac[] = confidential::magicmac[];

bool isPermutation(char *str1, char *str2, int size)
{

  for (int i = 0; i < size; ++i)
  {
    if (str1[i] != str2[i])
      return false;
  }

  return true;
}

WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  delay(10000);
  // Send broadcast on port UDP_REMOTE_PORT = 1234
  udp.broadcastTo("Anyone here?", UDP_REMOTE_PORT);
  delay(1000);
}
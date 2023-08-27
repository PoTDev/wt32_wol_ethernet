#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <confidential.h>

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

  // Set WiFi to station mode and disconnect from an AP if it was Previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  udp.begin(udpServerPort); // Инициализация UDP для приема данных
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    // Прием данных по UDP
    int packetSize = udp.parsePacket();
    if (packetSize)
    {
      Serial.println(packetSize);
      char incomingPacket[255];
      int len = udp.read(incomingPacket, 6);
      if (len > 0)
      {
        incomingPacket[len] = 0;
        Serial.printf("Получено сообщение: %s\n", incomingPacket);
        Serial.printf(incomingPacket);
        Serial.printf(confidential::magicmac);
        // проверка мака на волшебный пакет. пока что только первые 6 байт
        if (isPermutation(incomingPacket, confidential::magicmac, 6))
        {
          Serial.println("Magic mac");
        }
      }
    }
  }
  delay(1000);
}
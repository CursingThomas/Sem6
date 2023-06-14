#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <RingBuf.h>

#include "Reading.h"

String URL = "http://i466372.hera.fhict.nl/connect.php";

Reading sensorReading;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
struct tm timeinfo;
RingBuf<Reading, 1000> buffer;
WiFiMulti wifiMulti;
int retriesConnection = 0;

void setupWifiCreds()
{
  wifiMulti.addAP("Internet", "");
  wifiMulti.addAP("Test", "Test1234");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
}

void printLocalTime()
{
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  setupWifiCreds();
  wifiMulti.run();

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("No usable adresses were found");
  }

}

void setup() {
  Serial.begin(115200);
  connectWiFi();
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("Connected");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getLocalTime(&timeinfo);

    Serial.print("WIFI network was found, time is setup");
    Serial.println("Current time is:");
    printLocalTime();
    
  } else {
    Serial.println("WIFI network was not found, no timestamps will be created.");
  }

  sensorReading.speed = 10;
  sensorReading.rpm = 1000;
  sensorReading.oilTemperature = 65;
  sensorReading.timeStamp = timeinfo;

}

void loop() {
  if (timeinfo.tm_year != 0)
    {
      printLocalTime();
    }
  if(WiFi.status() != WL_CONNECTED) 
  {
    sensorReading.timeStamp = timeinfo;
    buffer.push(sensorReading);
     Serial.println(&sensorReading.timeStamp, "%A, %B %d %Y %H:%M:%S");
    Serial.println(buffer.size());
    Serial.println("No internet, data stored in buffer");
    delay(1000);
  }
  if(WiFi.status() == WL_CONNECTED) 
  {
    if (buffer.isEmpty() == false)
    {
      while(buffer.isEmpty() == false)
      {
        Reading tempObject;
        buffer.pop(tempObject);
        String date = "0";
        if (tempObject.timeStamp.tm_year != 0)
        {  
          printLocalTime();
          String year = String(tempObject.timeStamp.tm_year);
          year.remove(0,1);
          date = ("20" + year + "-" + String((tempObject.timeStamp.tm_mon + 1)) + "-" + String(tempObject.timeStamp.tm_mday) + "_" + String(tempObject.timeStamp.tm_hour) + ":" + String(tempObject.timeStamp.tm_min) + ":" + String(tempObject.timeStamp.tm_sec));
        }

        String postData = "oilTemperature=" + String(tempObject.oilTemperature) + "&rpm=" + String(tempObject.rpm) + "&speed=" + String(tempObject.speed) + "&timestamp=" + date;
        HTTPClient http;
        http.begin(URL);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
        int httpCode = http.POST(postData);
        String payload = http.getString();

        Serial.print("URL : "); Serial.println(URL); 
        Serial.print("Data: "); Serial.println(postData);
        Serial.print("httpCode: "); Serial.println(httpCode);
        Serial.print("payload : "); Serial.println(payload);
        Serial.println("--------------------------------------------------");
      }

    } else {
      String date = "0";
      if (timeinfo.tm_year != 0)
      {  
        printLocalTime();
        String year = String(timeinfo.tm_year);
        year.remove(0,1);
        date = ("20" + year + "-" + String((timeinfo.tm_mon + 1)) + "-" + String(timeinfo.tm_mday) + "_" + String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min) + ":" + String(timeinfo.tm_sec));
      }
      String postData = "oilTemperature=" + String(sensorReading.oilTemperature) + "&rpm=" + String(sensorReading.rpm) + "&speed=" + String(sensorReading.speed) + "&timestamp=" + date;
      HTTPClient http;
      http.begin(URL);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      
      int httpCode = http.POST(postData);
      String payload = http.getString();

      Serial.print("URL : "); Serial.println(URL); 
      Serial.print("Data: "); Serial.println(postData);
      Serial.print("httpCode: "); Serial.println(httpCode);
      Serial.print("payload : "); Serial.println(payload);
      Serial.println("--------------------------------------------------");  
    }
  }

  delay(1000);

  retriesConnection++;
  if (retriesConnection >= 50)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      connectWiFi();
    }    
    retriesConnection = 0;
  }  
}

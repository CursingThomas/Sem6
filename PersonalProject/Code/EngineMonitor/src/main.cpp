#include <WiFi.h>
#include <HTTPClient.h>
#include <RingBuf.h>

#include "Reading.h"

String URL = "http://i466372.hera.fhict.nl/connect.php";

const char* ssid = "Interne"; 
const char* password = "TLE9009tle"; 
Reading sensorReading;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
struct tm timeinfo;
RingBuf<Reading, 1000> buffer;

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
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
for (int i = 0; i <= 10; i++) 
  {
    WiFi.begin(ssid, password);
    if (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
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
  //new data has been gathered
  buffer.push(sensorReading);
  Serial.println(buffer.size());
  if (timeinfo.tm_year != 0)
  {
    printLocalTime();
  }
  

  if(WiFi.status() == WL_CONNECTED) 
  {
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

  delay(1000);
  
}

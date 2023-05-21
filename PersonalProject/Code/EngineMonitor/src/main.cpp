#include <Arduino.h>
// #include <Temperature/ITemperature.h>
// #include <RingBuf.h>
// #include "time.h"
// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <HTTPClient.h>

// /*const char* ssid       = "Internet";
// const char* password   = "TLE9009tle";
// const char* ntpServer = "pool.ntp.org";

// const long  gmtOffset_sec = 3600;
// const int   daylightOffset_sec = 3600;
// struct tm timeinfo;
// //RingBuf<> offlineBuffer;

// void setup() 
// {
//   Serial.begin(115200);

//   Serial.printf("Connecting to %s ", ssid);
//   WiFi.begin(ssid, password);
//   int tries;
//   for (int i = 0; WiFi.status() != WL_CONNECTED; i++) {
//     delay(500);
//     Serial.print(".");
//   }

//   if (WiFi.status() == WL_CONNECTED)
//   {
//     Serial.print("Wifi Connected");
//     configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    
//     getLocalTime(&timeinfo);
//     WiFi.disconnect(true);
//     WiFi.mode(WIFI_OFF);
//   }
// }
// void printLocalTime()
// {
//   Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
// }

// void loop() 
// {
//   delay(500);
//   printLocalTime();
//   Serial.print('x');
// }*/

// // REPLACE with your Domain name and URL path or IP address with path
// const char* serverName = "http://i466372.hera.fhict.nl/post-esp-data.php";

// // Keep this API Key value to be compatible with the PHP code provided in the project page. 
// // If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
// String apiKeyValue = "tPmAT5Ab3j7F9";

// const char* ssid       = "Internet";
// const char* password   = "TLE9009tle";

// const char* ntpServer = "pool.ntp.org";
// const long  gmtOffset_sec = 3600;
// const int   daylightOffset_sec = 3600;
// struct tm timeinfo;

// void printLocalTime()
// {
  
//   if(!getLocalTime(&timeinfo)){
//     Serial.println("Failed to obtain time");
//     return;
//   }
//   Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
// }

// void setup()
// {
//   Serial.begin(115200);
  
//    Serial.printf("Connecting to %s ", ssid);
   

//   for (int i = 0; i <= 10; i++) 
//   {
//     WiFi.begin(ssid, password);
//     if (WiFi.status() != WL_CONNECTED)
//     {
//       delay(500);
//       Serial.print(".");
//     }
//   }

//   if (WiFi.status() == WL_CONNECTED)
//   {
  
//     //init and get the time
//     configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
//     getLocalTime(&timeinfo);

//     //disconnect WiFi as it's no longer needed
//     //WiFi.disconnect(true);
//     //WiFi.mode(WIFI_OFF);
//     Serial.print("WIFI network was found, time is setup");
//     Serial.println("Current time is:");
//     printLocalTime();
    
//   } else {
//     Serial.println("WIFI network was not found, no timestamps will be created.");
//   }
// }

// void loop()
// {
//   //getsensorinfo
//   if (WiFi.status() == WL_CONNECTED)
//   {
//     WiFiClientSecure *client = new WiFiClientSecure;
//     client->setInsecure(); //don't use SSL certificate
//     HTTPClient http;
    
//     // Your Domain name with URL path or IP address with path
//     http.begin(*client, serverName);
    
//     // Specify content-type header
//     //https.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
//     // Prepare your HTTP POST request data
//     //String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + "xy"
//     //                      + "&location=" + "XX" + "&value1=" + String(1)
//     //                     + "&value2=" + String(2) + "&value3=" + String(3) + "";
//     //Serial.print("httpRequestData: ");
//     //Serial.println(httpRequestData);
    
//     // You can comment the httpRequestData variable above
//     // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
//     String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

//     // Send HTTP POST request
//     int httpResponseCode = http.POST(httpRequestData);
     
//     // If you need an HTTP request with a content type: text/plain
//     //https.addHeader("Content-Type", "text/plain");
//     //int httpResponseCode = https.POST("Hello, World!");
    
//     //If you need an HTTP request with a content type: application/json, use the following:
//     //client->setInsecure(); //don't use SSL certificate
//     //http.addHeader("Content-Type", "application/json");
//     //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
    
//     if (httpResponseCode>0) {
//       Serial.print("HTTP Response code: ");
//       Serial.println(httpResponseCode);
//     }
//     else {
//       Serial.print("Error code: ");
//       Serial.println(httpResponseCode);
//     }
//     // Free resources
//     http.end();
//   }
//   else {
//     Serial.println("WiFi Disconnected");
//   } 
//   delay(5000);
// }

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  
}
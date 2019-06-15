
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <HTTPClient.h>
int fsrPin = 35;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int prevReading= 1100;
int iszero= 0;
int quantity=0;



//const char* ssid = "tr\"IO\"";
const char* ssid = "shweta";
//const char* password = "7033144375";
const char* password = "shweta04";

String host2 = "http://13.56.250.165:8000/glass/savestate";

//DeviceAddress sensor1 = { 0x28, 0xBA, 0x18, 0x79, 0x97, 0x20, 0x3, 0xDE };

void setup() {
   Serial.begin(9600);
   
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

void loop(void){ 
  
   fsrReading = analogRead(fsrPin);  
 
  //Serial.print("Analog reading = ");
 // Serial.print(fsrReading);     // the raw analog reading
 

 /*
  if (fsrReading == 0) {
    Serial.println(" - No pressure");
  } else if (fsrReading < 10) {
    Serial.println(" - Light touch");
  } else if (fsrReading < 50) {
    Serial.println(" - Light squeeze");
  } else if (fsrReading < 150) {
    Serial.println(" - Medium squeeze");
  } else {
    Serial.println(" - Big squeeze");
  }*/
  if(fsrReading==0)
  {
    delay(20000);
    Serial.println("Zero so 10 sec delay");
    Serial.print("While loop Analog reading = ");
  Serial.println(fsrReading);
  }
 else if ( prevReading-fsrReading > 150 && fsrReading!=0)
  {
    quantity += prevReading-fsrReading;
    prevReading=fsrReading;
    Serial.print("Quantity loop Analog reading = ");
  Serial.println(fsrReading);
  Serial.print("Water quantity drank is ");
  Serial.print(quantity);
  Serial.println("ml");
    delay(20000);
  }
  else if (fsrReading>prevReading+50)
  {
    prevReading=fsrReading;
    Serial.print("Refill loop Analog reading = ");
  Serial.println(fsrReading);
    Serial.println("Looks like water has been filled");
    delay(10000);
  }
  else {Serial.println("None executed");
  delay(10000);
}


 pushTempDataToServer(fsrReading, quantity);
 delay(1000);
}

void pushTempDataToServer(float C, float d1){

  String slash = "/";
  
  String pressure = String(C);
  String q1 = String(d1);
  String host = host2 + slash + pressure + slash + q1;

  Serial.print("Connecting to ");
  Serial.println(host);

  HTTPClient http;   
   http.begin(host);  //Specify destination for HTTP request
   
   http.addHeader("Content-Type", "text/plain"); 

   int httpResponseCode = http.POST("Hi");   //Send the actual POST request
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
  }

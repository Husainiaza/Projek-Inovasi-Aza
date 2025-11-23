/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/

//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <WiFi.h>
#include <MQTT.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

#define relay01     6  // digital OUTPUT - RELAY 1
#define relay02     7  // digital OUTPUT - RELAY 2
#define buzzer      0  // digital OUTPUT - BUZZER
#define sensorLDR   2  // analog INPUT   - Sensor Cahaya
#define DHTPIN      5     
#define TRIG_PIN    20 // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN    21 // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin

#define sensor1      1  
#define sensor3      3 
#define sensor4      4   
#define sensor10     10 

// pin 8(sda) dan pin 9(scl) untuk komunikasi I2C

#define DHTTYPE     DHT22
//---Penentuan Saiz Skrin OLED --
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "id_anda___ESP32c3"
#define NamaBroker  "broker.emqx.io"
//#define namaSSID    "IoT";
//#define SSIDpwd     "iot@kksj2023";
#define namaSSID    "Haza@unifi";
#define SSIDpwd     "0135335045";
// ~~~~~~~~~~~~~~~~~~~  TAMMAT   ~~~~~~~~~~~~~~~~~~~~~~~

//-----c.  - ISTIHAR  constant dan pembolehubah------------------------------
//---Penetapan nama Pembolehubah yg diumpukkan kepada satu nilai awal  --
const char ssid[] = namaSSID;
const char pass[] = SSIDpwd;

float humid;
float temp ;
float distance_cm;
int dataLDR;
float lux;
//char statusRLY1[3];
String statusRLY1 ="OFF";
String statusRLY2 ="OFF";
//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;

//-----d. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;

DHT dht(DHTPIN, DHTTYPE);

// Istihar objek bagi Module OLED Display - SSD1306
Adafruit_SSD1306 paparOled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


//##################  Seksyen 1 - TAMAT #############################
//--------------FUNCTION----------------------------

void connect() {
  Serial.print("sambungan ke wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.print("sambungan WiFi berjaya ..... ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Print the IP address

  Serial.print("sambungan ke broker MQTT : ");
  Serial.println(NamaBroker);

  Serial.print("\nconnecting...");
  while (!client.connect(Client_Id)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("topicAnda/buzzer");
  client.subscribe("topicAnda/relay1");
  client.subscribe("topicAnda/relay2");
  // -- tambah subcribe disini ---
 
}

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
   Serial.println(payload);
  
  //   ----Tulis Kod Kawalan ( subsribe here ) ---------------------
  //==========================Buzzer Control ========================
     if(String(topic) == "topicAnda/buzzer") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(buzzer,HIGH);
      Serial.println("Buzzer ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(buzzer,LOW);
        Serial.println("Buzzer OFF");
        
      }
  } 
  //==========================Relay 1 Control ========================
 
  if(String(topic) == "topicAnda/relay1") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay01,LOW);
      Serial.println("socket1 ON");
       statusRLY2 = "ON ";
      Serial.println(statusRLY2);
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay01,HIGH);
        Serial.println("socket1 OFF");
        statusRLY2 = "OFF";
        Serial.println(statusRLY2);
      }
  }

  //==========================Relay 2 Control ========================

   if(String(topic) == "topicAnda/relay2") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay02,LOW);
      Serial.println("socket2 ON");
      statusRLY1 = "ON ";
      Serial.println(statusRLY1);
  
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay02,HIGH);
        Serial.println("socket2 OFF");
        statusRLY1 = "OFF";
        Serial.println(statusRLY1);
     
      }
  }

  //--------------------------- END --------------------
}

//###################################################
//==================  Seksyen 2 - Fungsi Setup ======================
//-------------------------------------------------------------------

void setup() {
  pinMode(relay01,OUTPUT);
  pinMode(relay02,OUTPUT);
  pinMode(buzzer,OUTPUT); 
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

 
  Serial.begin(115200); // initialize serial
  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);
  connect();

  dht.begin();

   if(!paparOled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  paparOled.clearDisplay();
  paparOled.setTextSize(1);
  paparOled.setTextColor(WHITE);
  paparOled.setCursor(0,0);
  paparOled.println("--- ESP32C3- MINI ---");
  paparOled.setCursor(0,10);
  paparOled.println("K. Komuniti Sbg Jaya");
  paparOled.setCursor(0,20);
  paparOled.println("--------------------");
  paparOled.display();
  delay(100);


}
//##################  Seksyen 2 - TAMAT #############################

//==============  Seksyen 3 - Fungsi Utama (LOOP) ===================
//-------------------------------------------------------------------
void loop() {

 client.loop();
 delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

// publish a message roughly every second.
  if (millis() - lastMillis > 2000) {
  lastMillis = millis();

  //------SENSOR 1 -------------------------------------------------------------
    
  int dataLDR = analogRead(sensorLDR);
  Serial.print("Cahaya: ");
  Serial.println(dataLDR);  

  lux = dataLDR * (3.3 / 4095.0) / 10000.0 * 1000000.0 / 2.0;
  Serial.print("LUX : ");
  Serial.println(lux);  

  client.publish("topicAnda/ldr", String(dataLDR));   

 //------SENSOR 2 -------------------------------------------------------------
   humid = dht.readHumidity();
   temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(humid);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C ");

  client.publish("topicAnda/suhu", String(temp));  
  client.publish("topicAnda/humid", String(humid));  

 //------SENSOR 2 -------------------------------------------------------------
  jarak();
 
 //-----------end ----------------------------------
   paparanOled();
  }
}

void paparanOled() {
//------DISPLAY OLED   -----------------------------------------------------------

  paparOled.clearDisplay();
  paparOled.setTextSize(1);
  paparOled.setTextColor(WHITE);
  paparOled.setCursor(0,0);
  paparOled.println("--- ESP32C3- MINI ---");
  paparOled.setCursor(0,10);
  paparOled.println("K. Komuniti Sbg Jaya");
  paparOled.setCursor(0,20);
  paparOled.println("--------------------");
  paparOled.display();
  paparOled.setCursor(0,30);
  paparOled.print("HUM: ");
  paparOled.print(humid,0);
  paparOled.setCursor(60,30);
  paparOled.print("TEMP: ");
  paparOled.print(temp,1);
  paparOled.setCursor(0,40);
  paparOled.print("JRK: ");
  paparOled.print(distance_cm,0);
  paparOled.setCursor(60,40);
  paparOled.print("LUX : ");
  paparOled.print(lux,1);
  paparOled.setCursor(0,50);
  paparOled.print("RLY1: ");
  paparOled.print(statusRLY1);
  paparOled.setCursor(60,50);
  paparOled.print("RLY2: ");
  paparOled.print(statusRLY2);
  paparOled.display();
}

void jarak() {
  //float duration_us, distance_cm;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;


  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  client.publish("kon1/jarak", String(distance_cm));
}

//##################  Seksyen 3 - TAMAT #############################

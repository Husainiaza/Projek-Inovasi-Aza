/*------------------------------------------------------------------
  ===================  Seksyen 1 - HEADER        ===================
  ------------------------------------------------------------------*/

//-------------------------------------------------------------------
//=  A. - Library  include and define  yang diperlukan              =
//-------------------------------------------------------------------

#include <WiFi.h>
#include <MQTT.h>
#include <Adafruit_NeoPixel.h>
#include "DHT.h"

//--------------------------------------------------------------------------
//-----b. - ISTIHAR Sambungan nama Pin dengan Nombor Fizikal PIN ----
//--------------------------------------------------------------------------

#define relay01     26  // digital OUTPUT - RELAY 1
#define relay02     27  // digital OUTPUT - RELAY 2
#define buzzer      25  // digital OUTPUT - BUZZER
#define SensorDS18  15  // pin ke DS18B20 (ONEWIRE) sensor Suhu
#define sensorLDR   34  // analog INPUT   - Sensor Cahaya
#define sensorTilt  4   // digital Input  - Sensor Tilt
#define sensorVolt  35  // analog INPUT   - Sensor Voltan

#define TRIG_PIN 22 // ESP32 pin GPIO23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 21 // ESP32 pin GPIO22 connected to Ultrasonic Sensor's ECHO pin

#define DHTPIN 33     
#define DHTTYPE DHT21


#define PIN       5
#define NUMPIXELS 30 // Popular NeoPixel ring size
#define DELAYVAL 100 // Time (in milliseconds) to pause between pixels

// ~~~~~~~~~~~~~~~~~~~~ PENTING ~~~~~~~~~~~~~~~~~~~~~~~~
// ------ Sila edit nama atau ID ikut keperluan --------
#define Client_Id   "id_anda___"
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

//------ ISTIHAR Pemboleh ubah dengan jenis Data yang digunakan---
unsigned long lastMillis = 0;
int suisKon;
//-----d. - Cipta Objek dari Librari berkaitan------------------ ----
//--------------------------------------------------------------------------

WiFiClient net;
MQTTClient client;

DHT dht(DHTPIN, DHTTYPE);

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


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
  client.subscribe("kon1/buzzer");
  client.subscribe("kon1/relay1");
  client.subscribe("kon1/relay2");
    client.subscribe("kon1/ledMerah");
  client.subscribe("kon1/ledBiru");
  client.subscribe("kon1/ledAmber");
  client.subscribe("kon1/ledMagenta");
  client.subscribe("kon1/ledTurquoise");
  client.subscribe("kon1/ledWhite");
  client.subscribe("kon1/ledHijau");
  // -- tambah subcribe disini ---
 
}

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);
   Serial.println(payload);
  
  //   ----Tulis Kod Kawalan ( subsribe here ) ---------------------
  //==========================Buzzer Control ========================
     if(String(topic) == "kon1/buzzer") 
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
 
  if(String(topic) == "kon1/relay1") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay01,HIGH);
      Serial.println("socket1 ON");
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay01,LOW);
        Serial.println("socket1 OFF");
      }
  }

  //==========================Relay 2 Control ========================

   if(String(topic) == "kon1/relay2") 
  {
      if(payload =="on")
      {
      Serial.println(payload);
      digitalWrite(relay02,HIGH);
      Serial.println("socket2 ON");
  
      }
      
      else if(payload =="off")
      {
        Serial.println(payload);
        digitalWrite(relay02,LOW);
        Serial.println("socket2 OFF");
     
      }
  }

//--------------
//==============================================
 if (String(topic) == "kon1/ledMerah") {
    Serial.print("Changing output to LED Merah ");
    if(payload == "on"){
      suisKon = 2;
      Serial.println(suisKon);
    }
  }

//==============================================
  if (String(topic) == "kon1/ledBiru") {
    Serial.print("Changing output to LED Biru ");
    if(payload == "on"){
      suisKon = 1;
      Serial.println(suisKon);
    }
  }
//=============================================

//---- Kod Merah -----
//==============================================
 if (String(topic) == "kon1/ledAmber") {
    Serial.print("Changing output to LED Amber ");
    if(payload == "on"){
      suisKon = 3;
      Serial.println(suisKon);
    }
  }
//=============================================
//---- Kod Merah -----
//==============================================
  if (String(topic) == "kon1/ledWhite") {
    Serial.print("Changing output to LED White ");
    if(payload == "on"){
      suisKon = 4;
      Serial.println(suisKon);
    }
  }
//=============================================
//---- Kod Merah -----
//==============================================
 if (String(topic) == "kon1/ledMagenta") {
    Serial.print("Changing output to LED Magenta ");
    if(payload == "on"){
      suisKon = 5;
      Serial.println(suisKon);
    }
  }
//=============================================
//---- Kod Merah -----
//==============================================
 if (String(topic) == "kon1/ledTurquoise") {
    Serial.print("Changing output to LED Turquoise ");
    if(payload == "on"){
      suisKon = 6;
      Serial.println(suisKon);
    }
  }
//================================tvoc=============
//---- Kod Merah -----
//==============================================

 else if (String(topic) == "kon1/ledHijau") {
    Serial.print("Changing output to LED Hijau ");
    if(payload == "on"){
      suisKon = 7;
      Serial.println(suisKon);
    }
  //--------------------------- END --------------------
}
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
  pinMode(sensorTilt, INPUT);
 
  Serial.begin(115200); // initialize serial
  WiFi.begin(ssid, pass);

  client.begin(NamaBroker, net);
  client.onMessage(messageReceived);
  connect();

  pixels.begin();
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

  client.publish("kon1/ldr", String(dataLDR));   

  //------SENSOR 2 -------------------------------------------------------------
   //------SENSOR 3 -------------------------------------------------------------
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.println(humid);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("°C ");

  client.publish("kon1/suhu", String(temp));  
  client.publish("kon1/humid", String(humid));  
 //-----------end ----------------------------------
  

 //------SENSOR 3 -------------------------------------------------------------

    jarak();




  
  if (suisKon == 1){
    nyalaBarisPixel(40,0,0,200); //biru
    delay(500);
    nyalaBarisPixel(40,0,0,0); //led off
    delay(500);
    client.publish("kon1/led/status", "LED BIRU NYALA");
    Serial.println("--LED BIRU Menyala--");
  }

  else if (suisKon == 2){
    nyalaBarisPixel(40,200,0,0); //merah
    delay(500);
    nyalaBarisPixel(40,0,0,0); //led off
    delay(500);
    client.publish("kon1/led/status", "LED MERAH NYALA");
    Serial.println("--LED MERAH Menyala--");
  }

  else if (suisKon == 3){
    nyalaBarisPixel(40,255,191,0); //amber
    delay(500);
    nyalaBarisPixel(40,0,0,0); //led off
    delay(500);
    client.publish("kon1/led/status", "LED AMBER NYALA");
    Serial.println("--LED AMBER Menyala--");
  }

  else if (suisKon == 4){
    nyalaBarisPixel(40,255,255,255); //putih
    delay(500);
    nyalaBarisPixel(40,0,0,0); //led off
    delay(500);
    client.publish("kon1/led/status", "LED PUTIH NYALA");
    Serial.println("--LED PUTIH Menyala--");
  }

  else if (suisKon == 5){
    nyalaBarisPixel(40,255,0,255); //magenta
    delay(500);
    nyalaBarisPixel(40,0,0,0); //led off
    delay(500);
    client.publish("kon1/led/status", "LED MAGENTA NYALA");
    Serial.println("--LED MAGENTA Menyala--");
  }

  else if (suisKon == 6){
    nyalaBarisPixel(40,64,224,208); //torquise
    delay(500);
    nyalaBarisPixel(40,0,0,0); //led off
    delay(500);
    client.publish("kon1/led/status", "LED TURQUIOS NYALA");
    Serial.println("--LED TURQUIOS Menyala--");
  }

  else if (suisKon == 7){
    nyalaBarisPixel(40,0,255,0); //hijau
    delay(500);
    nyalaBarisPixel(40,0,0,0); //led off
    delay(500);
    client.publish("kon1/led/status", "LED HIJAU NYALA");
    Serial.println("--LED MERAH Menyala--");
  }
   
  else {
    nyalaBarisPixel(40,0,0,0); //padam semua LED
    delay(100);
  }
 //-----------end ----------------------------------
  }
}

void nyalaBarisPixel(int bilLED, int R, int G, int B){
  for(int i=0; i<bilLED; i++) { // For each pixel...

    // pixels.Color() mengambil nilai dari 0,0,0 sehingga 255,255,255
    pixels.setPixelColor(i, pixels.Color(R, G, B));// RGB yang dipilih warna HIJAU
    pixels.show();  
    
  }
}

void jarak() {
  //float duration_us, distance_cm;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  float distance_cm = 0.017 * duration_us;


  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  client.publish("kon1/jarak", String(distance_cm));
}

//##################  Seksyen 3 - TAMAT #############################

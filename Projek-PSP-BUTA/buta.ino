#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>


//----ISTIHAR GPIO PIN anda kumpulkan disini ---------------------------------------------------------------------------------


//---=on board------
#define oneWireBus 15  //--SENSOR SUHU DS18B20
#define Relay01 27   //relay 1
#define Relay02 26   // relay 2
#define buzzer  25     // Buzzer
//--- device/sensor OFF board ------
#define analogSensor1 33
#define analogSensor2 35


#define TRIG_PIN 13 // Pin connected to the trigger pin of the ultrasonic sensor
#define ECHO_PIN 12 // Pin connected to the echo pin of the ultrasonic sensor
#define BUTTON_PIN 36 // Pin connected to the button


//----------------------------------- end -------------------------------------------------------------

// Define constants
#define MAX_DISTANCE_CM 80 // Maximum distance in centimeters for object detection
#define BUZZER_FREQ 2000 // Frequency of the buzzer in Hz

//----ISTIHAR LCD I2C --------------------------------------------------------------
LiquidCrystal_I2C lcd(0x27,20,4);




//----ISTIHAR SENSOR SUHU DS18B20 ---------------------------------------------------------------------
 
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
//----------------------------------- end -------------------------------------------------------------

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers



//---- PENETAPAN WIFI ---------------------------------------------------------------------------------
// --- ubah mengikut wifi masing masing ----------
//const char* ssid = "GUEST";  
//const char* password = "";

const char* ssid = "5rose";
const char* password = "meegoreng1";
//-------------------------------------------------------------------------------
WiFiClient espClient;                                                                          
PubSubClient client(espClient); //MQTT


const char* mqtt_server = "broker.hivemq.com";


//----------------------------------- end -------------------------------------------------------------


//---- PEMBOLEHUBAH DATA---------------------------------------------------------------------------------


char varPotString[8];
long lastMsg = 0;
char msg[50];
int value = 0;
float light;


//----------------------------------- end ---------------------------------------------


void setup() {
  pinMode (Relay01,OUTPUT);
  pinMode (Relay02,OUTPUT);
  pinMode (buzzer,OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  //pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
 
  Serial.begin(115200);
  sensors.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  namakan projek anda  ");
   
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(100);  
   
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Namakan projek anda ");
}


void loop() {
if (!client.connected()) {
    reconnect();
  }
  client.loop();


  long now = millis();


  if (now - lastMsg > 1000) {  
    lastMsg = now;


          //-----------------------------------------------------------------------
          //---mulakan sensor kod anda disini--
         ultrasonic();

         suisMsg();

         suhu();
          //-------------------end ------------------------------------------------
  }
}

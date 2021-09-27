/*
Date 2021-06-27

Garge Door Opener
  Uses WifiManager
  Uses AsyncWebserver

  Presents page which let user open the garage door
  after entering in a secret code...

*/
#include <Arduino.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESPAsyncWebServer.h>
#include <LITTLEFS.h>
#include <ESPmDNS.h>
#include <AsyncElegantOTA.h>
#include "version.h"
#include "garage_server.h"
#include "garage_settings.h"

#define OPEN_PIN 32
#define LAMP_PIN 23
#define NOT_PRESSED LOW
#define PRESSED HIGH
#define BUTTON_DOWN_TIME_MS 2000UL
#define WIFI_UPDATE_PERIOD_MS 10000UL
#define DAILY_RESET_PERIOD_MS (60UL*60UL*24UL*1000UL)
#define MAX_TIME_IN_PORTAL 300000L //5minutes in the portal is long enough
#define MAX_TIME_IN_WIFI_DISCONNECTED 1200000L //20 minutes


/**
 * Global Variables
 */
extern AsyncWebServer server;
extern GarageSettings_t settings;


WiFiManager wm;
Info_t info = {
  .up_hours = 0,
  .up_min   = 0,
  .up_sec   = 0,
  .up_time  = 0,
  .wifi_rssi= -99
};

enum GarageState_t{g_init,g_idle,g_open_down,g_lamp_down} garageState;

bool garageStateOnEntry = true;
unsigned long garageStateMSTimer = 0UL;
uint8_t  open_command  = 0;//set by the server, cleared by the loop garage
uint8_t  lamp_command = 0;//set by the server, cleared by the loop_garage
unsigned long  loop_wifi_timer = 0UL;
unsigned long  portal_timer = MAX_TIME_IN_PORTAL;
unsigned long  wifi_disconnected_timer = MAX_TIME_IN_WIFI_DISCONNECTED;

/*
*Function Prototypes
*/
void setup_fs();
void setup_wifi();
void setup_pins();
void loop_garage();
void loop_wifi();
bool checkCode(String code);
void loop_wifi_rssi();
void loop_reset_every_day();
void update_info();
String processor(const String& var);
void setup_ota();

void setup(){
    // put your setup code here, to run once:
    Serial.begin(115200);
    delay(200);
    Serial.println(String("Garage Door Version:") + VERSION);
    setup_fs();
    setup_settings();
    setup_pins();
    setup_wifi();
    setup_ota();
    setup_server();
}

bool used_portal = false;
bool server_init = false;
void loop() {
    // put your main code here, to run repeatedly:
    loop_wifi();
    loop_garage();
    //see if its time to do the daily reset
    loop_reset_every_day();
}
void setup_ota(){
  Serial.println("Setting up OTA");
  
  AsyncElegantOTA.begin(&server,settings.http_username,settings.http_password);    // Start ElegantOTA
}
void setup_wifi() {
  portal_timer = MAX_TIME_IN_PORTAL + millis();
  wifi_disconnected_timer = MAX_TIME_IN_WIFI_DISCONNECTED + millis();

  // WiFi.mode(WiFi_STA); // it is a good practice to make sure your code sets wifi mode how you want it.
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

    //reset settings - wipe credentials for testing
    //wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    
    wm.setConfigPortalBlocking(false);

    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("GarageAP","!tomlov123!"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        wifi_disconnected_timer = MAX_TIME_IN_WIFI_DISCONNECTED + millis();
    }

  //setup mdns
  Serial.print("Starting mDNS:");
  Serial.println(settings.dev_name);

  if(!MDNS.begin(settings.dev_name)) {
     Serial.println("Error starting mDNS");
  }
  MDNS.addService("_http", "_tcp", 80);
  MDNS.setInstanceName(settings.dev_name);
}



void setup_fs(){
Serial.println("Mounting file system\n");
  if(!LITTLEFS.begin()){
        Serial.println("An Error has occurred while mounting LITTLEFS");
        return;
  }
}

void setup_pins(){
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(OPEN_PIN,OUTPUT);
  pinMode(LAMP_PIN,OUTPUT);
}

void loop_reset_every_day(){
  if(millis()>DAILY_RESET_PERIOD_MS){
    Serial.println("Executing Daily Reset!\n");
    delay(200);
    ESP.restart();
  }

}

void loop_wifi_rssi(){
  
  //display rssi every 10s
  
  if(loop_wifi_timer < millis()){
    loop_wifi_timer =  millis() + WIFI_UPDATE_PERIOD_MS;
    
      if(WiFi.status() == WL_CONNECTED){
      
        int16_t rssi;
        rssi = WiFi.RSSI();  // eg. -63
        
        // Convert to scale -48 to 0 eg. map(rssi, -100, 0, 0, -48);
        // I used -100 instead of -120 because <= -95 is unusable
        // Negative number so we can draw n pixels from the bottom in black
      
        if(rssi < -99)
        {
          rssi = -99;
        }
        //  lbg.drawValue(100+rssi, 100);
        Serial.printf("wifi signal report:%ddb\n",rssi);
        wifi_disconnected_timer = MAX_TIME_IN_WIFI_DISCONNECTED + millis();
      }else{
        Serial.printf("wifi not connected!\n");
        if( wifi_disconnected_timer < millis()){
          Serial.printf("wifi disconnected timer expired!\n Resetting device!.\n");
          ESP.restart();
        }
      }
  }
}


void loop_wifi(){
    wm.process();
    if(wm.getConfigPortalActive()){
      used_portal = true;

      if(portal_timer < millis()){
          Serial.println(F("Device in portal too long...\nReseting Device!\n"));
          ESP.restart();
      }
    }
    else{
      if(!server_init){
        if(used_portal){
          Serial.println(F("Used a portal Reseting Device."));
          ESP.restart();
          server_init=true;
        }else{
          Serial.println(F("Starting Application"));
          server.begin();
          server_init=true;
       }
      }else{
        //periodically report the wifi signal strength
        loop_wifi_rssi();
      }
    }
}

void loop_garage(){
  switch(garageState){
    case g_init:
      if(garageStateOnEntry){
        Serial.println(F("GarageState Init:"));
        digitalWrite(OPEN_PIN,NOT_PRESSED);
        digitalWrite(LAMP_PIN,NOT_PRESSED);
        digitalWrite(LED_BUILTIN,LOW);
        garageState = g_idle;
        garageStateOnEntry = true;
      }
    break;
    case g_idle:
      if(garageStateOnEntry){
          Serial.println(F("GarageState Idle:"));
          digitalWrite(OPEN_PIN,NOT_PRESSED);
          digitalWrite(LAMP_PIN,NOT_PRESSED);
          digitalWrite(LED_BUILTIN,LOW);
          garageStateOnEntry = false;
        }

        if(open_command){
          garageStateOnEntry=true;
          garageState = g_open_down;
          open_command = 0;
        }else if(lamp_command){
          garageStateOnEntry=true;
          garageState = g_lamp_down;
          lamp_command = 0;
        }
    break;
    case g_open_down:
      if(garageStateOnEntry){
          Serial.println(F("Open Down:"));
          digitalWrite(OPEN_PIN,PRESSED);
          digitalWrite(LAMP_PIN,NOT_PRESSED);
          digitalWrite(LED_BUILTIN,HIGH);
          garageStateOnEntry = false;
          garageStateMSTimer = millis() + BUTTON_DOWN_TIME_MS;
        }

        if(garageStateMSTimer < millis()){
          garageState = g_idle;
          garageStateOnEntry = true;
        }
    break;
    case g_lamp_down:
      if(garageStateOnEntry){
          Serial.println(F("Lamp Down:"));
          digitalWrite(OPEN_PIN,NOT_PRESSED);
          digitalWrite(LAMP_PIN,PRESSED);
          digitalWrite(LED_BUILTIN,HIGH);
          garageStateOnEntry = false;
          garageStateMSTimer = millis() + BUTTON_DOWN_TIME_MS;
        }

        if(garageStateMSTimer < millis()){
          garageState = g_idle;
          garageStateOnEntry = true;
        }
    break;

  }
}

/**
 *Update the info data for the info page 
 */
void update_info(){
  unsigned long temp;
  info.up_time = millis();
  info.wifi_rssi = WiFi.RSSI();
  info.ip_addr = WiFi.localIP().toString();
  info.dev_name = String(settings.dev_name);
  info.url = String("http://") + info.dev_name + ".local";

  info.up_hours = info.up_time / (3600UL*1000UL);
  temp = info.up_time - info.up_hours * 3600UL*1000UL;
  info.up_min = temp / (60UL*1000UL);
  temp = info.up_time - info.up_hours * 3600UL*1000UL - info.up_min*60UL * 1000UL;
  info.up_sec = temp / 1000UL; 
}

void send_open_command(){
  open_command = true;
}

void send_lamp_command(){
  lamp_command = true;
}


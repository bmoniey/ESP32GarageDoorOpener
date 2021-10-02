#include "garage_server.h"
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ESPAsyncWebServer.h>
#include <LITTLEFS.h>
#include "version.h"
#include "garage_settings.h"

AsyncWebServer server(80);

const char* http_username = "admin";
const char* http_password = "password";

extern Info_t info;
extern GarageSettings_t settings;
extern WiFiManager wm;
extern void update_info();
extern void send_lamp_command();
extern void send_open_command();

bool checkCode(String code){
  if(code == settings.code){
    return true;
  }
  else{
    return false;
  }
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

String info_processor(const String& var){
  String S = String();

  if(var == "UPTIME"){
    S += info.up_hours;
    S += "hh ";
    S += info.up_min;
    S += "mm ";
    S += info.up_sec;
    S += "ss";
    Serial.println("UPTIME:" + S);
    return S;
  }else if(var == "WIFI_RSSI"){
    S +=info.wifi_rssi;
    Serial.println("WIFI_RSSI:" + S);
    return S;
  }else if(var == "VERSION"){
    S += VERSION;
    Serial.println("VERSION:" + S);
  }else if(var == "IP_ADDR"){
    S += info.ip_addr;
    Serial.println("IP_ADDR:" + S);
  }else if(var == "DEV_NAME"){
    S += info.dev_name;
    Serial.println("DEV_NAME:" + S);
  }else if(var == "URL"){
    S += info.url;
    Serial.println("URL:" + S);
  }

  return S;
}

String make_form_entry(String url,String display_name,String var_name, String val){
  String S = String();
  S+="<h2>";
  S+= "<form action =\"" + url + "\" method=\"get\">";
  S+= display_name;
  S+= "<input type=\"text\"   name=";
  S+= "\"" + var_name + "\" value=\""+ val + "\">";
  S+= "<input type=\"submit\" value=\"Submit\">";
  S+="</form>";
  S+="</h2>";
  return S;
}

String make_action_button(String url, String name){
  String S = String();
   S+="<button onclick=genericButtonClick(\"" + url + "\")>"+name+"</button>";
  return S;
}

String admin_processor(const String& var){
  String S = String();
  S+=make_form_entry("admin","admin username", "http_username",settings.http_username);
  S+="<br>\n";
  S+=make_form_entry("admin","admin password", "http_password",settings.http_password);
  S+="<br>\n";
  S+=make_form_entry("admin","device name", "dev_name",settings.dev_name);
  S+="<br>\n";
  S+=make_form_entry("admin","garage access code", "code",settings.code);
  S+="<br>\n";
  S+= make_action_button(String("reset"),String("Reset"));
  S+="<br>\n";
  S+= make_action_button(String("default"),String("Restore Default Settings"));
  S+="<br>\n";
  S+= make_action_button(String("save"),String("Save Settings"));
  S+="<br>\n";
  S+= make_action_button(String("reset_wifi"),String("Reset WiFi Credentials"));
  S+="<br>\n";
  return S;
}

void send_json_message(AsyncWebServerRequest *request,String field1,String value1){
  String S = String();
  S+="{\"" + field1 + "\":\"" + value1 + "\"}";
  request->send(200, "appliction/json", S);
}

void setup_server(){
  Serial.println("Setting up web server...");
  
  //wm.server->close();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //readFile(LITTLEFS,"/index.html");
    request->send(LITTLEFS, "/index.html", String(), false);
  });

    // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LITTLEFS, "/style.css", "text/css");
  });

  // Route to load scripts.js file
  server.on("/scripts.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LITTLEFS, "/scripts.js", "text/js");
  });

  // reset the esp32
  server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Received /reset request");
    
    send_json_message(request,"message","resetting in 2 seconds...");

    //wm.resetSettings();
    delay(2000);
    ESP.restart();
  });

    // reset the esp32
  server.on("/reset_wifi", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Received /reset_wifi request");
    
    send_json_message(request,"message","resetting wifi credentials in 2 seconds...look for GarageAP at 192.168.1.4");

    wm.resetSettings();
    delay(2000);
    ESP.restart();
  });

   // process the code
  server.on("/code", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Received /code request");
    String code;
        if (request->hasParam("code")) {
            code = request->getParam("code")->value();
            Serial.print("Got:");
            Serial.println(code);
        } else {
            code = "0";
        }
        
        send_json_message(request,"code",code);

        if(checkCode(code)){
          send_open_command();
          Serial.println("valid code recieved!");
        }
  });

  // process the lamp command
  server.on("/lamp", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Received /lamp request");
    String lamp;
        if (request->hasParam("lamp")) {
            lamp = request->getParam("lamp")->value();
            Serial.print("Got:");
            Serial.println(lamp);
        } else {
            lamp = "0";
        }
        
        send_json_message(request,"lamp",lamp);

        if(lamp == "toggle"){
          send_lamp_command();
          Serial.println("lamp toggled!");
        }
  });

  // info page
  server.on("/info", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Received /info request");
        update_info();

        request->send(LITTLEFS, "/info.html", String(), false,info_processor); 
  });

    // admin
  server.on("/admin", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Received /admin request");
        if(!request->authenticate(settings.http_username, settings.http_password))
            return request->requestAuthentication();
        Serial.println("/admin Authentication Success!");
        String message;
        
        if (request->hasParam("code")) {
            message = request->getParam("code")->value();
            strcpy(settings.code,message.c_str());
        }else if(request->hasParam("http_username")) {
            message = request->getParam("http_username")->value();
            strcpy(settings.http_username,message.c_str());
        }else if(request->hasParam("http_password")) {
            message = request->getParam("http_password")->value();
            strcpy(settings.http_password,message.c_str());
        }else if(request->hasParam("dev_name")) {
            message = request->getParam("dev_name")->value();
            strcpy(settings.dev_name,message.c_str());
        }
        Serial.println(message);

        request->send(LITTLEFS, "/admin.html", String(),false,admin_processor); 
  });

  // default settings
  server.on("/default", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Received /default request");
        if(!request->authenticate(settings.http_username, settings.http_password))
            return request->requestAuthentication();
        Serial.println("/default Authentication Success!");
        restore_default_settings();
        send_json_message(request,"message","restore setting defaults success!"); 
  });

    // save settings
  server.on("/save", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("Received /save request");
        if(!request->authenticate(settings.http_username, settings.http_password))
            return request->requestAuthentication();
        Serial.println("/default Authentication Success!");
        save_settings(&settings);
        
        send_json_message(request,"message","save settings success!");
  });

  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(401);
  });

  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LITTLEFS, "/index.html", String(),false);
  });
  
  server.onNotFound(notFound);
}


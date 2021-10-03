#include <garage_settings.h>
#include <ArduinoJson.h>
//#define HALT() for(;;){}
#define HALT() 

GarageSettings_t settings;
StaticJsonDocument<255> json_settings;


void default_settings(GarageSettings_t * s){
    Serial.println("setting default settings");
    strcpy(s->http_username,"admin");
    strcpy(s->http_password,"password");
    strcpy(s->code,"161974");
    strcpy(s->dev_name,"garage-test");
    strcpy(s->ap_name,"GarageAP");
    strcpy(s->ap_password,"!tomlov123!");
}

void show_settings(GarageSettings_t * s){
    Serial.println("Show Settings:");
    Serial.print("http_username:");
    Serial.println(s->http_username);
    Serial.print("http_password:");
    Serial.println(s->http_password);
    Serial.print("code:");
    Serial.println(s->code);
    Serial.print("dev_name:");
    Serial.println(s->dev_name);
    Serial.print("ap_name:");
    Serial.println(s->ap_name);
    Serial.print("ap_password:");
    Serial.println(s->ap_password);
}

void save_settings(GarageSettings_t * s){
  Serial.println(F("Saving settings\n"));

  json_settings["http_username"] = s->http_username;
  json_settings["http_password"] = s->http_password;
  json_settings["code"] = s->code;
  json_settings["dev_name"] = s->dev_name;
  json_settings["ap_name"] = s->ap_name;
  json_settings["ap_password"] = s->ap_password;

  LITTLEFS.remove("/settings.json");
  File fd = LITTLEFS.open("/settings.json",FILE_WRITE);
  if(serializeJson(json_settings,fd)==0){
    Serial.println(F("Failed to write to file"));
  }
  fd.close();
}


void load_settings(GarageSettings_t * s){
    Serial.println(F("loading settings\n"));

    default_settings(&settings);//make sure something good is in there
    File fd = LITTLEFS.open("/settings.json",FILE_READ);
    if(!fd){
      Serial.println("Failed to open settings.json\n");  
      save_settings(&settings);
      show_settings(&settings);
      return;
    }
    size_t sz = fd.size();
    if(sz >1024){
      Serial.println("settings.json > 1024 bytes\n");
      HALT();
    }
    //get the settings from the file
    DeserializationError err = deserializeJson(json_settings,fd);
    fd.close();

    if(err){
      Serial.print("Error deserializing jason settings with code:");
      Serial.println(err.c_str());
      HALT();
    }

    if(json_settings["http_username"]){
      strcpy(s->http_username,json_settings["http_username"]);
    }
    
    if(json_settings["http_password"]){
      strcpy(s->http_password,json_settings["http_password"]);
    }

    if(json_settings["code"]){
      strcpy(s->code,json_settings["code"]);
    }

    if(json_settings["dev_name"]){
      strcpy(s->dev_name,json_settings["dev_name"]);
    }

    if(json_settings["ap_name"]){
      strcpy(s->ap_name,json_settings["ap_name"]);
    }

    if(json_settings["ap_password"]){
      strcpy(s->ap_password,json_settings["ap_password"]);
    }
}

void setup_settings(){
    Serial.println("Setup Settings:");
    load_settings(&settings);
    Serial.println("settings.json");
    serializeJson(json_settings,Serial);
    Serial.println("");
    show_settings(&settings);
}

void restore_default_settings(){
    Serial.println("Restoring default Settings:");
    default_settings(&settings);
    save_settings(&settings);
    serializeJson(json_settings,Serial);
    show_settings(&settings);
}
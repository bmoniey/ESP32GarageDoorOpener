#ifndef GARAGE_SETTINGS_H
#define GARAGE_SETTINGS_H
    #include <Arduino.h>
    #include <LITTLEFS.h>
    #define DEFAULT_STRING_LEN 64
typedef struct GarageSettings{
    char http_username[DEFAULT_STRING_LEN];
    char http_password[DEFAULT_STRING_LEN];
    char code[DEFAULT_STRING_LEN];
    char dev_name[DEFAULT_STRING_LEN];
}GarageSettings_t;

void show_settings(GarageSettings_t * s);
void save_settings(GarageSettings_t * s);
void default_settings(GarageSettings_t * s);
void setup_settings();
extern void restore_default_settings();
#endif
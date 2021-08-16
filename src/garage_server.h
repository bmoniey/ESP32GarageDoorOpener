#ifndef GARAGE_SERVER_H
#define GARAGE_SERVER_H
    #include <Arduino.h>

    typedef struct Info{
        uint32_t        up_hours;
        uint32_t        up_min;
        uint32_t        up_sec;
        unsigned long   up_time;//same as millis()
        int             wifi_rssi;
        String          ip_addr;
        String          dev_name;
        String          url;
    }Info_t;

    void setup_server(void);
#endif
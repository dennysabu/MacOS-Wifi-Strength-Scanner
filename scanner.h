#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef SCANNER_H

     #define WIFI_COMMAND "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -I"
     #define BUF_SIZE 512

     typedef struct _scanData {
          int * agrCtlRSSI;
          int  *agrExtRSSI;
          int * agrCtlNoise;
          int * agrExtNoise;
          char state[50];
          char op_mode[50];
          double * lastTxRate;
          double * maxRate;
          char auth_80211[50];
          char link_Auth[50];
          char BSSID[20];
          char SSID[256];
          int * MCS;
          char channel[10];

     } ConnData;



     int freeConnData(ConnData * data){
          free(data->agrCtlRSSI);
          free(data->agrExtRSSI);
          free(data->agrCtlNoise);
          free(data->agrExtNoise);
          //free(data->state);
          //free(data->op_mode);
          //free(data->lastTxRate);
          //free(data->maxRate);
          //free(data->auth_80211);
          //free(data->link_Auth);
          //free(data->BSSID);
          //free(data->SSID);
          //free(data->MCS);
          //free(data->channel);

          return 0;
     }

     int printConnStrength(ConnData * data){
          printf("Strength: %d\n", *data->agrCtlRSSI);
          return 0;
     }

#endif
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef SCANNER_H

     #define WIFI_COMMAND "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -I"
     #define BUF_SIZE 512
     #define DEBUG 0
     #define PRINT_DEBUG 0

     typedef struct _scanData {
          int * agrCtlRSSI;     //0             
          int  *agrExtRSSI;
          int * agrCtlNoise;
          int * agrExtNoise;
          char * state;
          char * op_mode;     //5
          int * lastTxRate;
          int * maxRate; //7
          int * lastAssocStatus;
          char * auth_80211;
          char * link_Auth;        //10
          char * BSSID;
          char * SSID;
          int * MCS;
          char * channel;               //14

     } ConnData;



     int freeConnData(ConnData * data){
          free(data->agrCtlRSSI);
          free(data->agrExtRSSI);
          free(data->agrCtlNoise);
          free(data->agrExtNoise);
          free(data->state);
          free(data->op_mode);
          free(data->lastTxRate);
          free(data->maxRate);
          free(data->lastAssocStatus);
          free(data->auth_80211);
          free(data->link_Auth);
          free(data->BSSID);
          free(data->SSID);
          free(data->MCS);
          free(data->channel);

          return 0;
     }

     int printConnStrength(ConnData * data, int verbosity){

          if (verbosity == 0 ){
               printf("%d\n", *data->agrCtlRSSI);
          }
          else if (verbosity == 1){
               printf("Strength: %d\n", *data->agrCtlRSSI);
          }
          else if ( verbosity == 2 ){
               printf("agrCtlRSSI: %d\n", *data->agrCtlRSSI);
               printf("agrExtRSSI: %d\n", *data->agrExtRSSI);
               printf("agrCtlNoise: %d\n", *data->agrCtlNoise);
               printf("agrExtNoise: %d\n", *data->agrExtNoise);
               printf("state: %s\n", data->state);
               printf("op mode: %s\n", data->op_mode); 
               printf("lastTxRate: %d\n", *data->lastTxRate);
               printf("maxRate: %d\n", *data->maxRate);
               printf("lastAssocStatus: %d\n", *data->lastAssocStatus);
               printf("802.11 auth: %s\n", data->auth_80211);
               printf("link auth-psk: %s\n", data->link_Auth);
               printf("BSSID: %s\n", data->BSSID);
               printf("SSID: %s\n", data->SSID);
               printf("MCS: %d\n", *data->MCS);
               printf("channel: %s\n", data->channel);
          }


          return 0;
     }

#endif
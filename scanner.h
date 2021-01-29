#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef SCANNER_H

     #define WIFI_COMMAND "/System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport -I"
     #define BUF_SIZE 512
     #define DEBUG 0
     #define PRINT_DEBUG 1

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

     int printConnStrength(ConnData * data){

          printf("Strength: %d\n", *data->agrCtlRSSI);
          if ( PRINT_DEBUG ){
               printf(" auth : %s\n",data->auth_80211);
               printf(" link : %s\n",data->link_Auth);
               printf(" bssid : %s\n",data->BSSID);
               printf(" ssid : %s\n",data->SSID);
               printf(" channel: %s\n",data->channel);
          }


          return 0;
     }

#endif
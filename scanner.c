#include "scanner.h"


#define DEBUG 0


int splitInt( int ** recv,  char * line){
     char * key;
     char * value;

     int keyStartFound = 0;


     for (int i = 0; i < strlen(line); i++){
          if(!keyStartFound){
               if(isalpha(line[i])){
                    key = &line[i];
                    keyStartFound = 1;
               }
          }

          if (keyStartFound){
               if(line[i] == ':'){
                    line[i]='\0';
                    value = &line[i + 1];
                    break;
               }
          }
     }



     *recv = (int * )malloc(sizeof(int));
     if (*recv == NULL){
          printf("Unable to allocate memory...terminating\n");
          return -1;
     } 

     int val = atoi(value);

     **recv = val;
     return 0;
}

int splitDouble(const double * recv, const char * line){
     printf("got: %s\n", line);
     return 0;
}

int splitChar(const double * recv, const char * line){

     return 0;
}

int runWifiScan(){
     ConnData * data = (ConnData*)malloc(sizeof(ConnData) * 1);
     bzero(data, sizeof(ConnData));

     char readBuffer[BUF_SIZE];

     FILE * cmdResult = popen(WIFI_COMMAND, "r");

     int line = 0;

     if (cmdResult == NULL){
          printf("Unable to run command '%s'\nTerminating\n", WIFI_COMMAND);
          return -1;
     }
     while (fgets(readBuffer, BUF_SIZE, cmdResult) != NULL){
          //printf("%s", readBuffer);

          switch(line){
               case 0:
                    if (splitInt(&data->agrCtlRSSI, readBuffer) < 0){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
               case 1: 
                    if (splitInt(&data->agrExtRSSI, readBuffer) < 0){
                          printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
               case 2:
                    if(splitInt(&data->agrCtlNoise, readBuffer) < 0) {
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
               case 3: 
                    if(splitInt(&data->agrExtNoise, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
               case 6:
               case 7:
               case 8:
               case 13:
                    
                    break;
          }

          if (DEBUG){
               for (int i = 0; i < strlen(readBuffer); i++){
                    if (readBuffer[i] == '\n')
                         printf("\nfound end right after: %c\n", readBuffer[i -1]); 
               }
          }
          bzero(readBuffer, BUF_SIZE);
          line++;
          
          if (DEBUG){
               if (line > 2){
                    line = 0;
                    break;
               }
          }
          
          
          
     }
     printConnStrength(data);
     freeConnData(data);
     return 0;
}


int main(int argc, char ** argv){

     printf("Command to run %s\n", WIFI_COMMAND);

     while(1){
          runWifiScan();
          usleep(2000000);
     }
     

     

}
#include "scanner.h"


int splitInt( int ** recv,  char * line){
     char * key;
     char * value;

     int keyStartFound = 0;


     for (int i = 0; i < strlen(line); i++){
          if(!keyStartFound){
               if(isalnum(line[i])){
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

     **recv = atoi(value);
     return 0;
}

int splitChar( char ** recv,  char * line){

     if (DEBUG){
          //printf(" ** Incoming Data **\n");
          //printf(" ** *recv : %p **\n", *recv);
          //printf(" ** line : %s **\n", line);
     }

     char * key;
     char * value;
     int keyStartFound = 0;


     for (int i = 0; i < strlen(line); i++){
          if(!keyStartFound){
               if(isalnum(line[i])){
                    key = &line[i];
                    keyStartFound = 1;
               }
          }

          if (keyStartFound){
               if(line[i] == ':'){
                    line[i]='\0';
                    value = &line[i + 2];
                    int j = 0 ; //Start of value
                    while (j < strlen(value) && (isalnum(value[j]) || ispunct(value[j]))){
                         j++;
                    }
                    value[j] = '\0'; //replace last item (j should be a non alpha char) with a \0
                    break;
               }
          }

          }

          *recv = (char *)malloc(sizeof(char) * strlen(value));
           
          if( *recv == NULL){
               printf("Unable to allocate memory...terminating\n");
               return -1;
          }

          strncpy(*recv, value, strlen(value)); // Copy values over to malloc'd 

     return 0;
}

int runWifiScan( int verbosity ){
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
                    }

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
               case 4:
                    if(splitChar(&data->state, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;       
               case 5:
                    if(splitChar(&data->op_mode, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;                
               case 6:
                    if(splitInt(&data->lastTxRate, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
               case 7:
                    if(splitInt(&data->maxRate, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
               case 8:
                    if(splitInt(&data->lastAssocStatus, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;             
               case 9:
                    if(splitChar(&data->auth_80211, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
                case 10:
                    if(splitChar(&data->link_Auth, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
                case 11:
                    if(splitChar(&data->BSSID, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;    
                case 12:
                    if(splitChar(&data->SSID, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;    
               case 13:
                    if(splitInt(&data->MCS, readBuffer) < 0) {
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };
                    break;
                case 14:
                    if(splitChar(&data->channel, readBuffer) < 0 ){
                         printf("Error parsing data...terminating\n");
                         return -1;
                    };                               
                    break;
               default:
                    printf("Unexpected data...terminating\n");
                    return 0;
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
     printConnStrength(data, verbosity);
     freeConnData(data);
     pclose(cmdResult);
     return 0;
}


int main(int argc, char ** argv){

     /*
          0: No extra output
          1: Standard output       //Default
          2: Print all the output 
     */
     int verbosity = 1;


     /*
          0: print only once
          1: print continuously    //Default
     */
     int repetition = 1;

     opterr = 0;

     //Verbosity v 
     //output o
     int c;
     while ((c = getopt (argc, argv, "v::o::")) != -1){
          
          int verbSwitch = -99;
          int outputSwitch = -99;
          switch(c){
               case 'v':

                    verbSwitch = atoi(optarg);
                    if (verbSwitch == 0 || verbSwitch == 1 || verbSwitch == 2){
                         verbosity = verbSwitch;
                    }
                    else{
                         printf("\tInvalid value for option -%c: '%s'\n", c, optarg);
                         return -1;
                    }
                    break;
               case 'o':
                    outputSwitch = atoi(optarg);
                    if (outputSwitch == 0 || outputSwitch == 1){
                         repetition = outputSwitch;
                    }
                    else{
                         printf("\tInvalid value for option -%c: '%s'\n", c, optarg);
                         return -1;
                    }
                    break;
               
               case '?':
                    printf("Unknown option '-%c'\n", optopt);
               
               case 'h':
                    printf("\nUsage: scanner [OPTIONS]\n");
                    printf("\n -v Verbosity\n");
                    printf("\t 0 - Minimal output\n");
                    printf("\t 1 - Standard output [Default]\n");
                    printf("\t 2 - Maximum output\n");

                    printf("\n -o Repetition\n"); 
                    printf("\t 0 - Do not repeat\n");
                    printf("\t 1 - Repeat [Default]\n");
                    return 0;
               
               default:
                    //printf("Not matching args");
                    break;

          }
     }
    
     if (repetition)
          while(1){
               runWifiScan(verbosity);
               usleep(2000000);
          }
     else{
          runWifiScan(verbosity);
     }
     

     

}
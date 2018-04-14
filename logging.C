#include "logging.h"
#include <stdio.h>
#include <string.h>


FILE* Logger::logger = fopen("logger", "w");

DataFlowException :: DataFlowException(const char *type, const char *error){
    strcpy(msg, error);
}

void Logger :: LogEvent(const char *event){
    fwrite(event, sizeof(char), sizeof(char)*strlen(event), logger);    
    fflush(logger);
}

void Logger :: Finalize(){
    fclose(logger);
}




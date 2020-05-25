#include"commands.h"

void help(){
    printf("\nCommands : \n\
        - echo      Printing HashQueue, FreeList and ProcessList\n\
        - process   Creating multiple processes\n\
        - clear     Clear the screen\n\
        - help      Open the help section\n\
        ");
    
    printf("\necho :\n\
        It take only one parameter.\n\
        - hashqueue     for printing HashQueue\n\
        - freelist      for printing FreeList\n\
        - processlist   for printing ProcessList\n\
        ");

    printf("\nprocess - Create multiple processes :\n\
        It takes any number of parameter\n\
        - filename -  that consist the requests for blocks.\n\
        e.g process input1.txt input2.txt \
        ");   
}

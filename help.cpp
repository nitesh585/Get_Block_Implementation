#include"commands.h"

void help(){
    printf("\nCommands : \n\
        - echo      Printing HashQueue, FreeList and ProcessList\n\
        - addblk    Adding block to the hashqueue\n\
        - getblk    Requesting for buffer block\n\
        - brelse    Releasing the buffer block\n\
        - clear     Clear the screen\n\
        - help      Open the help section\n\
        ");
    
    printf("\necho :\n\
        It take only one parameter.\n\
        - hashqueue     for printing HashQueue\n\
        - freelist      for printing FreeList\n\
        - processlist   for printing ProcessList\n\
        ");

    printf("\naddblk - ADD BLOCK :\n\
        It takes two parameters ( block number and status of the block )\n\
        - block number   is any integer value\n\
        - status         1 - unlocked block / 3 - block marked as delayed write\n\
    ");
    
    printf("\ngetblk - GET BLOCK :\n\
        It takes only one parameter\n\
        - block number   is any integer value\n\
        ");

    printf("\nbrelse - BLOCK RELEASE :\n\
        It takes only one parameter\n\
        - block number is any integer value\n\n");    
}

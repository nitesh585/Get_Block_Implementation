#include"commands.h"
#include"buffer.h"

void brelse(string blkNum){
    int blk_num = stoi(blkNum);
    /*
    wakeup all PfOCS: event, waiting for any buffer to become free;
    wakeup all procs: event, waiting for this buffer to become free;
    raise processor execution level to block interrupts;
    */
    if(getStatus(blk_num)==0){
        setStatus(blk_num,1);  //unlock(buffer) ;
        addToTailFL(blk_num,1,1); //enqueue buffer at head of free list
        printf("Block Released!!\n");
    }else{
        printf("Block is not locked!!\n");
    }
    
}
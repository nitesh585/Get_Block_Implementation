#include"commands.h"
#include"buffer.h"
#include<unistd.h>
#include<mutex>
mutex mtx2;

void brelse(int blkNum){
    /*
      wakeup all PfOCS: event, waiting for any buffer to become free;
      wakeup all procs: event, waiting for this buffer to become free;
      raise processor execution level to block interru  pts;
    */

    sleep(20);
    if(getStatus(blkNum) == 0){
        mtx2.lock();
          setStatus(blkNum, 1);  //unlock(buffer) ;
          addToTailFL(blkNum, 1, 1); //enqueue buffer at head of free list
        mtx2.unlock();
        // printf("Block Released!!\n");
    }else{
      //  printf("Block is not locked!!\n");
    }
}
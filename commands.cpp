#include<iostream>
#include<unistd.h>
#include"commands.h"
#include"buffer.h"
 
// Hashmap to check whether thread is alive or not
unordered_map<thread::id,bool> threadAlive;

// set thread is alive
void setAlive(thread::id id){
    threadAlive[id]  = true;
}


// set thread is die ( its works is done )
void setDie(thread::id id){
    threadAlive[id]  = false;
}


// function to addblk to hashqueue
void addblk(string blk_num, string status){
    int blknum = stoi(blk_num);
    int sts = stoi(status);
    if(searchHQ(blknum)){
	    std::cout<<"Block already in HashQueue\n";
        return;
    }
  
    // if the status of the block is unlocked or marked as delayed write
    if(sts==1 || sts==3){
        addToHQ(blknum,1,sts);
        cout<<"Block Added !!\n";

        if(sts==1){
            // if status of block is unlocked then add to tail in the freelist
            addToTailFL(blknum,1,sts);
        }else{
            // if status of block is marked as delayed write then add to head in the freelist
            addToHeadFL(blknum,1,sts);
        }

    }else{
        cout<<"\nERROR\n";
    }   
    sleep(1);
}


// Display the IDs of the thread that are still alive ( waiting for a block to be assign)
void displayPL(){
    cout<<"\n---------------PROCESS_LIST---------------\n";
    for(auto i=threadAlive.begin() ; i!=threadAlive.end() ; i++){
        if(i->second){
            std::cout<<i->first<<" ";
        }
    }
    std::cout<<"\n\n";
}


// function to print the defined data structures
void echo(string arg){

    if(arg=="hashqueue"){
        displayHQ(); // print Hashqueue
    
    }else if(arg=="freelist"){
        displayFL(); // print free list
    
    }else if(arg=="processlist"){
        displayPL(); // print Process list
    
    }else{
        printf("Invalid Command !!\n");
    }
}
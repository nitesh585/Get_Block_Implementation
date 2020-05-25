#include"buffer.h"
#include<iostream>
#include<algorithm>
#define siz 16

// HashQueue
std::unordered_map <int,std::vector<bufferHeader>> HashQueue;
//vector of bufferheader in freeList
std::vector<bufferHeader> freeList;
std::unordered_map<int,bufferHeader> map;


// initialization function
void init(){
    bufferHeader* tmp =  new bufferHeader(-1,1,1);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            HashQueue[i].emplace_back(*tmp);
        }
    }

    for(int i=0; i<16; i++) freeList.emplace_back(*tmp);
}


//---------------------HASHQUEUE METHODS---------//

//Print all the blocks present in hashqueue
void displayHQ(){
    cout<<"\n---------HASH_QUEUE---------\n\n";
        bool check =false;
        for(int i=0; i<4; i++){
            if(HashQueue[i].begin()->blk_num!=-1){
                check=true;
                break;
            }
        }
        if(check){
            for(int i=0;i<4;i++){
                vector<bufferHeader> tmp = HashQueue[i];
                cout<<i<<"->";
                auto it = tmp.begin();
                for (int j=0; j< tmp.size() ; j++){
                    if(it->blk_num!=-1)
                        std::cout<<"|"<<it->blk_num<<"|->";
                    it++;
                }
                std::cout<<"\n";
            }
        }else{
            for(int i=0;i<4;i++){
                vector<bufferHeader> tmp = HashQueue[i];
                cout<<i<<"->";
                auto it = tmp.begin();
                for (int j=0; j< tmp.size() ; j++){
                    std::cout<<" |"<<it->blk_num<<"|->";
                    it++;
                }
                std::cout<<"\n";
            }
        }

    std::cout<<"\n";

}


// Add block to hash queue
void addToHQ(int blk_num,int dNum,int status){
    bufferHeader *block = new bufferHeader(blk_num,dNum, status);
    
    int hash = (dNum+blk_num)%4;
    // if the block is not found in hashqueue then only insert it into hashqueue
    if(!searchHQ(blk_num)){
         HashQueue[hash].push_back(*block);
    }
}


// delete block from hash queue
void deleteFromHQ(int blk_num){
    int hash = (blk_num+1)%4; 
    
    for(auto i = HashQueue[hash].begin() ; i!= HashQueue[hash].end() ; i++){
        if(i->blk_num==blk_num){
            HashQueue[hash].erase(i);
            return;
        }
    } 
}


// search block in hash queue
bool searchHQ(int blk_num){
    int hash = (blk_num+1)%4;
    vector<bufferHeader> tmp = HashQueue[hash];
    
    for(auto bfheader = tmp.begin() ; bfheader!=tmp.end() ;bfheader++){
        if(bfheader->blk_num==blk_num){
            return true;
        }
    }
    return false;
}


// check hash queue is empty or not
bool emptyHQ(){
    return HashQueue.empty();
}


//---------------------FREELIST METHODS---------//

// add to tail in the freelist
void addToTailFL(int blk_num,int dNum,int status){
    bufferHeader *block = new bufferHeader(blk_num,dNum, status);
    freeList.push_back(*block);
}


// add to head in freelist
void addToHeadFL(int blk_num,int dNum,int status){
    bufferHeader *block = new bufferHeader(blk_num,dNum, status);
    freeList.insert(freeList.begin(),*block);
}


// delete from head in freelist
bufferHeader deleteToheadFL(){
    bufferHeader tmp;
    if(!emptyFL()){
        tmp = freeList[0];
        freeList.erase(freeList.begin());
    }
    return tmp;
}


// get the head content of freelist
bufferHeader getHeadToFL(){
    // if freelist is not empty then return head block otherwise, return dummy block
    return !freeList.empty() ? freeList[0] : *new bufferHeader(-1,-1,-1);
}


// delete from any position in freelist
bufferHeader deleteAnyPositionFL(int blk_num){
    bufferHeader tmp;
    for(auto i=freeList.begin() ; i!=freeList.end() ; i++){
        if(i->blk_num == blk_num){
            tmp = *i;
            freeList.erase(i);
            return tmp;
        }
    }
    return tmp;
}


// search block in freelist
bool searchFL(int blk_num){
    for(auto i=freeList.begin() ; i!=freeList.end() ; i++){
            if(i->blk_num == blk_num){
                return true;
            }
    }
    return false;
}


// display the block of freelist
void displayFL(){
    cout<<"\n-----------FREE_LIST-----------\n";
    auto it=freeList.begin();
    for(int j=0; j<16; j++){
        std::cout<<"->|"<<it->blk_num<<"|";
        it++;
    }
    std::cout<<"\n\n";
}
 

// check whether freelist is empty or not
bool emptyFL(){
    return freeList.empty();
}


// get status of the block
int getStatus(int blk_num){
    for(bufferHeader bh : HashQueue[(blk_num+1)%4]){
        if(bh.blk_num==blk_num){
            return bh.status;
        }
    }
}


// set status of the block
void setStatus(int blk_num, int sts){
    for(bufferHeader bh : HashQueue[(blk_num+1)%4]){
        if(bh.blk_num==blk_num){
            deleteFromHQ(blk_num);
            addToHQ(blk_num,1,sts);
            break;
        }
    }
}
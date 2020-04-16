#pragma once
#include<unordered_map>
#include<vector>

using namespace std;

class bufferHeader{
    public :
    // bock_number of data on disk
    int blk_num;

    // device_number specify the file system (for this program device_num = 1)
    int device_num;
    /*
      status :
      0 - locked
      1 - unlocked
      2 - valid data
      3 - delayed-write
      4 - kernel is reading/writing
      5 - process is waiting
    */
    int status;

    bufferHeader(int bnum, int dnum, int sts){
        blk_num = bnum;
        device_num = dnum;
        status = sts;
    }
    bufferHeader(){}
};


//---------------HashQueue functions---------
void addToHQ(int blk_num,int dNum,int status);
bool searchHQ(int blk_num);
int getStatus(int blk_num);
void setStatus(int blk_num, int sts);
void displayHQ();
void deleteFromHQ(int blk_num);
bool emptyHQ();

//---------------Freelist functions---------
void addToHeadFL(int blk_num,int dNum,int status);
void addToTailFL(int blk_num,int dNum,int status);
bool searchFL(int blk_num);
bufferHeader deleteToheadFL();
bufferHeader getHeadToFL();
bufferHeader deleteAnyPositionFL(int blk_num);
void displayFL();
bool emptyFL();
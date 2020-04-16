#include"commands.h"
#include"buffer.h"
#include<iostream>
#include<unistd.h>

//-----------------------GET BLOCK----------------------------
void getblk(int blk_num){
    setAlive(this_thread::get_id());

    while(1){
        if(searchHQ(blk_num)){
            if(getStatus(blk_num)==0){  //SCENERIO 5
                sleep(3);
                continue;
            }

            bufferHeader tmp = deleteAnyPositionFL(blk_num);
            if(tmp.status==3){           //SCENERIO 3
                sleep(20);
                addToHeadFL(tmp.blk_num,1,1);
                continue;
            }

            setStatus(blk_num,0);       //SCENERIO 1
            deleteAnyPositionFL(blk_num);
            break ;
        }else{
            if(emptyFL()){              //SCENERIO 4
                sleep(3);
                continue;
            }

            bufferHeader tmp = deleteToheadFL();
            if(tmp.status==3){           //SCENERIO 3
                sleep(20);
                addToHeadFL(tmp.blk_num,1,1);
                continue;
            }

            //SCENERIO 2
            deleteFromHQ(tmp.blk_num);
            addToHQ(blk_num,1,0);
            
            break;
        }
    }
    setDie(this_thread::get_id());
    cout<<"\nBlock Allocated !!\n";
}

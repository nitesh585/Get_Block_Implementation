#include"commands.h"
#include"buffer.h"
#include<iostream>
#include<thread>
#include<unistd.h>
#include<mutex>
#include <stdlib.h>

mutex mtx3;


//-----------------------GET BLOCK----------------------------
void getblk(int blk_num){
    

    //setAlive(this_thread::get_id());
    mtx3.lock();
        std::cout<<"\nProcess with id "<<this_thread::get_id()<<" starts Racing for buffer "<<blk_num<<endl;
    mtx3.unlock();
    while(1){
        //Scenario 5    
        if(searchHQ(blk_num)){
            
            if(getStatus(blk_num)==0){    
                mtx3.lock();
                    std::cout<<"\nCase 5: Buffer "<<blk_num<<" in HashQueue and Locked, So Process with id "<<this_thread::get_id()<<" is going to sleep\n";
                    sleep(10);
                    setAlive(this_thread::get_id());
                mtx3.unlock();
                continue;
            }
            
            //Scenario 1
            mtx3.lock();
                std::cout<<"\nCase 1: Buffer "<<blk_num<<" in HashQueue and not Locked , So Process with id "<<this_thread::get_id()<<" has taken that buffer\n";
                setStatus(blk_num,0); 
                deleteAnyPositionFL(blk_num);
            mtx3.unlock();
            break ;
        }else{

            //Scenario 4
            if(emptyFL()){  
                mtx3.lock();
                    std::cout<<"\nCase 4: Empty Free List , So Process with id "<<this_thread::get_id()<<" is going to sleep\n";                          
                    sleep(10);
                mtx3.unlock();
                continue;
            }
        
            //Scenario 3
            bufferHeader tmp = deleteToheadFL();
        
            if(tmp.status==3){  
                mtx3.lock();
                    std::cout<<"\nCase 3: Asynchronous Write to Disk is going on for buffer "<<tmp.blk_num<<" allocated to Process with id "<<this_thread::get_id()<<endl;         
                    
                    sleep(20);
                    
                    std::cout<<"\nCase 3: Asynchronous Write to Disk is Done for buffer "<<tmp.blk_num<<" allocated to Process with id "<<this_thread::get_id()<<endl;
                    addToHeadFL(tmp.blk_num,1,1);
                mtx3.unlock();
                continue;
            }

            //Scenario 2
            mtx3.lock();
                std::cout<<"\nCase 2: Buffer "<<blk_num<<" not in HashQueue , ";
                std::cout<<"So Process with id "<<this_thread::get_id()<<" is allocated Free buffer "<<tmp.blk_num<<endl;
                deleteFromHQ(tmp.blk_num);
                addToHQ(blk_num,1,0);
            mtx3.unlock();
            break;
        }
    }
    mtx3.lock();
        setDie(this_thread::get_id());
        std::cout<<"\nProcess with id "<<this_thread::get_id()<<" has completed its operation with buffer "<<blk_num<<endl;
        std::thread th(brelse, blk_num );
        th.detach();
    mtx3.unlock();
}

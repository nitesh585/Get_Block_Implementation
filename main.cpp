#include<unistd.h>
#include<iostream>
#include<vector>
#include<fstream>
#include<mutex>
#include<sys/types.h>
#include<sys/wait.h>
#include<thread>
#include"commands.h"
#include"buffer.h"
 
// clear command to clean the terminal
#define clear() printf("\033[H\033[J");
mutex mtx;

// Process list containing the  different thread
vector<thread> processList;

//  parse the input command into command and there parameters
vector<string> split(string str){
    vector<string> argv;

    string word="";
    for(short i=0; i<str.length() ; i++){
        if(str[i]==' '){
            argv.push_back(word);
            word="";
        }else{
             word+=str[i];
        }
    }
    argv.push_back(word);
    return argv;
}


void handle_process(string file){
    string block;
    ifstream fl(file);

    while(getline(fl,block)){
        getblk(stoi(block));
    }
    cout<<"PROCESS END !\n";
    cout<<"\n\n";
}


// execute the command given in the terminal 
void execute(vector<string> argv){  // argv - argument vector
    if(argv[0]=="echo"){           // if command is echo
        if(argv.size()==2){
        
            if(argv[1]=="processlist"){
                displayPL();
            }else{
                echo(argv[1]);    
            }

        }else{
            printf("%s","\nCommand not found.\n");
        }
    }else if(argv[0]=="clear"){
        clear();
    }else if(argv[0]=="help"){
        help();
    }else if(argv[0]=="process"){  // get block 
        
        if(argv.size()>=2){
            for(int i=1; i<argv.size(); i++){
                    // create a new thread and add it to the process list
                processList.emplace_back( thread(handle_process,argv[i]) );
                    // thread is joinable
                if(processList[processList.size()-1].joinable()){
                    // detach the thread ( run concurrently with the main function )
                    // main thread do not have to wait for these thread to complete
                    processList[processList.size()-1].detach();
                }
            }
        }

    }else{
        printf("%s","\nCommand not found.\n");	
	}
}


// loop function that runs the shell
void loop(){
    string command;
    vector<string> argv;

    do{
        cout<<"\nbufferCache> ";

        getline(cin,command); // get input command

        if(command=="") continue; // if nothing entered
        
        argv = split(command);
        
        if( argv[0]=="exit"){ // if command is exit then exit from  shell
            cout<<"\nGood Bye!!\n";
            break;
        }

        execute(argv);
        sleep(0.5);

    }while(1);
}


// Initial welcome message to show
void promptMsg(){
    cout<<"----------------------------------------------------\n";
    cout<<"|               WELCOME TO BUFFER CACHE            |\n";
    cout<<"----------------------------------------------------\n";
    cout<<"Type 'help' for help. Type 'clear' to clear the current input statement.\n\n";
}


// main function to start the shell
int main(){
    clear();
    promptMsg();
    init();
    loop();
}
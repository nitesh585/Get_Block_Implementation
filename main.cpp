#include<unistd.h>
#include<iostream>
#include<vector>
#include<sys/types.h>
#include<sys/wait.h>
#include<thread>
#include"commands.h"

// clear command to clean the terminal
#define clear() printf("\033[H\033[J");

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

// execute the command given in the terminal 
void execute(vector<string> argv){ // argv - argument vector
    if(argv[0]=="echo"){  // if command is echo
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
    }else if(argv[0]=="getblk"){  // get block 
        
        if(argv.size()==2){
            // create a new thread and add it to the process list
            processList.emplace_back( thread(getblk,stoi(argv[1])) );
            // thread is joinable
            if(processList[processList.size()-1].joinable()){
                // detach the thread ( run concurrently with the main function )
                // main thread do not have to wait for these thread to complete
                processList[processList.size()-1].detach();
            }
        }else{
            printf("%s","\nCommand not found.\n");
        }

    }else if(argv[0]=="brelse"){ // block release
        
        if(argv.size()==2){
            brelse(argv[1]);
        }else{
            printf("%s","\nCommand not found.\n");
        }

    }else if(argv[0]=="addblk"){ // add block
        
        if(argv.size()==3){
            addblk(argv[1],argv[2]);
        }else{
            printf("%s","\nCommand not found.\n");    
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

        cout<<"bufferCache> ";

        getline(cin,command); // get input command

        if(command=="") continue; // if nothing entered
        
        argv = split(command);
        
        if( argv[0]=="exit"){ // if command is exit then exit from  shell
            cout<<"\nGood Bye!!\n";
            break;
        }

        execute(argv);
        sleep(1);

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
    loop();
}
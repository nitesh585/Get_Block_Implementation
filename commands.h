#pragma once
#include<string>
#include<unordered_map>
#include<queue>
#include<thread>

using namespace std;

// defining the functions to handle the commands

void echo(string arg);
void displayPL();
void getblk(int blk_num);
void brelse(string blknum);
void addblk(string blk_num, string status);
void help();
void setAlive(thread::id id);
void setDie(thread::id id);
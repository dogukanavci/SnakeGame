//
//  main.cpp
//  SnakeGame
//
//  Created by Doğukan Avcı on 06/07/2018.
//  Copyright © 2018 dogukan avci. All rights reserved.
//

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <stdio.h>
#include <thread>
#include <chrono>

int score=0;
int fruitX=5;
int fruitY=6;
char input='n';

void SnakeDraw(std::vector <int> pos,int x,int y){
    int i=0;
    int size=pos.size();
    bool trg=false;
    while(i<size){
        if(x==pos.at(i)){
                if(y==pos.at(i+1)){
                    if(i==0)
                        std::cout<<"0";
                    else
                    std::cout<<"o";
                    trg=true;
                }
            }
        
        i=i+2;
    }
    if(!trg){
        std::cout<<" ";
    }
    
    
}
std::vector <int> SnakeUpdate(std::vector <int> &pos,bool &eaten){
    std::vector <int> instructions;
    std::vector<int>::iterator it;
    it=instructions.begin();
    instructions.insert(it, pos.begin(),pos.end());
    int size=pos.size();
    int lastY=pos.at(size-1);
    int lastX=pos.at(size-2);
    while(size>2){
        instructions.at(size-1)=pos.at(size-3);
        size--;
    }
    if(input=='d'){
        if(pos.at(0)>pos.at(2))
            instructions.at(1)=pos.at(1)-1;
        else if(pos.at(0)<pos.at(2))
            instructions.at(1)=pos.at(1)+1;
        else if(pos.at(1)>pos.at(3))
            instructions.at(0)=pos.at(0)+1;
        else if(pos.at(1)<pos.at(3))
            instructions.at(0)=pos.at(0)-1;
    }
    if(input=='n'){
        if(pos.at(0)>pos.at(2))
            instructions.at(0)=pos.at(0)+1;
        else if(pos.at(0)<pos.at(2))
            instructions.at(0)=pos.at(0)-1;
        else if(pos.at(1)>pos.at(3))
            instructions.at(1)=pos.at(1)+1;
        else if(pos.at(1)<pos.at(3))
            instructions.at(1)=pos.at(1)-1;
        
    }
    if(input=='a'){
        if(pos.at(0)>pos.at(2))
            instructions.at(1)=pos.at(1)+1;
        else if(pos.at(0)<pos.at(2))
            instructions.at(1)=pos.at(1)-1;
        else if(pos.at(1)>pos.at(3))
            instructions.at(0)=pos.at(0)-1;
        else if(pos.at(1)<pos.at(3))
            instructions.at(0)=pos.at(0)+1;
    }
    for(int ctr(0);ctr<pos.size()-1;ctr++){
        if(instructions.at(0)==pos.at(ctr) && instructions.at(1)==pos.at(ctr+1)){
            std::cout<<"YOU LOST"<<std::endl<<"Your Score is "<<score<<std::endl;
            exit(0);
        }
    }
    if(instructions.at(0)==fruitX && instructions.at(1)==fruitY){
        eaten=true;
        instructions.push_back(lastX);
        instructions.push_back(lastY);
        score++;
    }
    input='n';
    if(instructions.at(0)==20 || instructions.at(0)==-1 || instructions.at(1)==33 || instructions.at(1)==-1){
        std::cout<<"YOU LOST"<<std::endl<<"Your Score is "<<score<<std::endl;){
        std::cout<<"YOU LOST"<<std::endl<<"Your Score is "<<score<<std::endl;
        exit(0);
    }
    return instructions;
}
void LoadTable(std::vector <int> &instructions,bool &eaten){
    //instructions first element snake headx,second snake heady...
    instructions=SnakeUpdate(instructions,eaten);
    int row=20;
    int column=35;
    int ctr=0;
    if(eaten){
        fruitX=rand()%19;
        fruitY=rand()%34;
        eaten=false;
        
    }
    while(ctr<column){
        std::cout<<"_";
        ctr++;
    }
    std::cout<<std::endl;
    for(int i=0;i<row;i++){
        std::cout<<"|";
        for(int k=0;k<column-2;k++){
            if(i==fruitX && k==fruitY){
                std::cout<<"O";
                k++;
            }
            SnakeDraw(instructions, i, k);
        }
        std::cout<<"|"<<std::endl;
    }
    ctr=0;
    while(ctr<column){
        std::cout<<"_";
        ctr++;
    }
    std::cout<<std::endl;
}
void call(){
    std:: vector <int> ins= {3,5,2,5,1,5,0,5};
    bool eaten=true;
    while(1){
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        LoadTable(ins, eaten);
    }
}
void control(){
    system("stty raw");
    
    // Wait for single character
    while (input!='e') {
        input = getchar_unlocked();
    }
}

int main() {
    
    std::thread t (control);
    std::thread b (call);
    t.join();
    //control();
    
    system("stty cooked");
    // And we're out of here
    return 0;
}

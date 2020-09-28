#ifndef CONSTANTS_H
#define CONSTANTS_H

//for setting type of token to push and evaluate
const int _int = 1;
const int _function  = 2;
const int _operator = 3;
const int _variable = 4;
const int _token = 5;

//consts for precedence
const int sub=1;
const int add=1;
const int divide=2;
const int mult=2;
const int expon=3;
const int trigFun=4;

//consts for processing events
const int GORIGHT=6;
const int GOLEFT=7;
const int GOUP=8;
const int GODOWN=9;
const int IN=10;
const int OUT=11;
const int RESET=12;
const int NEW=13;
const int DELETE=14;
const int IDK=15;
const int IDK2=16;

//consts for window properties
const int SCREEN_WIDTH = 2400;
const int SCREEN_HEIGHT = 1350;
const float GRAPH_PANEl=(SCREEN_WIDTH*2.8/5)+700;
const float SIDE_BAR=SCREEN_WIDTH*2.2/5;

#endif // CONSTANTS_H

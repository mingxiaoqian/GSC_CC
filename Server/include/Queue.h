// MyQueue.cpp : 定义控制台应用程序的入口点。   
//实现链式队列（queue），包括一个头结点。队列操作包括在队头出队（pop）、在队尾入队（push）、   
//取得队头元素（front_element)、取得队尾元素（back_element）、队列元素个数（size）、   
//队列是否为空（empty）。   
//#include "stdafx.h"   
#include "LVS_define.h"
#include <iostream>   
  
using namespace std;  
//定义队列的节点结构   
//template <class T>  
struct NODE  
{  
    NODE* next;  
    LVS_UINT32 data;  
};  

class ChannelQueue
{	
private:  
	NODE* front; 	//指向头结点的指针。 front->next->data是队头第一个元素。   
	NODE* rear;		//指向队尾（最后添加的一个元素）的指针   

public:  
    ChannelQueue();
    void push(LVS_UINT32 e); 	//在队尾入队
	LVS_UINT32 pop();			//在队头出队           
    LVS_UINT32 front_element();	//取得队头元素
    LVS_UINT32 back_element(); 
    LVS_UINT32 size();			//取得队列元素个数  
    bool empty();   	//判断队列是否为空   
};


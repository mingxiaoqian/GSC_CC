// MyQueue.cpp : �������̨Ӧ�ó������ڵ㡣   
//ʵ����ʽ���У�queue��������һ��ͷ��㡣���в��������ڶ�ͷ���ӣ�pop�����ڶ�β��ӣ�push����   
//ȡ�ö�ͷԪ�أ�front_element)��ȡ�ö�βԪ�أ�back_element��������Ԫ�ظ�����size����   
//�����Ƿ�Ϊ�գ�empty����   
//#include "stdafx.h"   
#include "LVS_define.h"
#include <iostream>   
  
using namespace std;  
//������еĽڵ�ṹ   
//template <class T>  
struct NODE  
{  
    NODE* next;  
    LVS_UINT32 data;  
};  

class ChannelQueue
{	
private:  
	NODE* front; 	//ָ��ͷ����ָ�롣 front->next->data�Ƕ�ͷ��һ��Ԫ�ء�   
	NODE* rear;		//ָ���β�������ӵ�һ��Ԫ�أ���ָ��   

public:  
    ChannelQueue();
    void push(LVS_UINT32 e); 	//�ڶ�β���
	LVS_UINT32 pop();			//�ڶ�ͷ����           
    LVS_UINT32 front_element();	//ȡ�ö�ͷԪ��
    LVS_UINT32 back_element(); 
    LVS_UINT32 size();			//ȡ�ö���Ԫ�ظ���  
    bool empty();   	//�ж϶����Ƿ�Ϊ��   
};


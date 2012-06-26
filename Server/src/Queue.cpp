#include "Queue.h"

//template <class T>  

ChannelQueue::ChannelQueue()  
{  
    NODE* p = new NODE();  
    if (NULL == p)  
    {  
        cout << "Failed to malloc the node." << endl;  
    }  
    p->data = NULL;  
    p->next = NULL;  
    front = p;  
    rear = p;  
}  
  
//�ڶ�β���   
void ChannelQueue::push(LVS_UINT32 e)  
{  
    NODE* p = new NODE;  
    if (NULL == p)  
    {  
        cout << "Failed to malloc the node." << endl;  
    }  
    p->data = e;  
    p->next = NULL;  
    rear->next = p;  
    rear = p;  
}  
  
//�ڶ�ͷ����   
LVS_UINT32 ChannelQueue::pop()  
{  
    LVS_UINT32 e;  

    if (front == rear)  
    {  
        cout << "The queue is empty." << endl;  
        return NULL;  
    }  
    else  
    {  
        NODE* p = front->next;  
        front->next = p->next;  
        e = p->data;  
        //ע���жϵ�ֻ��һ��Ԫ�أ���ɾ����֮��rearָ���node��ɾ��   
        //Ӧ����ָ��ͷ���   
        if (rear == p)  
        {  
            rear = front;  
        }  
        delete p; p = NULL;  
        return e;  
    }  
}  
  
    //ȡ�ö�ͷԪ��   
LVS_UINT32 ChannelQueue::front_element()  
{  
    if (front == rear)  
    {  
        cout << "The queue is empty." << endl;  
        return NULL;  
    }  
    else  
    {  
        NODE* p = front->next;  
        return p->data;  
    }  
}  
  
LVS_UINT32 ChannelQueue::back_element()  
{  
    if (front == rear)  
    {  
        cout << "The queue is empty." << endl;  
        return NULL;  
    }  
    else  
    {  
        return rear->data;  
    }  
}  
  
    //ȡ�ö���Ԫ�ظ���   
LVS_UINT32 ChannelQueue::size()  
{  
    LVS_UINT32 count(0);  

    NODE* p = front;  

    while (p != rear)  
    {  
        p = p->next;  
        count++;  
    }  
    return count;  
}  
      
    //�ж϶����Ƿ�Ϊ��   
bool ChannelQueue::empty()  
{  
    if (front == rear)  
    {  
        return true;  
    }  
    else  
    {  
        return false;  
    }  
}  
  
/*
int main(int argc, char* argv[])  
{  
    MyQueue<int> myqueue;  
    cout << myqueue.size() << endl;  
    myqueue.push(10);  
	
    cout << myqueue.size() << endl;  
    myqueue.push(20);  
	
    cout << myqueue.size() << endl;  
    myqueue.push(30);  

    cout << myqueue.front_element() << endl;  
    cout << myqueue.back_element() << endl;  
    myqueue.pop();  
    if (myqueue.empty())  
    {  
        cout << "The queue is empty now." << endl;  
    }  
    else  
    {  
        cout << "The queue has " << myqueue.size() << " elements now." << endl;  
    }  
    myqueue.pop();  
    myqueue.pop();  
    if (myqueue.empty())  
    {  
        cout << "The queue is empty now." << endl;  
    }  
    else  
    {  
        cout << "The queue has " << myqueue.size() << " elements now." << endl;  
    }  
    return 0;  
}  
*/
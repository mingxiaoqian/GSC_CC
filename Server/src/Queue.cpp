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
  
//在队尾入队   
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
  
//在队头出队   
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
        //注意判断当只有一个元素，且删除它之后，rear指向的node被删除   
        //应将其指向头结点   
        if (rear == p)  
        {  
            rear = front;  
        }  
        delete p; p = NULL;  
        return e;  
    }  
}  
  
    //取得队头元素   
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
  
    //取得队列元素个数   
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
      
    //判断队列是否为空   
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
#include<iostream>
#include "list.cpp"

using namespace std;
template<class T>
class Queue
{
    List<T> lst;
public:
    bool push(T t)
    {
        return lst.endInsert(t);
    }
    bool pop(T* t)
    {
        return lst.begDelete(t);
    }
    bool is_Empty()
    {
        return (lst.getPtr()==NULL);
    }
    void display(){lst.display();}
};



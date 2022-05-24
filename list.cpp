#include<iostream>

using namespace std;

template<class T>
struct node
{
    T data;
    node* next=NULL;
};

template<class T>
class List
{
    node<T>* lst;
public:
    List()
    {
        lst=NULL;
    }
    node<T>* getPtr()
    {
        return lst;
    }
    bool begInsert(T x)
    {
        node<T>* n=new node<T>;
        if(n==NULL)
            return false;
        (n->data)=x;
        (n->next)=lst;
        lst=n;
        //cout<<lst<<;
        return true;
    }
    bool endInsert(T x)
    {
        node<T>* n=new node<T>;
        if(n==NULL)
            return false;
        n->data=x;
        node<T>* ntmp=lst;
        if(ntmp==NULL)
        {
            lst=n;
        return true;
        }
        while (ntmp->next!=NULL) ntmp=ntmp->next;
        ntmp->next=n;
        return true;
    }
    bool ins_bef(T x,node<T>* y)
    {
        node<T>* n=new node<T>;
        if((y==NULL)||(n==NULL))
            return false;
        n->next=y->next;
        y->next=n;
        n->data=y->data;
        y->data=x;
        return true;
    }
    bool ins_aft(node<T>* y, T x)
    {
        node<T>* n=new node<T>;
        if((y==NULL)||(n==NULL))
            return false;
        n->data=x;
        n->next=y->next;
        y->next=n;
        return true;
    }
    bool begDelete(T* t)
    {
        if(lst==NULL)
            return false;
        node<T>* ntmp=lst;
        lst=lst->next;
        *t=ntmp->data;
        delete ntmp;
        return true;
    }
    bool endDelete(T* t)
    {
        if(lst==NULL)
            return false;
        node<T>* ntmp=lst;
        if(lst->next==NULL)
        {
            lst=NULL;
            *t=ntmp->data;
            delete ntmp;
            return true;
        }
        while (ntmp->next->next!=NULL) ntmp=ntmp->next;
        *t=ntmp->next->data;
        delete (ntmp->next);
        ntmp->next=NULL;
        return true;
    }
    bool del_aft(node<T>* n, T* t)
    {
        if(n==NULL)
            return false;
        node<T>* ntmp=n->next;
        if(ntmp==NULL)
            return true;
        n->next=ntmp->next;
        *t=ntmp->data;
        delete ntmp;
        return true;
    }
    void display()
    {
        node<T>* n=lst;
        if(n==NULL)
        {
            cout<<"\n\t-->empty";
            return;
        }
        cout<<"\n\t[ ";
        while(n!=NULL)
        {//cout<<"yo";
            T t=n->data;
            cout<<t<<(((n=(n->next))==NULL)?" ]\n":" , ");
        }
    }
    bool khoja(node<T>** n,T t, int i=0)
    {
        if(i<=0)
            i=1;
        node<T>* ntmp=lst;
        int j=0;
        while(1)
        {
            if(ntmp==NULL)
                return false;
            if(ntmp->data==t)
                j++;
            if(j==i)
                break;
            ntmp=ntmp->next;
        }
        *n=ntmp;
        return true;
    }

};


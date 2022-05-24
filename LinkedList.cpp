#define LinkedList12xzx
#include<iostream>

using namespace std;

template <class T>
struct node
{
    T data;
    node* prev=NULL;
    node* next=NULL;
};

template <class T>
class LinkedList
{
    node<T> *dll, *nD;
    bool bhtau(T yo, node<T>** yesma)
    {
        node<T>* ntmp=dll;
        if(ntmp==NULL) return false;
        while(ntmp!=NULL)
        {
            if(ntmp->data==yo)
                break;
            else
                ntmp=ntmp->next;
        }
        if(ntmp==NULL) return false;
        *yesma=ntmp;
        return true;
    }
public:
    LinkedList()
    {
        dll=NULL;
        nD=NULL;
    }
    bool contains(T* yo)
    {
        node<T>* ntmp=dll;
        if(ntmp==NULL) return false;
        while(ntmp!=NULL)
        {
            if(&(ntmp->data)==yo)
                break;
            else
                ntmp=ntmp->next;
        }
        if(ntmp==NULL) return false;
        //*yesma=ntmp;
        return true;
    }
    bool beg_ins(T t)
    {
        node<T>* n=new node<T>;
        if(n==NULL) return false;
        n->data=t;
        if(dll!=NULL)
        {
            dll->prev=n;
            n->next=dll;
        }
        else
            nD=n;
        dll=n;
        return true;
    }
    bool end_ins(T t)
    {
        node<T>* n=new node<T>;
        if(n==NULL) return false;
        n->data=t;
        if(nD!=NULL)
        {
            nD->next=n;
            n->prev=nD;
        }
        else
            dll=n;
        nD=n;
        return true;
    }
    bool ins_aft(T n, T t)
    {
        node<T>* ntmp;
        if(!bhtau(n,&ntmp)) return false;
        node<T>* nn=new node<T>;
        nn->data=t;
        nn->prev=ntmp;
        nn->next=ntmp->next;
        if(ntmp->next==NULL)
            nD=nn;
        ntmp->next=nn;
    }
    bool ins_bef(T t, T n)
    {
        node<T>* ntmp;
        if(!bhtau(n,&ntmp)) return false;
        node<T>* nn=new node<T>;
        nn->data=t;
        nn->prev=ntmp->prev;
        nn->prev->next=nn;
        nn->next=ntmp;
        if(ntmp->prev==NULL)
            dll=nn;
        ntmp->prev=nn;
        return true;
    }

    bool del(T* t){
        node<T>* ndP=dll;
        node<T>* tmpNP=NULL;
        if (ndP==NULL)
            return false;
        do{
            if(&(ndP->data)==t){
                if(tmpNP==NULL)
                    beg_del(t);
                else{
                    tmpNP->next=ndP->next;
                    delete ndP;
                }
                return true;
            }
            tmpNP=ndP;
            ndP=ndP->next;
        }while(ndP!=NULL);
        return false;
    }

    bool beg_del(T* t)
    {
        node<T>* ntmp=dll;
        if(ntmp==NULL) return false;
        dll=dll->next;
        dll->prev==NULL;
        *t=ntmp->data;
        delete ntmp;
    }
    bool end_del(T* t)
    {
        node<T>* ntmp=nD;
        if(ntmp==NULL) return false;
        nD=nD->prev;
        nD->next=NULL;
        *t=ntmp->data;
        delete ntmp;
    }
    bool del_bef(T* t, T n)
    {
        node<T>* ntmp;
        if(!bhtau(n,&ntmp)) return false;
        if(ntmp->prev!=NULL)
        {
            node<T>* nn=ntmp->prev;
            ntmp->prev=nn->prev;
            if(nn->prev==NULL)
                dll=ntmp;
            else
                nn->prev->next=ntmp;
            *t=nn->data;
            delete nn;
        }
        return true;
    }
    bool del_aft(T n, T* t)
    {
        node<T>* ntmp;
        if(!bhtau(n,&ntmp)) return false;
        if(ntmp->next!=NULL)
        {
            node<T>* nn=ntmp->next;
            ntmp->next=nn->next;
            if(nn->next==NULL)
                nD=ntmp;
            else
                nn->next->prev=ntmp;
            *t=nn->data;
            delete nn;
            return true;
        }
    }
    void display()
    {
        node<T>* ntmp=dll;
        cout<<"\n[ ";
        if(dll==NULL)
        {
            cout<<"<-- empty --> ]";
            return ;
        }
        while(ntmp!=NULL)
        {
            cout<<ntmp->data<<((ntmp->next==NULL)?" ]":" , ");
            ntmp=ntmp->next;
        }
    }
};


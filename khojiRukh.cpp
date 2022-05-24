#define khojiRukh12xzx

#include <iostream>
#include <cmath>
#ifndef element12xzx
    #include "element.cpp"
#endif
#ifndef graph12xzx
#include "graph.cpp"
#endif

struct tag_List{
    g_node *gN;
    tag_List *next_tL;
};
struct khojiRukhNode{
    struct tag_List *tL;
    int bal;
    khojiRukhNode *dayan;
    khojiRukhNode *bayan;
};
bool operator<(g_node *gN, struct khojiRukhNode& kB);
bool operator==(g_node *gN, struct khojiRukhNode& kB);
bool operator<(string s, struct khojiRukhNode& kB);
bool operator==(string s, struct khojiRukhNode& kB);

class KhojiRukh{
    khojiRukhNode *root;
public:
    KhojiRukh(){
        root=NULL;
    }
    void insert(g_node *gN){
        if(root==NULL){
            root=getKRNptr(gN);
        }
        khojiRukhNode *nptr=root;
        khojiRukhNode *nptr2;
        while(nptr!=NULL){
            nptr2=nptr;
            if(gN < *nptr){
                nptr=nptr->bayan;
                if(nptr==NULL){
                    nptr2->bayan=getKRNptr(gN);
                }
            }
            else if(gN == *nptr){
                struct tag_List *tL=nptr->tL;
                struct tag_List *tL2=NULL;
                while(tL!=NULL){
                    tL2=tL;
                    if(gN->elm->getTag() == tL->gN->elm->getTag()){break;}
                    tL=tL->next_tL;
                }
                if(tL==NULL){
                    struct tag_List *nptr3 = new struct tag_List;
                    nptr3->gN=gN;
                    nptr3->next_tL=NULL;
                    tL2->next_tL=nptr3;;
                }
                break;
            }
            else{
                nptr=nptr->dayan;
                if(nptr==NULL){
                    nptr2->dayan=getKRNptr(gN);
                }
            }
        }
    }
    bool search_name(string name,struct tag_List **tLpptr){//cout<<"khojdai "<<name<<(root==NULL)<<"\n";
        khojiRukhNode *nptr=root;
        while(nptr!=NULL){//cout<<"ahile chain "<<nptr->tL->gN->elm->getName()<<"\n";
            if(name < *nptr){
                nptr=nptr->bayan;
            }
            else if(name == *nptr){
                *tLpptr=nptr->tL;
                return true;
            }
            else{
                nptr=nptr->dayan;
            }
        }
        return false;
    }
    struct khojiRukhNode * getKRNptr(g_node *gN){
            struct khojiRukhNode *nptr3 = new khojiRukhNode;
            struct tag_List *tLptr = new struct tag_List;
            tLptr->gN = gN;
            tLptr->next_tL=NULL;
            nptr3->tL=tLptr;
            nptr3->bayan=NULL;
            nptr3->dayan=NULL;
            
            return nptr3;
    }
};

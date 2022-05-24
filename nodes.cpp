#define nodes12xzx
#ifndef element12xzx
    #include "element.cpp"
#endif

#include <iostream>

struct g_node;

struct a_node{
    g_node* suNd;
    float wt;
    a_node* nextArc;
};

struct g_node{
    a_node* aN;
    Element* elm;
    g_node* next_gN;
    g_node* prev_gN;
    bool travsd;
    int id;
    g_node *prec;
    bool permanent;
    int wt;
    bool travsd2;
    bool highlight;
    g_node(){next_gN=prev_gN=NULL;aN=NULL;prec=NULL;travsd=travsd2=highlight=permanent=false;wt=-1;}
    ~g_node(){delete aN;}
};

struct fnd_List{
    g_node *gN;
    fnd_List *next_fnd;
};


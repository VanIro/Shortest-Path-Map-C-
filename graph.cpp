#define graph12xzx
#define WIDTH_FACTOR 15
#define NNUM 7
#define DEBUG_GRAPH false

#include <iostream>
#include<cmath>
/*#ifndef LinkedList12xzx
    #include "LinkedList.cpp"
#endif*/
#ifndef element12xzx
    #include "element.cpp"
#endif
#ifndef batoRukh12xzx
    #include "batoRukh.cpp"
#endif

#ifndef nodes12xzx
#include "nodes.cpp"
#endif
#include "queue_lst.cpp"


struct gNpWdst{
    g_node *gN;
    float wt;
    gNpWdst(){
        gN=NULL;
        wt=0;
    }
};
class Graph{
    Queue<struct gNpWdst> que;
    g_node* nodesB;
    g_node* nodesE;
    int ID;
    g_node* indices[NNUM];
    int ind_interval;
    batoRukh bR;
    bool Hflag;
public:
    Graph(){
        nodesB=nodesE=NULL;
        ID=0;
        for(int i=0;i<NNUM;i++){
            indices[i]=NULL;
        }
        Hflag=false;
        //ind_interval=;
    }
    bool isArc(g_node* from, g_node* to,a_node **aN2=NULL, g_node **gN2=NULL){
        a_node *aN = from->aN;
        g_node *gN;
        g_node *tmp_gN=NULL;
        while(aN!=NULL){
                gN=aN->suNd;
            while(gN->elm->isDummy()){
                tmp_gN=gN;
                gN=gN->next_gN;
            }
            if(gN==to){
                if(aN2!=NULL) *aN2=aN;
                if(gN2!=NULL) *gN2=tmp_gN;
                if(DEBUG_GRAPH)cout<<"graph.isArc(): yes\n";
                return true;
            }
            aN=aN->nextArc;
        }
        return false;
    }
    void draw(sf::RenderWindow& win, g_node *gN=NULL){
        /*g_node* aaa=nodesB;
        cout<<"Graph.draw():\n";
        while(aaa!=NULL){
            cout<<"\t"<<(aaa)->elm->getName()<<"! -> ";
            a_node* papa=aaa->aN;
            while(papa!=NULL){
                cout<<", to "<<papa->suNd->elm->getName();
                papa=papa->nextArc;
            }cout<<"\n";
            aaa=aaa->next_gN;
        }*/
        g_node* tmpGndP=(gN==nodesB)?nodesB->next_gN:nodesB;
        a_node* tmpAndP;
        struct gNpWdst tmpStr;
        tmpStr.gN=(gN==NULL)?nodesB:gN;
        tmpStr.wt=0;
        //traversal of graph begin
        while(tmpStr.gN!=NULL){//cout<<"\ngraph 89"<<tmpStr.gN->elm->getName()<<" <--> "<<tmpStr.gN->travsd;
            if(!((tmpStr.gN)->travsd)){
                que.push(tmpStr);
                //traversal of a connected component begin
                while(!que.is_Empty()){
                    que.pop(&tmpStr);
                    if(DEBUG_GRAPH)cout<<"graph.draw(): popped "<<tmpStr.gN->elm->getName()<<"\n";
                    if(((tmpStr.gN)->travsd)!=true){//not required
                        //((tmpStr.gN)->elm)->draw(win);
                        //cout<<"Graph.draw() : <traversing for paths>"<<(tmpStr.gN)->elm->getName()<<"\n";
                        (tmpStr.gN)->travsd=true;//cout<<(tmpStr.gN)->elm->getName()<<"! | ";
                        tmpAndP=(tmpStr.gN)->aN;
                        while(tmpAndP!=NULL){
                            if(DEBUG_GRAPH)cout<<"graph.draw(): tmpAndP!=NULL<next>?"<<(tmpAndP->nextArc==NULL)<<"\n";
                            struct gNpWdst tmp;
                            if( true/*tmpAndP->suNd->travsd != true*/ ){//so that path is not drawn twice
                                tmp.wt+=tmpAndP->wt;
                                g_node *A;
                                g_node *B;
                                A=tmpStr.gN;
                                B=tmpAndP->suNd;
                                while(B->elm->isDummy()){
                                    drawPath(A->elm, B->elm, win,(B->prec == A));
                                    A=B;
                                    B=B->next_gN;
                                }
                                drawPath(A->elm,B->elm,win,(B->prec == A));
                                tmp.gN=B;
                                que.push(tmp);
                                if(DEBUG_GRAPH)cout<<"graph.draw(): pushed "<<tmp.gN->elm->getName()<<"\n";
                            }
                            if(DEBUG_GRAPH)cout<<"graph.draw(): popped tira7"<<((tmpAndP==NULL)?"7":tmpAndP->suNd->elm->getName())<<"\n";
                            tmpAndP=tmpAndP->nextArc;
                        }

                    }
                    if(DEBUG_GRAPH)cout<<"graph.draw(): popped tira\n ";
                }//traversal end
            }
            tmpStr.gN=tmpGndP;
            //tmpStr.wt
            if(tmpGndP!=NULL)tmpGndP=tmpGndP->next_gN;
        }//traversal of graph end
        tmpGndP = nodesB;
        while(tmpGndP!=NULL){
            if(tmpGndP->travsd){
                if(DEBUG_GRAPH)cout<<"Graph.draw() : drawing"<<tmpGndP->elm->getName()<<"\n";
                tmpGndP->elm->draw(win);
                tmpGndP->travsd=false;//too soon
            }
            else
                tmpGndP->elm->draw(win);
            tmpGndP = tmpGndP->next_gN;
        }
    }
    void drawPath(Element* A, Element* B, sf::RenderWindow& rw, bool hL){
        float Av[2], Bv[2];
        A->getLocation(Av);
        B->getLocation(Bv);
        sf::Vector2u wnSz=rw.getSize();
        float length=pow(
                            pow((Av[0]-Bv[0])*wnSz.x,2) + pow((Av[1]-Bv[1])*wnSz.y,2)
                        ,.5);
        float width=(((wnSz.x<wnSz.y)?wnSz.x:wnSz.y)/float(800))*WIDTH_FACTOR*.6;
        float angle=atan2(Bv[1]-Av[1], ((Bv[0]-Av[0])!=0)?(Bv[0]-Av[0]):0.0001);
        sf::RectangleShape road(sf::Vector2f(length,width));
        road.setOrigin(0,width/2);
        road.setRotation(angle*180/3.1416);
        if(hL){
            road.setFillColor(sf::Color(255,255,0,150));
        }
        else{
            road.setFillColor(sf::Color(255,0,0,150));
        }
        road.setPosition(Av[0]*wnSz.x/*+WIDTH_FACTOR*.9*/,Av[1]*wnSz.y/*+WIDTH_FACTOR*.9*/);
        if(DEBUG_GRAPH)cout<<"graph.drawPath() : "<<A->getName()<<" to "<<B->getName()<<"\n";
        rw.draw(road);
    }
    bool shrtst_path(g_node *from, g_node *to){
        bR.seed(from , to);
        bool b=false;
        while(bR.advance(to,&b)){//cout<<"b= "<<b<<"\n";
            if(b==true){
                g_node *through1;
                through1=to;
                while(true){
                    if(through1 == from)
                        break;
                    through1->permanent=true;
                    //cout<<through1->elm->getName()<<(through1->prec==NULL)<<through1->prec->elm->getName()<<" <- ";
                    through1=through1->prec;
                }
                bR.reset(true);
                return true;
            }
        }
        bR.reset(true);
        return false;
    }
    void end_shPath(){
        Hflag=false;
        bR.reset(false);
    }
    bool addArc(g_node* Gfrom, g_node* Gto, float wt){
        //check-valid ptr args
        float aav[2],bbv[2];
        Gfrom->elm->getLocation(aav);
        Gfrom->elm->getLocation(aav);
        
        //floatwt=
        a_node* A=new a_node;
        A->wt=wt;
        A->suNd=Gto;
        A->nextArc=NULL;
        a_node* aN=Gfrom->aN;
        a_node* tmpnd;
        if(aN==NULL){
            Gfrom->aN=A;
            return true;
        }
        else
            do{
                if(aN==NULL || aN->wt>=wt)
                {//an amazing fix was done here
                    A->nextArc=aN;
                    tmpnd = nullptr;
                    if(tmpnd==NULL)
                        Gfrom->aN=A;
                    else
                        tmpnd->nextArc=A;
                    //cout<<"Graph.addArc(): added to"<<A->suNd->elm->getName()<<(aN==NULL)<<"\n";
                    return true;
                }
                tmpnd=aN;
                aN=aN->nextArc;
            }while(true);
        return false;
    }
    bool removeArc(g_node* Gfrom, g_node* Gto, int num=0){
        a_node* aN=Gfrom->aN;
        a_node* tmpnd=NULL;
        if(aN==NULL){
            return false;
        }
        else
            do{
                if(aN==NULL)
                {
                    return false;
                }
                else if(aN->suNd==Gto){
                    if(num==0)
                        if(tmpnd==NULL){
                            Gfrom->aN=NULL;
                            delete aN;
                            return true;
                        }
                    else{
                        num--;
                    }
                }
                tmpnd=aN;
                aN=aN->nextArc;
            }while(true);
    }
    g_node* addNode(Element* elm, g_node *sururu){//cout<<elm->getName()<<"&\n";
        g_node* gN=new g_node;
        gN->elm=elm;
        addNode(gN, sururu);
        return gN;
    }
    bool removeNode(g_node* g){
        g_node* tmpnd1=NULL;
        g_node* tmpnd2=NULL;
        if(nodesB==NULL){
            return false;
        }
        else{
            tmpnd1=nodesB;
            do{
                if(tmpnd1==NULL)
                {
                    return false;
                }
                else if(tmpnd1==g){
                    if(tmpnd2==NULL){
                        nodesB=nodesB->next_gN;
                    }
                    else
                        tmpnd2->next_gN=tmpnd1->next_gN;
                    delete tmpnd1;
                }
                tmpnd2=tmpnd1;
                tmpnd1=tmpnd1->next_gN;
            }while(true);
        }
    }
    void nodes_rearr(g_node* gN){if(DEBUG_GRAPH)cout<<"\ngraph.nodes_rearr : in";
        float X = gN->elm->getX();
        g_node* gN2;
        gN2 = gN->next_gN;
        if(gN2 != NULL && gN2->elm->getX()<X){if(DEBUG_GRAPH)cout<<"\ngraph.nodes_rearr : to right";
            gN2->prev_gN = gN->prev_gN;
            if(gN->prev_gN != NULL){
                gN->prev_gN->next_gN = gN2;
            }
            else{
                nodesB = gN2;
                //cout<<"\ngraph.nodes_rearr : nodesB moved";
            }
            gN2=gN2->next_gN;
            while(gN2!=NULL && gN2->elm->getX()<X){gN2=gN2->next_gN;}
            if(gN2!=NULL && gN2->elm->getX() == X)//so that we dont have to change indices for equal x
                gN2=gN2->next_gN;
            gN->next_gN = gN2;
            if(gN2!=NULL){
                gN2->prev_gN->next_gN = gN;
                gN->prev_gN = gN2->prev_gN;
                gN2->prev_gN = gN;
            }
            else{
                gN->prev_gN = nodesE;
                nodesE->next_gN = gN;
                nodesE=gN;
            }
            //gN2->prev_gN->next_gN = gN;
            //gN2->prev_gN will not ever be null
            /*if(gN2->prev_gN !=NULL){
                gN2->prev_gN->next_gN = gN;
            }
            else
                nodesB = gN;
            */
        }
        else{
            gN2=gN->prev_gN;
            if(gN2 != NULL && gN2->elm->getX()>X){if(DEBUG_GRAPH)cout<<"\ngraph.nodes_rearr : to left";
                gN2->next_gN = gN->next_gN;
                if(gN->next_gN != NULL){
                    gN->next_gN->prev_gN = gN2;
                }
                else nodesE = gN2;
                gN2=gN2->prev_gN;
                while(gN2!=NULL && gN2->elm->getX()>X){gN2=gN2->prev_gN;}
                gN->prev_gN = gN2;
                if(gN2!=NULL){
                    gN->next_gN = gN2->next_gN;
                    gN2->next_gN->prev_gN=gN;
                    gN2->next_gN = gN;
                }
                else{
                    gN->next_gN=nodesB;
                    nodesB->prev_gN = gN;
                    nodesB=gN;
                }
                /*if(gN2->next_gN !=NULL){
                    gN2->next_gN->prev_gN = gN;
                }
                else
                    nodesE = gN;
                */
            }
        }
        if(DEBUG_GRAPH){cout<<"\ngraph.nodes_rearr : ";if(gN->prev_gN!=NULL)cout<<gN->prev_gN->elm->getX()<<" ";cout<<" | "<<gN->elm->getX()<<" | ";if(gN->next_gN!=NULL)cout<<gN->next_gN->elm->getX();}
    }
    g_node* get_nodesB_786(){return nodesB;}
    private:
    void addNode(g_node *g, g_node* gN=NULL){
        g->id=ID++;
        g_node *gN2=NULL;
        if(gN==NULL)
            gN=nodesB;
        /*
        if(nodesB==NULL)
            nodesB=nodesE=g;
        else{
            nodesE->next_gN=g;
            g->next_gN=NULL;
            nodesE=g;
        }
        */
        ///*

        while(gN!=NULL && (gN->elm->getX() < g->elm->getX())){
            gN2=gN;
            gN=gN->next_gN;
            if(DEBUG_GRAPH)cout<<(gN==NULL)<<"\n";
        }
        if(gN2==NULL){
            g->next_gN = gN;// or nodesB
            nodesB=g;
            g->prev_gN = NULL;
        }
        /*if(gN2==NULL){
            nodesB=nodesE=g;
            g->next_gN=NULL;
        }*/
        else{
            if(DEBUG_GRAPH)std::cout<<g->elm->getName()<<"attha!2\n";
            gN2->next_gN=g;
            g->prev_gN = gN2;
            g->next_gN=gN;
        }
        if(gN==NULL){
            nodesE=g;
            g->next_gN=NULL;
        }
        else
            gN->prev_gN = g;
        //*/
    }

};

/*struct batoNd{
    g_node *gN;//parent?
    float wt;
    batoNd *next;
};


class batoRukh{
    struct batoNd *prQ;
public:
    void insert(g_node *gN, float wt){
        if(! gN->travsd ){
            //gN->travsd=true;
            struct batoNd *newTmp=new struct batoNd;
            newTmp->gN=gN;
            newTmp->wt=wt;
            if(prQ==NULL){
                newTmp->wt=0;
                prQ=newTmp;
                return;
            }
            struct batoNd *tmp=prQ;
            struct batoNd *tmp2=NULL;
            while(tmp != NULL){
                if(tmp->wt > wt){
                    if(tmp2 == NULL){
                        prQ=newTmp;
                    }
                    newTmp->next=tmp;
                    break;
                }
                else if(tmp->wt == wt && gN==tmp->gN){
                    if (wt<t)
                }
                tmp2=tmp;
                tmp=tmp->next;
            }
            if(tmp==NULL){
                tmp2->next=newTmp;
            }
            }
            else{
                while(tmp != NULL){
                    if(tmp->gN==gN){

                    }
                    tmp=tmp->next;
                }
            }
        }
    }
    bool pop(struct batoNd **ynha){
        if(prQ==NULL)
            return false;
        *ynha=prQ;
        prQ=prQ->next;
    }
    bool advance(){
        batoNd *tmp;
        if(!pop(&tmp))
            return false;
            tmp->gN->travsd=true;
        a_node *Atmp=tmp->gN->aN;
        while(Atmp != NULL){
            if( (! Atmp->suNd->travsd) ){
                if(Amp->suNd->wt == -1){
                    Atmp->suNd->prec=tmp->gN;
                    this->insert(Atmp->suNd,tmp->wt+Atmp->wt);
                }
                else {
                    if(gN->wt > tmp->wt+Atmp->wt){
                        Atmp->suNd->prec=tmp->gN;
                        Atmp->
                    }
                }
            }
            Atmp=Atmp->nextArc;
        }
    }
};
*/

/*
struct batoNd{
    g_node *gN;
    batoNd *left, *right;
    batoNd(){
        left=right=NULL;
    }
};

struct fnd_List{
    g_node *gN;
    fnd_List *next_fnd;
};
class batoRukh{
    struct batoNd *prQ;
    //struct batoNd *iN1;
    struct fnd_List *fnL;
    bool iNpre=true;
public:
    void insert(batoNd *bN){
        if(! bN->gN->travsd2 ){
            if(prQ==NULL){
                prQ=bN;
                return;
            }
            struct batoNd *tmp=prQ;
            struct batoNd *tmp2=NULL;
            while(tmp != NULL){
                tmp2=tmp;
                if(tmp->gN->wt > bN->gN->wt){
                    tmp=tmp->left;
                    if(tmp==NULL){
                        tmp2->left=bN;
                    }
                }
                else{
                    tmp=tmp->right;
                    if(tmp==NULL){
                        tmp2->right=bN;
                    }
                }
            }
        }
    }
    bool advance(g_node *destiN, bool *bhettiyo){
        batoNd *tmp;
        if(!pop(&tmp))
            return false;

        tmp->gN->travsd2=true;
        //later to make this travsd2s  false
        struct fnd_List *tmp_fnl = new struct fnd_List;
        tmp_fnl->gN = tmp->gN;
        if(fnL==NULL){
            fnL=tmp_fnl;
            tmp_fnl->next_fnd = NULL;
        }
        else{
            tmp_fnl->next_fnd=fnL;
            fnL=tmp_fnl;
        }

        a_node *Atmp=tmp->gN->aN;
        while(Atmp != NULL){
            if(Atmp->suNd == destiN){
                destiN->prec = tmp->gN;
                *bhettiyo = true;
            }
            if( (! Atmp->suNd->travsd) ){
                if(Atmp->suNd->wt == -1){
                    Atmp->suNd->wt = tmp->gN->wt + Atmp->wt;
                    Atmp->suNd->prec=tmp->gN;
                    batoNd *BndP=new struct batoNd;
                    BndP->gN=Atmp->suNd;
                    BndP->gN->wt = tmp->gN->wt + Atmp->wt;
                    BndP->gN->prec=tmp->gN;
                    this->insert(BndP);
                }
                else {
                    if(Atmp->suNd->wt > tmp->gN->wt + Atmp->wt){
                        batoNd *BndP;
                        this->remove(Atmp->suNd,&BndP);
                        BndP->gN->wt = tmp->gN->wt + Atmp->wt;
                        BndP->gN->prec=tmp->gN;
                        this->insert(BndP);
                    }
                }
            }
            Atmp=Atmp->nextArc;
        }
    }
private:

    bool pop(struct batoNd **ynha){
        if(prQ==NULL)
            return false;
        struct batoNd *tmp=prQ;
        struct batoNd *tmp2=NULL;
        while(1){
            if(tmp->left == NULL){
                if(tmp2==NULL){
                    prQ=tmp->right;
                }
                else{
                    tmp2->left = tmp->right;
                }
                *ynha=tmp;
                return true;
            }
            tmp2=tmp;
            tmp=tmp->left;
        }
    }
    bool remove(g_node *gN, batoNd **bNpp){
        struct batoNd **Bpp=NULL;//related to left or right son
        struct batoNd *tmp=prQ;
        struct batoNd *tmp2=NULL;
            while(tmp != NULL){
                if(tmp->gN->wt > gN->wt){
                    tmp2=tmp;
                    tmp=tmp->left;
                    Bpp=&(tmp2->left);
                    if(tmp==NULL){
                        return false;
                    }
                }
                else{
                    if(tmp->gN == gN){
                        *bNpp=tmp;
                    //delete
                        batoNd *left=tmp->left;
                        batoNd *right=tmp->right;
                        if(iNpre){
                            batoNd *tmp3=left;
                            batoNd *tmp4=NULL;
                            while(tmp3!=NULL){
                                if(tmp3->right == NULL){
                                    if(tmp4==NULL){
                                        if(tmp2==NULL){
                                            prQ=tmp3;
                                        }
                                        else{
                                            *Bpp=tmp3;
                                        }
                                        tmp3->right=right;
                                        return true;
                                    }
                                    else{
                                        if(tmp2==NULL){
                                            prQ=tmp3;
                                        }
                                        else{
                                            *Bpp=tmp3;
                                        }
                                        tmp3->left=left;
                                        tmp3->right=right;
                                        tmp4->right=NULL;
                                    }
                                }
                                tmp4=tmp3;
                                tmp3=tmp3->right;
                            }
                            iNpre=false;
                        }
                        else{
                            //
                            batoNd *tmp3=right;
                            batoNd *tmp4=NULL;
                            while(tmp3!=NULL){
                                if(tmp3->left == NULL){
                                    if(tmp4==NULL){
                                        if(tmp2==NULL){
                                            prQ=tmp3;
                                        }
                                        else{
                                            *Bpp=tmp3;
                                        }
                                        tmp3->left=left;
                                        return true;
                                    }
                                    else{
                                        if(tmp2==NULL){
                                            prQ=tmp3;
                                        }
                                        else{
                                            *Bpp=tmp3;
                                        }
                                        tmp3->left=left;
                                        tmp3->right=right;
                                        tmp4->left=NULL;
                                    }
                                }
                                tmp4=tmp3;
                                tmp3=tmp3->left;
                            }
                            //
                            iNpre=true;
                        }
                        return true;
                    }
                    tmp2=tmp;
                    tmp=tmp->right;
                    Bpp=&(tmp2->right);
                    if(tmp==NULL){
                        return false;
                    }
                }
            }
    }
};*/

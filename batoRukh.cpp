#define batoRukh12xzx
#define DEBUG_batoRukh
#include <iostream>
#include <cmath>
#ifndef element12xzx
    #include "element.cpp"
#endif
#ifndef nodes12xzx
#include "nodes.cpp"
#endif


struct batoNd{
    g_node *gN;
    batoNd *left, *right;
    batoNd(){
        left=right=NULL;
    }
};
class batoRukh{
    struct batoNd *prQ;
    //struct batoNd *iN1;
    struct fnd_List *fnL;
    bool iNpre;
    bool should_pop;
    g_node *from, *to;
    batoNd *tmp;
    a_node *Atmp;
public:
    batoRukh(){
        prQ=NULL;
        fnL=NULL;
        iNpre=true;
        should_pop=true;
        from=to=NULL;
    }
    void seed(g_node *gN, g_node *gN2){
        cout<<"batoRukh.seed() : "<<gN->elm->getName()<<" to "<<gN2->elm->getName()<<"\n";
        from=gN;
        to=gN2;
        batoNd *bN=new struct batoNd;
        bN->gN=gN;
        bN->gN->wt=0;
        this->insert(bN);
    }
    void insert(batoNd *bN){
        cout<<"batoRukh.insert() : inserting "<<bN->gN->elm->getName()<<" traversd2 is null ?"<<bN->gN->travsd2<<"  prQ is null ?"<<(prQ==NULL)<<"\n";
        if(! bN->gN->travsd2 ){
            if(prQ==NULL){
                prQ=bN;
                cout<<"batoRukh.insert() : inserted as root and root is null ?"<<(prQ==NULL)<<"\n";
                return;
            }
            struct batoNd *tmp=prQ;
            struct batoNd *tmp2=NULL;
            while(tmp != NULL){
                tmp2=tmp;
                if(tmp->gN->wt > bN->gN->wt){
                    tmp=tmp->left;
                    if(tmp==NULL){
                        cout<<"batoRukh.insert() : inserted as left\n";
                        tmp2->left=bN;
                    }
                }
                else{
                    tmp=tmp->right;
                    if(tmp==NULL){
                        cout<<"batoRukh.insert() : inserted as right\n";
                        tmp2->right=bN;
                    }
                }
            }
        }
    }
    bool advance(g_node *destiN, bool *bhettiyo){
        //cout<<"batoRukh.advance() : advancing prQ is null ?"<<(prQ==NULL)<<"\n";
        *bhettiyo=false;
        if(should_pop){
            if(!pop(&tmp))
                return false;
            cout<<"batoRukh.advance() : popped "<<(tmp->gN->elm->getName())<<"\n";
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
            //cout<<"batoRukh.advance() : adding to fnL "<<tmp->gN->elm->getName()<<
                //((tmp_fnl->next_fnd==NULL)?" true ":tmp_fnl->next_fnd->gN->elm->getName())<<"\n";
            //cout<<"batoRukh.advance() : (2) advancing prQ is null ?"<<(prQ==NULL)<<"\n";
            Atmp=tmp->gN->aN;
        }
        else{should_pop=true;}
        while(Atmp != NULL){
            if(Atmp->suNd == destiN){
                destiN->prec = tmp->gN;
                *bhettiyo = true;
                std::cout<<"batoRukh.advance() : bhettiyo"<<Atmp->suNd->elm->getName()<<"/\\ \n";
                Atmp=Atmp->nextArc;
                should_pop=false;
                return true;
            }
            if( (! Atmp->suNd->travsd) ){cout<<Atmp->suNd->elm->isDummy()<<"wt = "<<Atmp->suNd->wt<<"\n";
                if(Atmp->suNd->wt == -1){
                    Atmp->suNd->wt = tmp->gN->wt + Atmp->wt;
                    Atmp->suNd->prec=tmp->gN;
                    batoNd *BndP=new struct batoNd;
                    BndP->gN=Atmp->suNd;
                    BndP->gN->wt = tmp->gN->wt + Atmp->wt;
                    BndP->gN->prec=tmp->gN;
                    std::cout<<"first time\n";
                    this->insert(BndP);
                }
                else {
                    if(Atmp->suNd->wt > tmp->gN->wt + Atmp->wt){std::cout<<"edditing time\n";
                        batoNd *BndP;
                        this->remove(Atmp->suNd,&BndP);
                        BndP->gN->wt = tmp->gN->wt + Atmp->wt;
                        BndP->gN->prec=tmp->gN;
                        this->insert(BndP);
                    }
                }
            }
            Atmp=Atmp->nextArc;
            std::cout<<"firime"<<(Atmp==NULL)<<"\n";
            if(Atmp!=NULL)cout<<"hero hero : "<<Atmp->suNd->elm->getName()<<"\n";
        }
        return true;
    }
    bool reset(bool first){
        cout<<"batoRukh.reset() : first?"<<first<<"\n";
        if(first){
            if(fnL==NULL)
                return false;
            fnd_List *tmpFnl=fnL;
            while(fnL != NULL){
                tmpFnl=fnL;
                fnL=fnL->next_fnd;
                tmpFnl->gN->travsd2=false;
                tmpFnl->gN->wt = -1;
                //cout<<"batoRukh.reset() : fnL "<<tmpFnl->gN->elm->getName()<<(fnL==NULL)<<"\n";
                if(!(tmpFnl->gN->permanent)){
                    tmpFnl->gN->prec=NULL;
                }
                delete tmpFnl;
            }
            batoNd * tree=prQ;
            post_trav_del(tree);
            prQ=NULL;
        }
        else{//cout<<"sldk;jfla;djflkjdflk;j";
            if(to==NULL){return false;}
            g_node *Gtmp;cout<<"batoRukh.reset() : setting prec to null of "<<to->elm->getName()<<"\n";
            while(to != from && to!=NULL){
                Gtmp=to;
                to=to->prec;
                cout<<"batoRukh.reset() : setting prec to null of "<<Gtmp->elm->getName()<<"1212\n";
                Gtmp->prec=NULL;
                Gtmp->permanent=false;
            }
            to=from=NULL;
        }
    }
    void post_trav_del(batoNd *tree){cout<<"batoRukh.post_trav_del() : "<<(tree==NULL)<<"\n";
        if(tree == NULL)
            return;
        batoNd *left = tree->left;
        post_trav_del(left);
        batoNd *right = tree->right;
        post_trav_del(right);
        cout<<"batoRukh.post_trav_del() : traversing through "<<tree->gN->elm->getName()<<"\n";
        tree->gN->wt=-1;
        tree->gN->prec=NULL;
        delete tree;
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
    
};

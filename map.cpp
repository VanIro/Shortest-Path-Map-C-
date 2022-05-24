#define NNUM 7
#define OK_ELM_AROUND 1
#define DEBUG_MAP false

#include <iostream>
#include <cmath>
#ifndef element12xzx
    #include "element.cpp"
#endif
#ifndef graph12xzx
#include "graph.cpp"
#endif
#ifndef khojiRukh12xzx
    #include "khojiRukh.cpp"
#endif
#include<SFML/graphics.hpp>

class Map{
    Graph graph;
    float gnd_area[2];
    float win_area[2];
    float scale[2];
    sf::RenderWindow w;
    g_node *indices[NNUM];
    g_node *active_gN;
    g_node *active_gN2;
    float interval;
    sf::Clock doub_clk_clock;
    KhojiRukh rukh;
public:
    Map(float gx, float gy){
        gnd_area[0]=gx;
        gnd_area[1]=gy;
        win_area[1]=sf::VideoMode::getFullscreenModes()[0].height;
        win_area[0]=sf::VideoMode::getFullscreenModes()[0].width;
        scale[0]=win_area[0]/gnd_area[0];
        scale[1]=win_area[1]/gnd_area[1];
        w.setTitle("Me hun map!");
        //w.create(sf::VideoMode(300,300),,sf::Style::Default);
        w.setVisible(false);
        for(int i=0;i<NNUM;i++){
            indices[i]=NULL;
        }
        interval=(gnd_area[0]/float(win_area[0]))/float(NNUM);
        active_gN=NULL;
        active_gN2=NULL;
    }
    bool makeActive(bool b, g_node *gN=NULL){//cout<<"makeActive()!!\n";
        if(b){//cout<<"B!!\n";
            if(active_gN!=gN){
                if(gN == active_gN2){
                    active_gN2->elm->setClicked(false);
                    active_gN2 = NULL;
                }
                else{//cout<<"A!!\n";
                    if(active_gN2 != NULL){
                        active_gN2->elm->setClicked(false);
                    }
                    active_gN2=active_gN;
                    active_gN=gN;
                    active_gN->elm->setClicked(true);
                }
                //doub_clk_clock.restart();cout<<"\nmap.makeActive() count 1\n";
            }
            else{
                active_gN->elm->setClicked(false);
                active_gN = active_gN2;
                active_gN2 = NULL;
                /*if(doub_clk_clock.getElapsedTime().asMilliseconds()<800){
                    cout<<"\nmap.makeActive() count 2\n";
                    if(active_gN!=NULL)
                        return 2;
                    else
                        return -2;
                }*/
            }
            if(active_gN != NULL)
                return true;
        }
        else{
            if(active_gN2 != NULL){
                active_gN2->elm->setClicked(false);
                active_gN2=NULL;
            }
            if(active_gN != NULL){
                active_gN->elm->setClicked(false);
                active_gN=NULL;
            }
        }
        return false;
    }
    bool getAround_gN(g_node **gN,float x,float y){//cout<<"////getAround()!!\n";
        int i=x*NNUM;//cout<<i<<" <"<<x<<" , "<<y<<"> yess \n";
        g_node* gN2=indices[i];
        sf::Vector2u wnSz=w.getSize();
        float win_scale=((wnSz.x<wnSz.y)?wnSz.x:wnSz.y)/float(800);
        float ok_elm_rad[2] = {OK_ELM_AROUND*win_scale*THE_RAD/float(wnSz.x),
                                OK_ELM_AROUND*win_scale*THE_RAD/float(wnSz.y)
                              };
        //cout<<"map.getAround_gN() : "<<"\n\tok_elm_rad = "<<ok_elm_rad[0]<<","<<ok_elm_rad[1]<<" / "<<win_scale*THE_RAD;
        //cout<<"\n\t klkx = "<<x<<" klky = "<<y<<"\n";
        if(gN2!=NULL){
            float xx;
            while((xx=gN2->elm->getX())<= x+ ok_elm_rad[0] ){
                xx=xx-x;
                xx=(xx<0)?(xx*-1):xx;
                float yy=gN2->elm->getY()-y;
                yy=(yy<0)?(yy*-1):yy;
                //cout<<"\t"<<gN2->elm->getName()<<" xx = "<<xx<<" , yy = "<<yy<<"\n";
                if((xx<=ok_elm_rad[0]) && (yy<=ok_elm_rad[1])){
                    //*gN=gN2;
                    bool b = this->makeActive(true, gN2);
                    *gN=active_gN;
                    return b;
                }
                gN2=gN2->next_gN;
                if(gN2==NULL)
                    break;
            }
        }cout<<"??????????????????\n";
        if(active_gN != NULL){
            this->makeActive(false);
        }
        return false;
    }
    void display_selected(sf::RenderWindow& w,int x, int y){
        if(active_gN != NULL){
            if(active_gN2!=NULL){
                active_gN2->elm->disp_details(w, x, y,0);
                active_gN->elm->disp_details(w, x, y,1);
            }
            else
                active_gN->elm->disp_details(w, x, y,0);
        }
    }
    void shortest_path(bool b){
        if(b && active_gN2!=NULL && active_gN!=NULL)
            graph.shrtst_path(active_gN2,active_gN);
        else if(b==false){
            graph.end_shPath();
        }
    }
    g_node* addElm(Element* e,float lx, float ly){
        g_node* gN;
        /*e->setLocation(lx/gnd_area[0],ly/gnd_area[1]);
        cout<<"Map.addElm() : loc="<<lx/gnd_area[0]<<" , "<<ly/gnd_area[1]<<"\n";
        gN=graph.addNode(e);*/

        float X=lx/gnd_area[0];
        int i = X*NNUM;
        if(i>=0 && i<NNUM){
            e->setLocation(lx/gnd_area[0],ly/gnd_area[1]);
            if(DEBUG_MAP)cout<<"Map.addElm() : loc="<<lx/gnd_area[0]<<" , "<<ly/gnd_area[1]<<"\n";
            gN=graph.addNode(e,indices[i]);
            if(indices[i]==NULL){
                indices[i]=gN;
            }
            else if(indices[i]->elm->getX()>=X){
                indices[i]=gN;
            }
            
            rukh.insert(gN);
        }
        else
            gN = nullptr;
        //rukh.insert(gN);
        return gN;
    }
    bool map_search(string s, tag_List **tL){
        return rukh.search_name(s,tL);
    }
    void shapeArc(g_node* from, g_node* to, float x, float y){
        a_node* aN;
        g_node* gN;//cout<<"tattta";
        sf::Vector2u wnSz=w.getSize();
        if(graph.isArc(from, to, &aN, &gN)){//cout<<"in\n";
            g_node* gN2=new struct g_node;
            gN2->elm=new Element(true);//cout<<"Map.shapeArc():element is dummy "<<gN2->elm->isDummy()<<"\n";
            gN2->elm->setLocation(x/gnd_area[0],y/gnd_area[1]);
            //gN2->next_gN=aN->suNd;
            gN2->aN=new struct a_node;
            gN2->aN->wt=0;
            gN2->wt=-1;
            if(gN!=NULL){
                gN2->next_gN = gN2->aN->suNd = gN->next_gN;
                gN->next_gN=gN->aN->suNd=gN2;
            }
            else{
                gN2->next_gN = gN2->aN->suNd = aN->suNd;
                aN->suNd=gN2;
            }
            gN2->aN->nextArc=NULL;
        }
    }
    void reset_shapeArc(g_node* from, g_node* to){
        a_node* aN;
        g_node* gN;
        if(graph.isArc(from, to, &aN, &gN)){
            if(gN!=NULL){
                g_node* gN2=aN->suNd;
                aN->suNd=gN->next_gN;
                while(gN2->elm->isDummy()){
                    g_node* gN3=gN2;
                    gN2=gN2->next_gN;
                    delete gN3;
                }
            }
        }
    }
    bool addArc(g_node* Gfrom, g_node* Gto, float wt){
        return graph.addArc(Gfrom, Gto, wt);
    }
    bool removeArc(g_node* Gfrom, g_node* Gto, int num=0){
        return graph.removeArc(Gfrom, Gto, num=0);
    }
    bool removeNode(g_node* g){
        return graph.removeNode(g);
    }
    void render(){
        graph.draw(w);
    }
    void change_nd_loc(g_node* gN,float x, float y){
        int i = gN->elm->getX() * NNUM;
        int j = x*NNUM;
        if(indices[j]!=NULL){
            if(indices[j]->elm->getX()>x){//when i==j this will never execute
                indices[j]=gN;
            }
        }
        else
            indices[j]=gN;
        if(indices[i]==gN){
                //gN=gN->next_gN;
                if(gN->next_gN!=NULL && (
                                int(gN->next_gN->elm->getX()*NNUM) == i
                                ) )
                {
                    if(i==j){
                        if(x > gN->next_gN->elm->getX())
                            indices[i]=gN->next_gN;
                    }
                    else
                        indices[i]=gN->next_gN;
                }
        }
        gN->elm->setLocation(x,y);
        graph.nodes_rearr(gN);
        //graph.print_all_nodes();
        //g_node* gN=nodesB;
      /*//print all g_nodes
        g_node* gNPrint = graph.get_nodesB_786();
        cout<<"\nmap.change_nd_loc : ";
        while(gNPrint!=NULL){
            float x=gNPrint->elm->getX();
            cout<<"\n\t"<<gNPrint->elm->getName()<<" "<<x<<" <<"<<int(x*NNUM)<<" "<<(indices[int(x*NNUM)]==gNPrint);
            gNPrint=gNPrint->next_gN;
        }*/
    }
    void gNdsRarr(g_node* gN){
        graph.nodes_rearr(gN);
    }
    //void remove(){;}
    sf::RenderWindow& getMap(){return w;}

private:
    void display_add(){

    }
};

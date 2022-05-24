#define max_nodes 25

#include<iostream>
#include <SFML/Graphics.hpp>
#include "map.cpp"
#ifndef element12xzx
#include "element.cpp"
#endif // element12xzx
#include "search.cpp"
#include "button.cpp"
#include "scrollList.cpp"

int main(){
    sf::RenderWindow main_win;
    Map mp(200,200);
    int node_size = 0;
    Element *haru = new Element[max_nodes];
    g_node **g_haru = new g_node*[max_nodes];
    

    haru[0].setName("Iroj store");
    haru[1].setName("dc Electronics");
    haru[2].setName("bhandu Academy");
    haru[3].setName("kushal get Wells hospital");
    haru[4].setName("Janak Institute of Research");
    haru[5].setName("Gopal's Gym");
    haru[6].setName("Govind's dhaba");

    haru[0].setTag("General Shop");
    haru[1].setTag("Electronics shop");
    haru[2].setTag("School");
    haru[3].setTag("Hospital");
    haru[4].setTag("Academic Institution");
    haru[5].setTag("Fitness center");
    haru[6].setTag("Govind's dhaba");

    

    g_haru[0]=mp.addElm(&haru[0],20,20);
    g_haru[1]=mp.addElm(&haru[1],90,80);
    g_haru[2]=mp.addElm(&haru[2],80,150);
    g_haru[3]=mp.addElm(&haru[3],120,20);
    g_haru[4]=mp.addElm(&haru[4],130,90);
    g_haru[5]=mp.addElm(&haru[5],180,150);
    g_haru[6]=mp.addElm(&haru[6],16,180);

    node_size = 7;

    for(int i=0;i<7;i++){
        if (!g_haru){
            cout<<"\n is null";
        }
    }    

    mp.addArc(g_haru[0],g_haru[2],6);
    mp.shapeArc(g_haru[0],g_haru[2],10,70);
    mp.shapeArc(g_haru[0],g_haru[2],20,120);
    //mp.addArc(g_haru[2],g_haru[0],6);

    mp.addArc(g_haru[2],g_haru[1],3);
    //mp.addArc(g_haru[1],g_haru[2],3);

    mp.addArc(g_haru[2],g_haru[4],6);
    mp.shapeArc(g_haru[2],g_haru[4],120,120);

    mp.addArc(g_haru[1],g_haru[5],20);
    mp.shapeArc(g_haru[1],g_haru[5],100,70);
    mp.shapeArc(g_haru[1],g_haru[5],140,70);

    mp.addArc(g_haru[5],g_haru[3],10);
    mp.shapeArc(g_haru[5],g_haru[3],190,130);
    mp.shapeArc(g_haru[5],g_haru[3],170,40);

    mp.addArc(g_haru[0],g_haru[4],10);
    mp.addArc(g_haru[4],g_haru[0],10);

    mp.addArc(g_haru[3],g_haru[4],8);
    mp.addArc(g_haru[4],g_haru[3],8);
    
    sf::RenderWindow& map_win=mp.getMap();
    cout<<"\nMap win is open :"<<map_win.isOpen();

    sf::Event event;

    main_win.display();
    main_win.create(sf::VideoMode(880,700),"Main Menu",sf::Style::Default);
    main_win.setPosition(sf::Vector2i(70,70));//sf::Vector2i(70,70));
    map_win.create(sf::VideoMode(700,700),"Ma hun map",sf::Style::Default);
    map_win.setPosition(sf::Vector2i(952,70));
    mp.render();
    //main_win.setView(map_win.getView());
    main_win.display();
    map_win.display();

    Search srch;
    int srch_x=120;
    int srch_y=100;
    srch.draw(main_win,srch_x,srch_y);

    Button button_go("Go");
    button_go.setPosition(srch_x,srch_y-70);
    Button button_stop("Stop");
    button_stop.setPosition(srch_x+170,srch_y-70);
    //Button button_add("Add");
    //button_add.setPosition(20,20);

    ScrollList scrlst;
    bool results_flag=false;

    g_node *disp_gnde;
    bool display=false;
    bool move_node = false;
    float move_node_ref_x,move_node_ref_y;
    float delx_ndMv,dely_ndMv;
    while(main_win.isOpen()){
        while(main_win.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                main_win.close();
                map_win.close();
            }
            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    int Mx=event.mouseButton.x;
                    int My=event.mouseButton.y;
                    if(results_flag){
                        if(scrlst.onClick(Mx,My,&disp_gnde)){
                            cout<<"scroll list clicked : "<<disp_gnde->elm->getName()<<"\n";
                            results_flag=false;
                            display=true;
                            mp.makeActive(true,disp_gnde);
                        }
                        else{
                            results_flag=false;
                        }
                    }
                    if (srch.is_in(Mx,My)){
                        //results_flag=false;
                        if(!srch.isActive()){
                            srch.makeActive(true);
                            srch.type_rst();
                        }
                    }
                    else{
                        srch.makeActive(false);
                    }
                    if (button_go.is_in(Mx,My)){
                        cout<<"Go\n";
                        button_go.makeclicked(true);
                        mp.shortest_path(true);
                    }
                    else if (button_stop.is_in(Mx,My)){
                        cout<<"Stop\n";
                        button_stop.makeclicked(true);
                        mp.shortest_path(false);
                    }
                }
            }
            else if(event.type==sf::Event::TextEntered){
                if(srch.isActive()){//cout<<"type type";
                    std::string s;//cout<<event.text.unicode<<"\n";
                    if(srch.type(event.text.unicode,&s)){
                        struct tag_List* tL;
                        if(mp.map_search(s,&tL)){
                            cout<<"bhettiyo";
                            scrlst.setList(tL,s);
                            results_flag=true;                    }
                        else{
                            tL=NULL;
                            if(s!=""){
                                scrlst.setList(tL,s);
                                results_flag=true;
                            }
                            else
                                results_flag=false;
                        }
                    }
                }
            }
            else if(event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                case sf::Keyboard::Left :
                    if(srch.isActive()){
                        srch.Arrow(false);
                    }
                    break;
                case sf::Keyboard::Right :
                    if(srch.isActive()){
                        srch.Arrow(true);
                    }
                    break;
                case sf::Keyboard::Delete :
                    srch.type(127);
                    break;
                default:
                    break;
                };
            }
        }
        while(map_win.pollEvent(event)){
            if(event.type==sf::Event::MouseButtonPressed){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    float Mx=event.mouseButton.x;
                    float My=event.mouseButton.y;
                    g_node* gN;
                    bool ga_code = mp.getAround_gN(&gN,
                                       Mx/float(map_win.getSize().x),
                                       My/float(map_win.getSize().y)
                                    );
                    if(ga_code){
                        cout<<"main : Clicked "<<gN->elm->getName()<<"\n";
                        disp_gnde=gN;
                        display=true;
                    }
                    else{
                        display=false;
                        /*
                        if(move_node){
                            sf::Vector2u wnSz=map_win.getSize();
                            //cout<<"\n main 210 "<<event.mouseButton.x / wnSz.x;//map_win.getPosition().x;//<<" "<<event.mouseButton.y + map_win.getPosition().y;
                            //disp_gnde->elm->setLocation((event.mouseButton.x)/float(wnSz.x) , (event.mouseButton.y)/float(wnSz.y));
                            //mp.gNdsRarr(disp_gnde);
                            //mp.change_nd_loc(disp_gnde,event.mouseButton.x/float(wnSz.x),event.mouseButton.y/float(wnSz.y));
                        }
                        */
                    }
                    move_node = false;
                    //move_node = (ga_code==2)?true:false;if(ga_code == 2)cout<<"\nmain() : *"<<ga_code<<"* move_node = true\n"; else cout<<"\nmain() : *"<<ga_code<<"*move_node = not true\n";
                }
            }
            else if(event.type == sf::Event::MouseMoved){
                if(move_node){
                    sf::Vector2u wnSz=map_win.getSize();
                    //disp_gnde->elm->setLocation(event.mouseMove.x/wnSz.x , event.mouseMove.y/wnSz.y);
                    delx_ndMv = event.mouseMove.x + move_node_ref_x;
                    dely_ndMv = event.mouseMove.y + move_node_ref_y;
                    if(delx_ndMv<0) delx_ndMv*=-1;
                    if (dely_ndMv < 0) dely_ndMv *= -1; disp_gnde = nullptr;
                    mp.change_nd_loc(disp_gnde,delx_ndMv/float(wnSz.x),dely_ndMv/float(wnSz.y));
                }
            }
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::M){
                    if(move_node){
                        move_node=false;
                    }
                    else if(display){
                        move_node = true;
                        disp_gnde = nullptr;
                        move_node_ref_x = disp_gnde->elm->getX()*map_win.getSize().x - sf::Mouse::getPosition().x + map_win.getPosition().x + 11;
                        move_node_ref_y = disp_gnde->elm->getY()*map_win.getSize().y - sf::Mouse::getPosition().y + map_win.getPosition().y + 40;
                        cout<<"\n"<<move_node_ref_x<<" , "<<move_node_ref_y;
                    }
                }
            }
            /*else if(event.type == sf::Event::MouseButtonReleased){
                move_node = false ;cout<<"\nmain() : "<<"move_node = false\n";
                if(0){;}
            }*/
        }
        main_win.clear();
        button_go.draw(main_win);
        button_stop.draw(main_win);
        srch.draw(main_win,srch_x,srch_y);
        if(display){
            mp.display_selected(main_win,srch_x-90, srch_y+70);
        }
        if(results_flag)
            scrlst.draw(main_win,srch_x,srch_y+srch.getHeight());
        main_win.display();
        map_win.clear();
        mp.render();
        map_win.display();
        ////map_win.clear();
        ////map_win.display();
    }
return 0;
}


#define element12xzx
#define THE_RAD 15
#define DEBUG_ELEMENT false

#include <iostream>
#include<SFML\graphics.hpp>
/*#ifndef LinkedList12xzx
    #include "LinkedList.cpp"
#endif*/
//#include<string>

using namespace std;

class Element{
    std::string name;
    std::string description;
    std::string tag;
    float location[2];
    int Sz;
    int id;
    static int id_gnrtr;
    sf::CircleShape circle;
    bool dummy;
    bool clicked;
    sf::Font font;
    int widthzxz;
    int heightzxz;
    //static LinkedList<Element *> elements;

public:
    Element(bool k=false){
        widthzxz=400;
        heightzxz=70;
        //id=id_gnrtr++;
        //elements.end_ins(this);
        dummy=k;
        clicked=false;
        Sz=THE_RAD;
        location[0]=0;
        location[1]=0;
        circle.setPointCount(25);
        circle.setFillColor(sf::Color::Green);
        font.loadFromFile("fonts/arial.ttf");
        //circle.setOrigin();
    }
    Element(string nm, string des=NULL, string tg=NULL, bool k=false){
        Element();
        setName(nm);
        description=des;
        tag=tg;
    }
    void setColor(int r, int g, int b){
        circle.setFillColor(sf::Color(r,g,b,250));
    }
    void draw(sf::RenderWindow& win){
        if(!dummy){
            sf::Vector2u wnSz=win.getSize();
            int rad=(((wnSz.x<wnSz.y)?wnSz.x:wnSz.y)/float(800))*Sz;
            circle.setRadius(rad);
            circle.setOrigin(rad,rad);
            circle.setPosition(location[0]*wnSz.x,location[1]*wnSz.y);//(location[0]/loc_scale[0],location[1]/loc_scale[1]);
            if(DEBUG_ELEMENT)cout<<"Element.draw() : $^location"<<location[0]*wnSz.x<<"/"<<wnSz.x<<" , "<<location[1]*wnSz.y<<"/"<<wnSz.y<<"\n";
            win.draw(circle);
        }
    }
    void disp_details(sf::RenderWindow& w,float x,float y,int num=0){
        sf::Text text;
        string str;
        float spr_rat=.07;
        if(num>0){
            sf::RectangleShape sprtr(sf::Vector2f(widthzxz*spr_rat,7*heightzxz));
            sprtr.setFillColor(sf::Color(100,100,100,200));
            sprtr.setPosition(x+num*widthzxz+(num-1)*widthzxz*spr_rat,y);
            w.draw(sprtr);
        }
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        sf::RectangleShape tagR(sf::Vector2f(widthzxz,heightzxz));
        tagR.setFillColor(sf::Color(255,100,100,200));
        tagR.setPosition(x+num*widthzxz*(1+spr_rat),y);
        text.setPosition(x+num*widthzxz*(1+spr_rat)+7,y+7);
        str="Tag : ";
        str.append(tag);
        text.setString(str);
        w.draw(tagR);
        w.draw(text);
        sf::RectangleShape title(sf::Vector2f(widthzxz,heightzxz));
        title.setFillColor(sf::Color(100,255,100,200));
        title.setPosition(x+num*widthzxz*(1+spr_rat),y+heightzxz);
        text.setPosition(x+num*widthzxz*(1+spr_rat)+7,y+heightzxz+7);
        str="Name : ";
        str.append(name);
        text.setString(str);
        w.draw(title);
        w.draw(text);
        sf::RectangleShape descriptionR(sf::Vector2f(widthzxz,heightzxz*5));
        descriptionR.setFillColor(sf::Color(100,100,255,200));
        descriptionR.setPosition(x+num*widthzxz*(1+spr_rat),y+heightzxz*2);
        text.setPosition(x+num*widthzxz*(1+spr_rat)+7,y+heightzxz+7);
        str=description;
        text.setString(str);
        w.draw(descriptionR);
    }
    void setDescription(string s){
        description=s;
    }
    int getID(){return id;}
    string getDescription(){
        return description;
    }
    void setName(string s){
        name=s;
    }
    string getName(){
        return name;
    }
    void setTag(string s){
        tag=s;
    }
    string getTag(){
        return tag;
    }
    bool isDummy(){return dummy;}
    void setLocation(float x,float y){
        location[0]=x;
        location[1]=y;
        //cout<<"element.setLocation(): "<<this->getName()<<" : "<<x<<" , "<<y<<"\n";
    }
    void getLocation(float* vec){
        vec[0]=location[0];
        vec[1]=location[1];
    }
    float getX(){
        return location[0];
    }
    void setX(float f){
        location[0]=f;
    }
    float getY(){
        return location[1];
    }
    void setY(float f){
        location[0]=f;
    }
    void setClicked(bool b){
        clicked=b;
        std::cout<<"Element.setClicked() : "<<getName();
        if(b){
            std::cout<<" is Blue\n";
            circle.setFillColor(sf::Color::Blue);
        }
        else{
            std::cout<<" is Green\n";
            circle.setFillColor(sf::Color::Green);
        }
    }
private:
    //set
};
//int Element::id_gnrtr=0;

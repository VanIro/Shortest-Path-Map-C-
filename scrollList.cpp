#include <iostream>
#include <SFML/graphics.hpp>
#ifndef khojiRukh12xzx
    #include "khojiRukh.cpp"
#endif

#define NUMCARDS 4
#define BORDER 10
#define SEPN 7

class ScrollList{
    tag_List *tLptr;
    sf::RectangleShape box;
    sf::RectangleShape meta_card;
    sf::RectangleShape card;
    int list_sZ;
    int bgn;
    sf::Text text;
    sf::Font font;
    string srch_key;

public:
    ScrollList(){
        bgn=0;
        srch_key="";
        font.loadFromFile("fonts/arial.ttf");
        text.setFont(font);
    }
    ScrollList(tag_List *tp, string s){
        ScrollList();
        setList(tp,s);
    }
    void setList(tag_List *tp, string s){
        tLptr=tp;
        list_sZ=getSz();
        srch_key=s;
    }
    int getSz(){
        int i=0;
        struct tag_List *tP=tLptr;
        while(tP!=NULL){
            i++;
            tP=tP->next_tL;
        }
        return i;
    }
    bool onClick(int mx,int my,g_node **gN){
        float ycheck = SEPN + card.getSize().y;
        int y = box.getPosition().y + meta_card.getSize().y + BORDER;
        my-=y;//cout<<"diff= "<<my<<" / "<<ycheck<<"\n";
        if(my>0){
            int a = (mx - box.getPosition().x - BORDER);
            if(a>=0 && a <= card.getSize().x){
                float b = my/float(ycheck);//cout<<"b= "<<b<<"\n";
                if((b-int(b))>=SEPN/float(ycheck)){
                    return getByIndex(int(b),gN);
                }
            }
        }
        return false;
    }
    bool getByIndex(int i, g_node **gN){
        if(i<0 || i>=list_sZ)
            return false;
        tag_List *tp=tLptr;
        while(tp!=NULL){
            if(i-- == 0)
                break;
            tp=tp->next_tL;
        }
        if(tp!=NULL){
            *gN=tp->gN;
            return true;
        }
        return false;
    }
    void draw(sf::RenderWindow& win, float x, float y){
        meta_card.setSize(sf::Vector2f(500,40));
        meta_card.setFillColor(sf::Color::Blue);
        card.setSize(sf::Vector2f(500,50));
        card.setFillColor(sf::Color::Red);
        int numcrds=(list_sZ<NUMCARDS)?list_sZ:NUMCARDS;
        box.setSize(sf::Vector2f(500+2*BORDER, meta_card.getSize().y + (card.getSize().y + SEPN)*numcrds+2*BORDER));
        box.setFillColor(sf::Color::Green);
        box.setPosition(x,y);
        win.draw(box);
        struct tag_List *tp=tLptr;
        int i=0;
        y+=BORDER;
        x+=BORDER;
        meta_card.setPosition(sf::Vector2f(x,y));
        win.draw(meta_card);
        text.setFillColor(sf::Color::Green);
        text.setPosition(x+7, y+7);
        std::string txt;
        txt=" result(s) found for \"";
        //char tmpchar='0'+list_sZ;
        string tmpstr="7";
        tmpstr[0]='0'+list_sZ;
        txt.insert(0,tmpstr);
        txt.append(srch_key);
        txt.append("\"");
        text.setString(txt);
        text.setCharacterSize(20);
        win.draw(text);
        y+=meta_card.getSize().y;
        text.setFillColor(sf::Color::Blue);
        text.setCharacterSize(30);
        while(tp!=NULL){
            if(i<bgn){i++;}
            else{
                y+=SEPN;
                card.setPosition(sf::Vector2f(x,y));
                win.draw(card);
                text.setPosition(x+7,y+7);
                txt="Name : ";
                txt.append(tp->gN->elm->getName());
                txt.append("   |   Tag : ");
                txt.append(tp->gN->elm->getName());
                text.setString(txt);
                win.draw(text);
            }
            tp=tp->next_tL;
        }
    }
};

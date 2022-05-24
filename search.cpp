#include <iostream>
#include <SFML/graphics.hpp>

class Search{
    bool active,curs;
    int knt;
    std::string input;
    int box_height;
    int box_width;
    int box_x,box_y;
    sf::RectangleShape box;
    sf::RectangleShape box2;
    sf::RectangleShape cursor;
    int cursPos,curs_off;
    sf::Text text,text2,tmptext;
    sf::Font font;
    sf::Clock clock;
public:
    Search(){
        active=false;
        curs=false;
        cursPos=curs_off=0;
        knt=1000;
        input="";
        font.loadFromFile("fonts/arial.ttf");
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color(250,250,0,200));
        text2.setFont(font);
        text2.setCharacterSize(30);
        text2.setFillColor(sf::Color::Black);
        tmptext.setFont(font);
        tmptext.setCharacterSize(30);
    }
    int getWidth(){return box_width;}
    int getHeight(){return box_height;}
    void draw(sf::RenderWindow& win,float x, float y, int height=50, int width=500, int border=5){
        box_height=height;
        box_width=width;
        text2.setString("Search");
        sf::FloatRect text2_rect = text2.getGlobalBounds();
        box2.setSize(
                        sf::Vector2f(box_width +text2_rect.width + 4*border,
                        box_height+2*border)
                     );
        box2.setPosition(x,y);
        text2.setPosition(x+5,y+5+border);
        box2.setFillColor(sf::Color::Green);
        box.setSize(sf::Vector2f(box_width,box_height));
        if(active){
            box.setFillColor(sf::Color(200,50,50,255));
        }
        else{
            box.setFillColor(sf::Color(150,150,150,200));
        }
        box_x=x+border*3+text2_rect.width;
        box_y=y+border;
        box.setPosition(box_x,box_y);
        text.setString(input);
        sf::Vector2f box_pos=box.getPosition();
        text.setPosition(box_pos.x+5,box_pos.y+5);
        //std::cout<<"left"<<txt_rect.left<<", top"<<txt_rect.top<<", width"<<txt_rect.width<<
        //    ", height"<<txt_rect.height<<" ani "<<text.getCharacterSize()<<"\n";
        //sf::RectangleShape cursor(sf::Vector2f(txt_rect.width,txt_rect.height));
        win.draw(box2);
        win.draw(box);
        if(active && curs){
            sf::FloatRect txt_rect=text.getGlobalBounds();
            cursor.setSize(sf::Vector2f(3,box_height-4));
            //cursor.setPosition(txt_rect.left,txt_rect.top);
            cursor.setPosition(txt_rect.left+txt_rect.width+3+curs_off,box_pos.y+2);
            cursor.setFillColor(sf::Color(0,255,0,255));
            win.draw(cursor);
            /*knt--;
            if(knt==0){
                curs=false;
            }*/
            if(clock.getElapsedTime().asSeconds()>=0.3){
                curs=false;
                clock.restart();
            }
        }
        else if(active && !curs){
            /*
            knt++;
            if(knt==700)
                curs=true;
            */
            if(clock.getElapsedTime().asSeconds()>=0.3){
                curs=true;
                clock.restart();
            }
        }
        win.draw(text2);
        win.draw(text);
    }
    bool is_in(int x, int y){
        //std::cout<<"Seaarch.is_in():"<<box_x<<" , "<<box_y<<" , "<<box_width<<" , "<<box_height<<" , "<<x<<" , "<<y<<"\n";
        if(y>=box_y && y<=(box_y+box_height))
            if(x>=box_x && x<=(box_x+box_width)){
                //std::cout<<"Search.is_in():"<<"ret true?\n";
                return true;
            }
        return false;
    }
    bool isActive(){return active;}
    bool type(char c,std::string* s=NULL){
        std::cout<<"Search.type(): "<<int(c)<<"\n";
        //std::cout<<"Search.type(): nl = "<<'\n'<<"\n";

        int sz=input.size();
        if(c=='\b'){
            if(sz-cursPos >0){
                input.erase(sz-1-cursPos,1);
            }
        }
        else if(c==127){
            if(cursPos >0){
                input.erase(sz-cursPos,1);
                Arrow(true);
            }
        }
        else{
            if(c==13){
                //std::cout<<"newline\n";
                if(s!=NULL){
                    *s=input;
                }
                return true;
            }
            else{
                //std::cout<<"Search.type(): appending "<<c<<"\n";
                if(cursPos==0){
                    input.append(&c);
                }
                else{
                    input.insert(input.size()-cursPos,&c);
                }
            }
        }
        return false;
    }
    void Arrow(bool right){
        int sZ=input.size();
        if(!right && (sZ-cursPos > 0)){
            curs_off=get_curs_off(++cursPos);
        }
        else if(cursPos > 0){
            curs_off=get_curs_off(--cursPos);
        }
    }
    void type_rst(){
        input="";
        cursPos=0;
        curs_off=0;
    }
    void makeActive(bool b){
        std::cout<<"Search.makeActive(): "<<b<<"\n";
        active=b;
        curs=true;
        clock.restart();
    }
private:
    int get_curs_off(int pos){
        if(pos==0)
            return 0;
        tmptext.setString(input.substr(input.size()-pos,pos));
        return (tmptext.getGlobalBounds().width * (-1) - 4);
    }
};

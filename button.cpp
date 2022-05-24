#include <iostream>
#include <SFML/graphics.hpp>

class Button{
    bool clicked;
    std::string input;
    int box_height;
    int box_width;
    float box_x,box_y;
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    sf::Clock clock;
public:
    Button(std::string s){
        clicked=false;
        font.loadFromFile("fonts/arial.ttf");
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color(250,250,0,200));
        setString(s);
        setSize();
    }
    int getWidth(){return box_width;}
    int getHeight(){return box_height;}
    void setString(std::string s){
        input=s;
        text.setString(input);
    }
    void draw(sf::RenderWindow& win){
        text.setString("Search");
        box.setSize(sf::Vector2f(box_width,box_height));
        if(clicked){
            box.setFillColor(sf::Color(200,200,50,255));
            if(clock.getElapsedTime().asSeconds()>=0.2)
                this->makeclicked(false);
        }
        else{
            box.setFillColor(sf::Color(150,150,150,200));
        }
        box.setPosition(box_x,box_y);
        text.setString(input);
        sf::Vector2f box_pos=box.getPosition();
        text.setPosition(box_pos.x+5,box_pos.y+5);
        win.draw(box);
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
    void setSize(int height=50, int width=100){
        box_height=height;
        box_width=width;
    }
    void setPosition(float x,float y){
        box_x=x;
        box_y=y;
        box.setPosition(sf::Vector2f(box_x,box_y));
    }
    bool isclicked(){return clicked;}
    void makeclicked(bool b){
        clicked=b;
        clock.restart();
    }
};


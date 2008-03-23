#ifndef MODEL_HPP
#define MODEL_HPP

#include "Tilemap.hpp"
#include "unit.hpp"
#include "ASprite.hpp"
#include "Plane.hpp"
#include "Factory.hpp"
#include "Blast.hpp"
#include "Hud.hpp"

class Model
{
    sf::View CurrentView;

    Tilemap mSea;
    Hud myHud;
    PlaneE * player;
    Blast * myBlast;
    ListUnit planeList;
    ListUnit bulletList;
    ListUnit blastList;
    sf::Image * TileSet;
    Factory * myFactory;

    sf::Sprite * cursor;
    bool leftButton;
public :
    Model(sf::Image & Img,sf::Image & LandTile,sf::Image & BlastImg,sf::Image & TileHud,Factory & myFactory);
    ~Model();
    void ReadControl(sf::Event & Event);          //apply user input on the model
    void Update(const sf::RenderWindow& Window);  //update object state and physics
    void UpdateView();                            //move view if needed
    sf::View * GetModelView() {return  & CurrentView;}
    void Draw(sf::RenderWindow& Window);
};



#endif // MODEL_HPP


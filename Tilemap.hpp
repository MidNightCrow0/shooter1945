#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "constant.hpp"
#include <SFML/Graphics.hpp>

/********************************************************************/
/* This class contain :                                              /
/*  - a whole map word (MAP_HEIGHT x MAP_WIDTH index of tiles)       /
/*  - a set of 256 Tiles                                             /
/*  - a set of 21 * 27 Sprite to render a single screen              /
/********************************************************************/
class Tilemap : public sf::Drawable
{
protected :
    unsigned char map[MAP_HEIGHT][MAP_WIDTH];
    sf::Sprite Tiles[256];
    sf::Sprite Screen[16][21];
public :
    Tilemap(sf::Image & TileSet);
    unsigned char GetTileNumber(int l,int c) const;
    void ComputeRender(const sf::View & CurrentView);
protected :
    virtual void Render(const sf::RenderWindow& Window) const;
};


#endif // TILEMAP_HPP

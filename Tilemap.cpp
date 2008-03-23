#include "Tilemap.hpp"
#include <cmath>

Tilemap::Tilemap(sf::Image & TileSet)
{
    //All sprite use the same SpriteSheet
    for(int i=0;i < 16; i++)
    for(int j=0;j < 21 ; j++)
    {
        Screen[i][j].SetImage(TileSet);
    }

    //Set up set of Tiles
    Tiles[0].SetSubRect(sf::IntRect(4, 70, 4+32, 70+32));  // black tile
    Tiles[1].SetSubRect(sf::IntRect(4, 37, 4+32, 37+32));  // n°1 sea tile
    Tiles[2].SetSubRect(sf::IntRect(37, 37, 37+32, 37+32));  // n°2 sea tile
    Tiles[3].SetSubRect(sf::IntRect(70, 4, 70+32, 4+32));  // n°3 sea tile ( diff)
    Tiles[4].SetSubRect(sf::IntRect(4, 4, 4+32, 4+32));  // grass tile
    Tiles[5].SetSubRect(sf::IntRect(37, 4, 37+32, 4+32));  // sand tile

    //Generating random tilemap
    sf::Randomizer::SetSeed(0);
    for(int i=0;i < MAP_HEIGHT; i++)
    for(int j=0;j < MAP_WIDTH ; j++)
    {
        map[i][j] = sf::Randomizer::Random(1, 2);
    }

}
unsigned char Tilemap::GetTileNumber(int l,int c) const
{
    if(l>=0 && l < MAP_HEIGHT && c>=0 && c < MAP_WIDTH)
        return map[l][c];
    else
         return 0;
}

//SetPosition of the sprites
void Tilemap::ComputeRender(const sf::View & CurrentView)
{
    int ViewTop = (int) CurrentView.Rect.Top;
    int ViewLeft = (int) CurrentView.Rect.Left;
    int mapx  = ViewLeft / 32;
    int mapy  =  ViewTop / 32;
    for(int l=0;l < 16; l++)
    for(int c=0;c < 21 ; c++)
    {
        int TileNumber = GetTileNumber(mapy+l,mapx+c);
        Screen[l][c].SetSubRect(Tiles[TileNumber].GetSubRect());
        Screen[l][c].SetPosition( (mapx+c) * 32 ,(mapy+l) * 32);
    }
}

void Tilemap::Render(const sf::RenderWindow& Window) const
{
    for(int l=0;l < 16; l++)
    for(int c=0;c < 21; c++)
    {
        Window.Draw( Screen[l][c]);
    }
}



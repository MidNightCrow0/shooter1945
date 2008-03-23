#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "ASprite.hpp"
#include "Unit.hpp"

class Hud : public sf::Drawable
{
    ASprite mCursor[3];
    ASprite mScale[3];
    ASprite mText[3];
public :
    Hud(sf::Image & TileHud);
    void Update(Unit & player);
protected :
    virtual void Render(const sf::RenderWindow& Window) const;
};


#endif // HUD_HPP

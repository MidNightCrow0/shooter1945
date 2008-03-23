#ifndef SCROLL_HPP
#define SCROLL_HPP

#include "constant.hpp"
#include <SFML/Graphics.hpp>

class Scroll : public sf::Drawable
{
public :
    Scroll();
protected :
    virtual void Render(const sf::RenderWindow& Window) const;
};

#endif // SCROLL_HPP

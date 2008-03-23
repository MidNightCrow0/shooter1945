#ifndef ASPRITE_HPP
#define ASPRITE_HPP
#include "constant.hpp"
#include <SFML/Graphics.hpp>

class ASprite : public  virtual sf::Sprite
{
    int mCurrentFrame;
    int mticks;
    int mDelay[MAX_NBR_FRAME];
    sf::IntRect mFrame[MAX_NBR_FRAME];
public :
    ASprite();
    int SetFrame(int index,int delay,sf::IntRect Frame);
    int SetNbrFrame(int Nbr);
    void Update_anm();
};

#endif // ASPRITE_HPP

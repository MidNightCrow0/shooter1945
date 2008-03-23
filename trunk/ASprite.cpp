#include "ASprite.hpp"


ASprite::ASprite() : Sprite()
{
    mticks = 0;
    mCurrentFrame = 0;

}

int ASprite::SetFrame(int index,int delay,sf::IntRect Frame)
{
    if(index >= MAX_NBR_FRAME) return 0;
    else
    {
        mDelay[index] = delay;
        mFrame[index] = Frame;
        return 1;
    }
}

int ASprite::SetNbrFrame(int Nbr)
{
    if(Nbr > MAX_NBR_FRAME) return 0;
    else if(Nbr == MAX_NBR_FRAME) return 1;
    else
    {
        mDelay[Nbr] = -1;
        return 1;
    }
}

//This fonction must be call every L_PERIOD
void ASprite::Update_anm(void)
{
    mticks++;
    if(mDelay[mCurrentFrame] == 0 || mticks < mDelay[mCurrentFrame]) {}  // do nothing;
    else
    {
        if(mCurrentFrame == MAX_NBR_FRAME-1) mCurrentFrame = 0;
        else if(mDelay[mCurrentFrame+1] == -1) mCurrentFrame = 0;
        else mCurrentFrame++;

        mticks = 0;
        SetSubRect(mFrame[mCurrentFrame]);
    }
}

#include <cmath>
#include "Gun.hpp"
#include "constant.hpp"
#include "Bullet.hpp"

Gun::Gun()
{
    //Default value
    mTicks = 0;
    ClipLeft =70;ClipTop = 202;
    mWidth = 32;mHeight = 32;
    mNbrOfBullet = 1;
    mAngle = 0;
    mTop = 0;mLeft = 17;
    mShootDelay = 10;
}


int  Gun::Shoot(sf::Image &Img,Unit & myUnit,ListUnit & bulletList)
{
    if(mTicks > mShootDelay)
    {
        mTicks = 0;
        for(int i=0;i < mNbrOfBullet;i++)
        {
            Bullet * ptrBullet = new Bullet;
            ptrBullet->SetImage(Img);
            ptrBullet->SetSubRect(sf::IntRect(ClipLeft, ClipTop, ClipLeft+mWidth, ClipTop+mHeight));
            ptrBullet->SetSpeed(BULLET_SPEED);
            float radius  = myUnit.GetWidth()/2.0;
            float posLeft = myUnit.GetLeft() + radius * (cos( (myUnit.GetRotation() * DEG_RAD) + M_PI_2) + 1);
            float posTop  = myUnit.GetTop() - (radius * (sin( (myUnit.GetRotation() * DEG_RAD) + M_PI_2) - 1));
            posLeft = posLeft - mLeft * cos(myUnit.GetRotation() * DEG_RAD) - mTop * sin(myUnit.GetRotation() * DEG_RAD);
            posTop  = posTop  - mTop * cos(myUnit.GetRotation() * DEG_RAD) + mLeft * sin(myUnit.GetRotation() * DEG_RAD);
            ptrBullet->SetPosition( posLeft , posTop );
            ptrBullet->SetRotation(myUnit.GetRotation() + mAngle);
            ptrBullet->SetCollRect(lowerCoeffPx);
            bulletList.AddUnit(ptrBullet);
        }
        return 1;
    }
    else
        return 0;
}


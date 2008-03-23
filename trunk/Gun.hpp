#ifndef GUN_HPP
#define GUN_HPP

#include "Bullet.hpp"
#include "Unit.hpp"


class Gun
{
    unsigned int mTicks;    //Timer for shoot rate
    int ClipTop,ClipLeft;   //Clip coordinate of the bullet
    int mWidth,mHeight;     //Clip dimension of the bullet
    int mNbrOfBullet;       //Number of bullet per shoot
    float mAngle;           //Relative angle of the gun
    float mTop, mLeft;      //Relative position of the gun
    int mShootDelay;        //Delay between two consecutive shoot
    int lowerCoeffPx;       //Lowering coefficient for collision detection
public :
    Gun();
    int  Shoot(sf::Image &Img,Unit & myUnit,ListUnit & bulletList);
    void Update() {mTicks++;}
    //Standart Mutators
    void SetClip(int Left,int Top,int Width,int Height) {ClipLeft = Left; ClipTop = Top;mWidth=Width;mHeight=Height;}
    void SetNbrOfBullet(int Nbr) {mNbrOfBullet=Nbr;}
    void SetRAngle(float Angl) {mAngle = Angl;}
    void SetRPosition(int Left,int Top) {mLeft=Left; mTop=Top;}
    void SetShootDelay(int Delay) {mShootDelay = Delay;}
    void SetCollRect(int CoeffPx) {lowerCoeffPx = CoeffPx;}
};

#endif // GUN_HPP

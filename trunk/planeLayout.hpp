#ifndef PLANELAYOUT_HPP
#define PLANELAYOUT_HPP

#include "Gun.hpp"
#include "Plane.hpp"
#include <tinyxml.h>

class planeLayout
{
    std::string name,imgFileName;
    int mKey;
    int mRectTop,mRectLeft;
    int mWidth,mHeight;
    int mRotX,mRotY;
    int mCollRect;
    float mSpeedMax,mSpeedMin;
    float mTrnSpdMx;
    int mNbrOfFrame,mNbrOfGun;
    Gun  Armament[5];
    int ptrAnim[3][10];     // left,top,delay
public :
    planeLayout() {mNbrOfFrame=0;};
    int LoadFromXml(const char* Filename);
    int GetKey() {return mKey;};
    void SetToPlane(PlaneE * Pln);
    void Print();

};
#endif // PLANELAYOUT_HPP

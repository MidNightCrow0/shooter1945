#include <cmath>
#include <iostream>
#include "unit.hpp"
#include "Plane.hpp"
#include "constant.hpp"



Unit::Unit() : Sprite()
{
    mSpeed = 0;
    mState = 1;
    mNext = NULL;
    mMaxturnspd = 0;
    mMaxSpeed = 50.0;
    mMinSpeed = 0;
    mRectCoeff = 0;
}


void Unit::Update_pos()
{
    float OffY = -  mSpeed * cos( GetRotation() * DEG_RAD) ;
    float OffX = -  mSpeed * sin( GetRotation() * DEG_RAD) ;
    Move(OffX,OffY);
    if(myCollRect.Left == 0 && myCollRect.Top == 0 && myCollRect.Right == 0 && myCollRect.Bottom == 0)
    {
        //it's the first update : compute rect according to mRectCoeff
        myCollRect.Left   = GetLeft() + mRectCoeff;
        myCollRect.Top    = GetTop()  + mRectCoeff;
        myCollRect.Right  = GetLeft() + GetWidth() - mRectCoeff;
        myCollRect.Bottom = GetTop()  + GetHeight() - mRectCoeff;
    }
    else
        myCollRect.Offset(OffX,OffY);   //just move the rect
}

bool Unit::Intersect(const Unit & obj,sf::FloatRect * ptrRect)
{
    return myCollRect.Intersects(obj.GetCollRect(),ptrRect);
}

float Unit::ComCenterX() const
{
    return GetLeft() + GetWidth()/2;
}

float Unit::ComCenterY() const
{
    return GetTop() + GetHeight()/2;
}

void Unit::SetSpeed(float Spd,bool check)
{
    if(check)
    {
        if(Spd > mMaxSpeed)
            Spd = mMaxSpeed;
        else if(Spd < mMinSpeed)
            Spd = mMinSpeed;
        mSpeed = Spd;
    }
    else
    {
        mSpeed = Spd;
    }
}

void Unit::Steer(float angle)
{
    if(angle > mMaxturnspd)
        angle = mMaxturnspd;
    else if(angle < mMaxturnspd * -1.0)
        angle = mMaxturnspd * -1.0;

    angle += GetRotation();
    SetRotation(angle);
}

/*
void Unit::SetCollRect(float lowerPx)
{
    myCollRect.Left   = GetLeft() + lowerPx;
    myCollRect.Top    = GetTop()  + lowerPx;
    myCollRect.Right  = GetLeft() + GetWidth() - lowerPx;
    myCollRect.Bottom = GetTop()  + GetHeight() - lowerPx;
    //std::cout << "Set CollRect : Width/Height : " << GetWidth() << "/" << GetHeight() << std::endl;
}*/

float Unit::ComRotationMod() const
{
    return fmod(GetRotation(), 360.f);
}

//Compute angle (in degree) between a unit+sprite and the horizon
float Unit::ComAngleto(Sprite & target) const
{
    float angle=0;
    float UniX = ComCenterX(); float UniY = ComCenterY();
    float TarX = target.GetLeft() + target.GetWidth()/2;
    float TarY = target.GetTop()  + target.GetHeight()/2;
    float deltaX = TarX - UniX;
    float deltaY = UniY - TarY;
    angle = RAD_DEG * atan(deltaY/deltaX);
    if(fabs(deltaX) < 1e-8)  //avoid per 0 division
    {
        if(TarY < UniY)
            angle = 90;
        else
            angle = 270;
    }
    else
    {
        angle = RAD_DEG * atan(deltaY/deltaX);
        //first quarter is 0->90
        if(TarX < UniX && TarY < UniY)         //second quarter is 90->180
            angle += 180;
        else if(TarX < UniX && TarY > UniY)    //third quarter is 180->270
            angle += 180;
        else if(angle < 0)                     //fourth quarter is 270->360
            angle +=360;

    }
    return angle;
}

float Unit::ComAngleto(float TarX, float TarY) const
{
    Sprite target;
    target.SetLeft(TarX);target.SetTop(TarY);
    return ComAngleto(target);
}

float Unit::ComDistto(Unit & target) const
{
    float tarX = target.ComCenterX(), tarY = target.ComCenterY();
    float myX  = ComCenterX(),myY  = ComCenterY();
    return sqrt((tarX - myX) * (tarX - myX) + (tarY - myY) * (tarY - myY));
}

float Unit::ComDistto(float TarX, float TarY) const
{
    float myX  = ComCenterX(),myY  = ComCenterY();
    return sqrt((TarX - myX) * (TarX - myX) + (TarY - myY) * (TarY - myY));
}

//Set rotation angle to go to the target
void Unit::SetRotationTo(Sprite & target)
{
    float alpha = ComRotationMod() +90;
    if (alpha < 0) alpha += 360;  // alpha is 0->360
    float beta  = ComAngleto( target );
    float delta = beta - alpha;   // delta must tend to 0

    if (delta > 180 ) delta = delta - 360;
    else if(delta < -180 ) delta = 360 + delta;

    Steer(delta);
}

void Unit::SetRotationTo(float TarX, float TarY)
{
    Sprite target;
    target.SetLeft(TarX);target.SetTop(TarY);
    SetRotationTo(target);
}

//*********************************************************************//
// List of Unit   :                                                    //
//*********************************************************************//

ListUnit::~ListUnit()
{
    Unit * ptrNode = ptrFirstUnit;
    while(ptrNode != NULL)
    {
        ptrFirstUnit =  ptrNode->GetNext();
        delete ptrNode;
        ptrNode = ptrFirstUnit;
    }
}

void ListUnit::Update_all()
{
    Unit * ptrNode = ptrFirstUnit;
    //Browse all elements
    while(ptrNode != NULL)
    {
        ptrNode->Update_all();
        ptrNode =  ptrNode->GetNext();
    }
}

void ListUnit::Intersect(Unit & target)
{
    sf::FloatRect * ptrRect = new sf::FloatRect(0,0,0,0);
    Unit * ptrNode = ptrFirstUnit;
    //Browse all elements
    while(ptrNode != NULL)
    {
        if( ptrNode->Intersect(target,ptrRect) )
        {
            //std::cout << "Detected colision : " << ptrRect->Left << "," << ptrRect->Top << "," << ptrRect->Right << "," << ptrRect->Bottom << std::endl;
            //std::cout << "Between : " << target.GetCollRect().Left << "," << target.GetCollRect().Top << "," << target.GetCollRect().Right << "," << target.GetCollRect().Bottom << std::endl;
            //std::cout << "and : " << ptrNode->GetCollRect().Left << "," << ptrNode->GetCollRect().Top << "," << ptrNode->GetCollRect().Right << "," << ptrNode->GetCollRect().Bottom << std::endl;
            ptrNode->SetState(0);
            target.SetState(0);
        }
        ptrNode =  ptrNode->GetNext();
    }
}

void ListUnit::Intersect(ListUnit & ListTarget)
{
    Unit * ptrNode = ptrFirstUnit;
    //Browse all elements
    while(ptrNode != NULL)
    {
        ListTarget.Intersect( *ptrNode );
        ptrNode =  ptrNode->GetNext();
    }
}

//Remove units which state are equal to 0
void ListUnit::CleanList(Unit * refBlast,ListUnit * BlastList)
{
    Unit * ptrNodeA = ptrFirstUnit;
    Unit * ptrNodeB = NULL;
    while(ptrNodeA != NULL)
    {
        if( !ptrNodeA->GetState() )
        {
            nbrOfUnit--;
            PlaneE * ptrPlaneE = dynamic_cast <PlaneE *> (ptrNodeA);
            if (ptrPlaneE != NULL)
                {
                    ptrPlaneE->Explode(refBlast,BlastList);
                }
            if(ptrNodeB == NULL)
                ptrFirstUnit = ptrNodeA->GetNext();
            else
                ptrNodeB->SetNext(ptrNodeA->GetNext());
            delete ptrNodeA;
            if(ptrNodeB == NULL)
                ptrNodeA = ptrFirstUnit;
            else
                ptrNodeA = ptrNodeB->GetNext();
        }
        else
        {
            ptrNodeB = ptrNodeA;
            ptrNodeA = ptrNodeA->GetNext();
        }
    }
}

void ListUnit::AddUnit(Unit * ptrU)
{
    nbrOfUnit++;
    Unit * ptrNode = ptrFirstUnit;
    if(ptrNode == NULL) ptrFirstUnit = ptrU;
    else
    {
        //Find last element
        while(ptrNode->GetNext() != NULL)
        {
            ptrNode =  ptrNode->GetNext();
        }
        ptrNode->SetNext(ptrU);
    }
}


void ListUnit::Render(const sf::RenderWindow& Window) const
{
   Unit * ptrNode = ptrFirstUnit;
    //Browse all elements
    while(ptrNode != NULL)
    {
        Window.Draw( *ptrNode );
        ptrNode =  ptrNode->GetNext();
    }
}

void ListUnit::Pilot(Unit * target)
{
    Unit * ptrNode = ptrFirstUnit;
    //Browse all elements
    while(ptrNode != NULL)
    {
        PlaneE * ptrPlaneE = dynamic_cast <PlaneE *> (ptrNode);
        if (ptrPlaneE != NULL)
            ptrPlaneE->Pilot(target,ptrFirstUnit);
        ptrNode =  ptrNode->GetNext();
    }
}






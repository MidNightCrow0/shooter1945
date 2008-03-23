#include "Plane.hpp"

Plane::Plane() : Unit() , ASprite()
{
    for(int i=0;i < 5;i++)
    {
        mSelGun[i] = false;
    }
}

void Plane::Shoot(sf::Image &Img,ListUnit & bulletList)
{
    for(int i=0;i < 5;i++)
    {
        if(mSelGun[i])
            Armament[i].Shoot(Img,*this,bulletList);
    }
}

void Plane::Explode(Unit * refBlast,ListUnit * blastList)
{
    if(blastList!=NULL)
    {
        Blast * ptrBlast = new Blast;
        Blast * ptrRefBlast = dynamic_cast <Blast *> (refBlast);
        * ptrBlast = * ptrRefBlast;
        float Tleft = GetLeft() + (GetWidth() - ptrBlast->GetWidth()) / 2.0;
        float Ttop  = GetTop() +  (GetHeight() - ptrBlast->GetHeight()) / 2.0;
        ptrBlast->SetPosition(Tleft,Ttop);
        blastList->AddUnit(ptrBlast);
    }
}

void Plane::SetActArmament(unsigned int mode)
{
    for(int i=0;i < 5;i++)  mSelGun[i] = false;
    if(mode < 5)
        mSelGun[mode] = true;
    else if(mode == 5)
        {
            mSelGun[1] =true;
            mSelGun[2] =true;
        }
}

bool Plane::SetArmament(int index,Gun & Arm)
{
    if(index < 0 || index > 4) return false;
    Armament[index] = Arm;          //copy constructor here ?
    return true;
}

Gun * Plane::GetArmament(unsigned int index)
{
    if(index < 5)
        return &Armament[index];
    else
        return NULL;
}

void Plane::Update_all()
{
    for(int i=0;i < 5;i++)
    {
        if(mSelGun[i])
            Armament[i].Update();
    }
    Update_anm();
    Update_pos();
}

//******************************************************************//
//  PlaneE implementation                                                 //
//******************************************************************//

PlaneE::PlaneE() : Plane()
{
    mScrptTarInd = 0;
    //Set a random destination
    for(int i=0;i<3;i++)
    {
        Scrpt[0][i] = sf::Randomizer::Random(0, MAP_WIDTH * 32);
        Scrpt[1][i] = sf::Randomizer::Random(0, MAP_HEIGHT * 32);
    }
    //Defaut values
    mDstEngage = 200;
    mDstAvoid  = 35;
    mSpeedAvd = 0;mSpeedEng = 0;mSpeedCru = 0;
}

void PlaneE::SetSpdBehave(float spdAvd,float spdEng,float spdCru)
{
    mSpeedAvd = spdAvd;
    mSpeedEng = spdEng;
    mSpeedCru = spdCru;
}

int PlaneE::SetScrpt(unsigned int l,unsigned int c,float val)
{
    if(l > 1 || c >3) return 0;
    else
    {
        Scrpt[l][c] = val;
        return 1;
    }
}

int PlaneE::Avoid(Unit * ptrGrpPlane)
{
    while(ptrGrpPlane != NULL)
    {
        if (ComDistto(*ptrGrpPlane) < mDstAvoid && this != ptrGrpPlane)
        {
            //A unit is too close to me (and it's not me) : try to avoid collision
            float alpha = ComRotationMod() +90;
            if (alpha < 0) alpha += 360;            // alpha is 0->360
            float beta  = ComAngleto(*ptrGrpPlane);

            float delta = beta - alpha;             //delta is -360->360

            if (delta > 180 ) delta = delta - 360;
            else if(delta < -180 ) delta += 360;    //delta is -180->180

            if(delta < 90 && delta > -90)           //the unit is in front of us
            {
                Steer(-delta);
                SetSpeed(mSpeedAvd);
                return 1;
            }
        }
        ptrGrpPlane = ptrGrpPlane->GetNext();
    }
    return 0;
}

void PlaneE::Pilot(Unit * target, Unit * ptrGrpPlane)
{
    float Distance = ComDistto(*target);
    if(Distance > mDstEngage)
    {
        //Player is too far : follow script destination
        if( ComDistto(Scrpt[0][mScrptTarInd],Scrpt[1][mScrptTarInd]) < 30)
        {
            //Scripted objective reached : next objective
            mScrptTarInd++;
            if(mScrptTarInd > 3) mScrptTarInd=0;
        }
        SetRotationTo(Scrpt[0][mScrptTarInd],Scrpt[1][mScrptTarInd]);
        SetSpeed(mSpeedCru);
    }
    else
    {
        //avoid if necessary
        if(!Avoid(target) && !Avoid(ptrGrpPlane))
        {
            //Engage player
            SetSpeed(mSpeedEng);
            SetRotationTo(*target);
        }
    }
}


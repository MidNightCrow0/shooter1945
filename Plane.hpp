#ifndef PLANE_HPP
#define PLANE_HPP

#include "unit.hpp"
#include "ASprite.hpp"
#include "Gun.hpp"
#include "Blast.hpp"


//Minimal plane : inherit from ASprite & Unit
class Plane : public Unit, public ASprite
{
    bool mSelGun[5];
    Gun  Armament[5];
public :
    Plane();
    void Shoot(sf::Image &Img,ListUnit & bulletList);
    Gun * GetArmament(unsigned int index);
    bool SetArmament(int index,Gun & Arm);
    void SetActArmament(unsigned int mode);
    void Update_all();
    void Explode(Unit * refBlast,ListUnit * blastList);
};


//******************************************************************//
// Enemy plane : inherit from  Plane                                //
//******************************************************************//

class PlaneE : public Plane
{
    int   mScrptTarInd;
    float mDstAvoid,mDstEngage;
    float mSpeedAvd,mSpeedEng,mSpeedCru;
    float Scrpt[2][4];
public :
    PlaneE();
    void Pilot(Unit * target, Unit * ptrGrpPlane);
    int Avoid(Unit * ptrGrpPlane);
    void SetSpdBehave(float spdAvd,float spdEng,float spdCru);
    void SetDstBehave(float Avoid,float Engage) {mDstAvoid = Avoid; mDstEngage = Engage;}
    int SetScrpt(unsigned int l,unsigned int c,float val);
};


#endif // PLANE_HPP

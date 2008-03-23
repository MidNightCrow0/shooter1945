#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>

class Unit;

class Unit : public virtual sf::Sprite
{
    Unit * mNext;
    float mSpeed;
    int mState;
    float mRectCoeff;
    sf::FloatRect myCollRect;
protected :
    float mMaxturnspd;
    float mMaxSpeed,mMinSpeed;
public :
    Unit();
    void Update_pos();
    bool Intersect(const Unit & obj,sf::FloatRect * ptrRect);

    void SetSpeed(float spd,bool check = true);
    void Steer(float angle);
    void SetMaxTurnSpeed(float spd) {mMaxturnspd=spd;}
    void SetMaxMinSpeed(float max,float min) {mMaxSpeed=max;mMinSpeed=min;}
    void SetState(int sta)   {mState=sta;}
    void SetNext(Unit * ptrNext) {mNext=ptrNext;}
    void SetCollRect(float lowerPx) {mRectCoeff=lowerPx;}

    int  GetState(void)   {return mState;}
    float GetSpeed(void)  {return mSpeed;}
    Unit *  GetNext(void) {return mNext;}
    const sf::FloatRect & GetCollRect() const {return myCollRect;}

    float ComCenterX() const;
    float ComCenterY() const;
    float ComRotationMod() const;
    float ComAngleto(Sprite & target) const;
    float ComAngleto(float TarX, float TarY) const;
    float ComDistto(Unit & target) const;
    float ComDistto(float TarX, float TarY) const;

    void SetRotationTo(Sprite & target);
    void SetRotationTo(float TarX, float TarY);

    virtual void Update_all() = 0;
};

//*********************************************************************//
// List of Unit   :                                                    //
//*********************************************************************//

class  ListUnit  : public sf::Drawable
{
    int nbrOfUnit;
    Unit * ptrFirstUnit;
public :
    ListUnit() {ptrFirstUnit=NULL;nbrOfUnit=0;}
    ~ListUnit();
    void Update_all();
    void CleanList(Unit * refBlast = NULL,ListUnit * BlastList = NULL);                 //remove object from list
    void AddUnit(Unit * ptrU);        //add a Plane to list
    void Pilot(Unit * target);
    void Intersect(Unit & target);
    void Intersect(ListUnit & ListTarget);
protected :
    virtual void Render(const sf::RenderWindow& Window) const;
};


#endif // UNIT_HPP

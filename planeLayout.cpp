#include <iostream>
#include "planeLayout.hpp"

using namespace std;

int planeLayout::LoadFromXml(const char* Filename)
{
    TiXmlDocument doc(Filename);
    if( !doc.LoadFile()) return 0;

    TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0),hAnim(0);

    pElem=hDoc.FirstChildElement().Element();
    if (!pElem) return 0;
    // save this for later
    hRoot=TiXmlHandle(pElem);

    pElem=hRoot.Element();
    name=pElem->Attribute("name");

	pElem=hRoot.FirstChild("Key").Element();
	if (!pElem) return 0;
    pElem->QueryIntAttribute("id",&mKey);

    pElem=hRoot.FirstChild("Img").Element();
	if (!pElem) return 0;
    imgFileName=pElem->Attribute("src");

    pElem=hRoot.FirstChild("MainRect").Element();
	if (!pElem) return 0;
    pElem->QueryIntAttribute("x",&mRectLeft);
    pElem->QueryIntAttribute("y",&mRectTop);

    pElem=hRoot.FirstChild("Dimension").Element();
	if (!pElem) return 0;
    pElem->QueryIntAttribute("w",&mWidth);
    pElem->QueryIntAttribute("h",&mHeight);

    pElem=hRoot.FirstChild("RotationCenter").Element();
	if (!pElem) return 0;
    pElem->QueryIntAttribute("x",&mRotX);
    pElem->QueryIntAttribute("y",&mRotY);

    pElem=hRoot.FirstChild("CollRect").Element();
	if (!pElem) return 0;
    pElem->QueryIntAttribute("coeff",&mCollRect);

    pElem=hRoot.FirstChild("Speed").Element();
	if (!pElem) return 0;
    pElem->QueryFloatAttribute("Max",&mSpeedMax);
    pElem->QueryFloatAttribute("Min",&mSpeedMin);

    pElem=hRoot.FirstChild("TurnSpeed").Element();
	if (!pElem) return 0;
    pElem->QueryFloatAttribute("Max",&mTrnSpdMx);

    pElem=hRoot.FirstChild("Animation").Element();
	if (!pElem) return 0;
    pElem->QueryIntAttribute("NbrOfFrame",&mNbrOfFrame);

    if(mNbrOfFrame < 0 || mNbrOfFrame >= 10)
        return 0;

    TiXmlElement* pAnimNode=hRoot.FirstChild( "Animation" ).FirstChild("Frame").Element();
    for(int i=0; i < mNbrOfFrame;i++)
    {
        int top,left,delay;
        hAnim=TiXmlHandle(pAnimNode);
        pElem=hAnim.FirstChild("Rect").Element();
        if (!pElem) return 0;
        pElem->QueryIntAttribute("x",&left);
        pElem->QueryIntAttribute("y",&top);

        pElem=hAnim.FirstChild("Delay").Element();
        if (!pElem) return 0;
        pElem->QueryIntAttribute("l",&delay);

        ptrAnim[0][i]=left;
        ptrAnim[1][i]=top;
        ptrAnim[2][i]=delay;

        pAnimNode=pAnimNode->NextSiblingElement();
    }

    pElem=hRoot.FirstChild("Armament").Element();
	if (!pElem) return 0;
    pElem->QueryIntAttribute("NBrOfGun",&mNbrOfGun);

    if(mNbrOfGun < 0 || mNbrOfGun > 5)
        return 0;

    TiXmlElement* pArmNode=hRoot.FirstChild( "Armament" ).FirstChild("Gun").Element();
    for(int i=0; i < mNbrOfGun;i++)
    {
        int Tleft,Ttop,Twidth,Theight,Tdelay,TRPosLeft,TRPosTop;
        hAnim=TiXmlHandle(pArmNode);
        pElem=hAnim.FirstChild("ClipRect").Element();
        if (!pElem) return 0;
        pElem->QueryIntAttribute("left",&Tleft);
        pElem->QueryIntAttribute("top",&Ttop);
        pElem->QueryIntAttribute("width",&Twidth);
        pElem->QueryIntAttribute("height",&Theight);
        Armament[i].SetClip(Tleft,Ttop,Twidth,Theight);

        pElem=hAnim.FirstChild("RelPos").Element();
        if (!pElem) return 0;
        pElem->QueryIntAttribute("left",&TRPosLeft);
        pElem->QueryIntAttribute("top",&TRPosTop);
        Armament[i].SetRPosition(TRPosLeft,TRPosTop);

        pElem=hAnim.FirstChild("Delay").Element();
        if (!pElem) return 0;
        pElem->QueryIntAttribute("l",&Tdelay);
        Armament[i].SetShootDelay(Tdelay);

        Armament[i].SetNbrOfBullet(1);  //default values, not yet implemented in xml files
        Armament[i].SetRAngle(0);
        Armament[i].SetCollRect(14);

        pArmNode=pArmNode->NextSiblingElement();
    }
	return 1;
}

void planeLayout::Print()
{
    cout << "Name :" << name << endl;
    cout << "Key value  : " << mKey << endl;
    cout << "Image source :" << imgFileName << endl;
    cout << "Rect value : " << mRectTop << "," << mRectLeft << "," << mRectTop+mHeight << "," << mRectLeft+mWidth << endl;
    cout << "Rotation Center : " << mRotX << "," << mRotY << endl;
    cout << "Collision Rect Coefficient : " << mCollRect << endl;
    cout << "Speed Range : " << mSpeedMin << " to " << mSpeedMax << endl;
    cout << "Turn Speed : " << mTrnSpdMx << endl;
    cout << "Animation (" << mNbrOfFrame << ") :" <<endl;
    for(int i=0; i < mNbrOfFrame;i++)
    {
        cout << ptrAnim[0][i] << "," << ptrAnim[1][i] << "," << ptrAnim[2][i] << endl;
    }
     cout << "Nbr of Gun : " << mNbrOfGun  <<endl;
}

void planeLayout::SetToPlane(PlaneE * Pln)
{
    Pln->SetSubRect(sf::IntRect(mRectLeft,mRectTop, mRectLeft+mWidth, mRectTop+mHeight));
    Pln->SetRotationCenter(mRotX,mRotY);
    Pln->SetCollRect(mCollRect);
    Pln->SetMaxTurnSpeed(mTrnSpdMx);
    Pln->SetMaxMinSpeed(mSpeedMax,mSpeedMin);
    Pln->SetNbrFrame(mNbrOfFrame);
    for(int i=0;i < mNbrOfFrame ; i++ )
    {
        int Tleft = ptrAnim[0][i];
        int Ttop = ptrAnim[1][i];
        int Tdelay = ptrAnim[2][i];
        Pln->SetFrame(i,Tdelay,sf::IntRect(Tleft, Ttop, Tleft+mWidth, Ttop+mHeight));
    }
    for(int i=0;i < mNbrOfGun ; i++)
    {
        Pln->SetArmament(i,Armament[i]);
    }
}

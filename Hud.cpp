#include "Hud.hpp"

Hud::Hud(sf::Image & TileHud)
{
    for(int i=0;i<3;i++)
    {
        mCursor[i].SetImage(TileHud);
        mCursor[i].SetSubRect(sf::IntRect(175, 61, 175+10, 61+6));
        mCursor[i].SetFrame(0,0,sf::IntRect(175, 61, 175+10, 61+6));
        mCursor[i].SetFrame(1,4,sf::IntRect(175, 43, 175+10, 43+6));
        mCursor[i].SetNbrFrame(2);
        mCursor[i].SetPosition(190,443 + i*14);

        mScale[i].SetImage(TileHud);
        mScale[i].SetSubRect(sf::IntRect(89, 54, 89+102, 54+8));
        mScale[i].SetFrame(0,0,sf::IntRect(89, 54, 89+102, 54+8));
        mScale[i].SetFrame(1,4,sf::IntRect(89, 36, 89+102, 36+8));
        mScale[i].SetNbrFrame(2);
        mScale[i].SetPosition(100,435 + i*14);

        mText[i].SetImage(TileHud);
        mText[0].SetSubRect(sf::IntRect(28, 14, 28+56, 14+15));
        mText[0].SetFrame(0,0,sf::IntRect(28, 14, 28+56, 14+15));
        mText[0].SetNbrFrame(1);
        mText[0].SetPosition(34,435);
        mText[1].SetSubRect(sf::IntRect(4, 34, 4+80, 34+15));
        mText[1].SetFrame(0,0,sf::IntRect(4, 34, 4+80, 34+15));
        mText[1].SetFrame(1,4,sf::IntRect(90, 14, 90+80, 14+15));
        mText[1].SetNbrFrame(2);
        mText[1].SetPosition(10,435 + 14);
        mText[2].SetSubRect(sf::IntRect(42, 52, 42+42, 52+12));
        mText[2].SetFrame(0,0,sf::IntRect(42, 52, 42+42, 52+12));
        mText[2].SetFrame(1,4,sf::IntRect(182, 14, 182+42, 14+12));
        mText[2].SetNbrFrame(2);
        mText[2].SetPosition(48,435 + 2*14);
    }
}

void Hud::Update(Unit & player)
{
    mCursor[0].SetLeft(88 + player.GetSpeed() * 12);

}

void Hud::Render(const sf::RenderWindow& Window) const
{
    for(int i=0;i < 3; i++)
    {
        Window.Draw( mCursor[i] );
        Window.Draw( mScale[i]  );
        Window.Draw( mText[i]   );
    }
}

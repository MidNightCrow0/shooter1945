#include <iostream>
#include <sstream>
#include <cmath>
#include "model.hpp"
#include "constant.hpp"


Model::Model(sf::Image &Img,sf::Image & LandTile,sf::Image & BlastImg,sf::Image & TileHud,Factory & Factory) :
CurrentView(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT), 1.f) , mSea(LandTile),myHud(TileHud)
{
    leftButton = false;
    myFactory = &Factory;
    TileSet = &Img;

    player = myFactory->Create(1,*TileSet);
    player->SetPosition(320,240);
    player->SetRotation(0);
    player->SetSpeed(3.0);
    player->SetActArmament(5);

    cursor = new sf::Sprite;
    cursor->SetImage(*TileSet);
    cursor->SetPosition(100,100);
    cursor->SetSubRect(sf::IntRect(268, 202, 268+32, 202+32));

    myBlast = new Blast;
    myBlast->SetImage(BlastImg);
    myBlast->SetSubRect(sf::IntRect(0, 0, 64, 64));
    for(int lig=0;lig<5;lig++)
    for(int col=0;col<8;col++)
    {
        myBlast->SetFrame(lig*8+col,1,sf::IntRect(col*64,lig*64,64*(col+1),64*(lig+1)));
    }

    PlaneE * Enm = myFactory->Create(2,*TileSet);
    Enm->SetDstBehave(100,600);
    Enm->SetSpdBehave(1.5,2.0,3.0);
    Enm->SetPosition(100,100);
    Enm->SetRotation(180);
    Enm->SetSpeed(3.0);
    planeList.AddUnit( Enm);

    Enm = myFactory->Create(2,*TileSet);
    Enm->SetDstBehave(100,600);
    Enm->SetSpdBehave(1.5,2.0,3.0);
    Enm->SetPosition(200,100);
    Enm->SetRotation(180);
    Enm->SetSpeed(3.0);
    planeList.AddUnit( Enm);

    Enm = myFactory->Create(3,*TileSet);
    Enm->SetDstBehave(100,600);
    Enm->SetSpdBehave(1.5,2.0,3.0);
    Enm->SetPosition(300,100);
    Enm->SetRotation(180);
    Enm->SetSpeed(3.0);
    planeList.AddUnit( Enm);
}

Model::~Model()
{
    delete cursor;
    delete player;
    delete myBlast;
}

void Model::ReadControl(sf::Event & Event)
{
    if(Event.Type == sf::Event::MouseMoved)
    {
        cursor->SetPosition(Event.MouseMove.X + CurrentView.Rect.Left,Event.MouseMove.Y + CurrentView.Rect.Top);
    }
    else if(Event.Type == sf::Event::MouseWheelMoved)
    {
        float upSpd = player->GetSpeed() + Event.MouseWheel.Delta / 2.5f;
        player->SetSpeed(upSpd);
    }
    else if(Event.Type == sf::Event::MouseButtonPressed && Event.MouseButton.Button == sf::Mouse::Left)
    {
        leftButton = true;
    }
    else if(Event.Type == sf::Event::MouseButtonReleased && Event.MouseButton.Button == sf::Mouse::Left)
    {
        leftButton = false;
    }
}


void Model::Update(const sf::RenderWindow& Window)
{
    if(leftButton)
       player->Shoot(*TileSet,bulletList);

    planeList.Intersect( *player);
    bulletList.Intersect(planeList);

    player->SetRotationTo(*cursor);
    player->Update_all();

    planeList.CleanList(myBlast,&blastList);
    planeList.Update_all();
    planeList.Pilot(player);

    bulletList.CleanList();
    bulletList.Update_all();

    blastList.CleanList();
    blastList.Update_all();

    myHud.Update( *player );
    UpdateView();
    mSea.ComputeRender(CurrentView);
}

void Model::UpdateView(void)
{
    //Define the central Rect (non scrolling area)
    sf::FloatRect CenterRect(CurrentView.Rect.Left + SCROLL_W ,CurrentView.Rect.Top + SCROLL_H ,CurrentView.Rect.Right - SCROLL_W ,CurrentView.Rect.Bottom  - SCROLL_H );
    //Change View if needed & Update Cursor position
    if(player->GetTop() < CenterRect.Top && player->GetTop() > SCROLL_H )
    {
        float Offset = player->GetTop() - CenterRect.Top;
        CurrentView.Rect.Offset(0,Offset);
        cursor->Move(0,Offset);
    }
    else if((player->GetTop() + player->GetHeight() > CenterRect.Bottom) && (player->GetTop() + player->GetHeight() < MAP_HEIGHT * 32 - SCROLL_H) )
    {
        float Offset = player->GetTop() + player->GetHeight() - CenterRect.Bottom;
        CurrentView.Rect.Offset(0,Offset);
        cursor->Move(0,Offset);
    }
    if(player->GetLeft() < CenterRect.Left && player->GetLeft() > SCROLL_W)
    {
        float Offset = player->GetLeft() - CenterRect.Left;
        CurrentView.Rect.Offset(Offset,0);
        cursor->Move(Offset,0);
    }
    else if((player->GetLeft() + player->GetWidth()> CenterRect.Right) && (player->GetLeft() + player->GetWidth()< MAP_WIDTH * 32 - SCROLL_W))
    {
        float Offset = player->GetLeft() + player->GetWidth() - CenterRect.Right;
        CurrentView.Rect.Offset(Offset,0);
        cursor->Move(Offset,0);
    }
}

void Model::Draw(sf::RenderWindow& Window)
{
    Window.SetView( & CurrentView);
    Window.Draw( mSea);
    Window.Draw( blastList );
    Window.Draw( *player );
    Window.Draw( planeList );
    Window.Draw( bulletList);
    Window.Draw( *cursor );

    Window.SetView(NULL);
    Window.Draw( myHud);
}


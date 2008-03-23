#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "model.hpp"
#include "constant.hpp"


int main()
{
    int countFPS=0;
    bool Running = true;
    sf::Event Event;
    sf::Clock Clock,TimeFPS;
    Factory myFactory;
    sf::Image TileSet,LandTile,BlastImg,HudImg;
    sf::String sFPS;sFPS.Move(10.f, 10.f);sFPS.SetSize(20.f);

    sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "1945 (v0.02b)",sf::Style::Fullscreen);
    App.OptimizeForNonOpenGL(true);
    App.ShowMouseCursor(false);
    //App.UseVerticalSync(true);

    if (!TileSet.LoadFromFile("data/1945mod.bmp"))
        return EXIT_FAILURE;
    TileSet.CreateMaskFromColor(sf::Color(0, 67, 171));
    if (!HudImg.LoadFromFile("data/Hud_00.bmp"))
        return EXIT_FAILURE;
    HudImg.CreateMaskFromColor(sf::Color(0, 67, 171));
    if (!BlastImg.LoadFromFile("data/Blast.bmp"))
        return EXIT_FAILURE;
    BlastImg.CreateMaskFromColor(sf::Color(0, 67, 171));
    if (!LandTile.LoadFromFile("data/landTiles.bmp"))
        return EXIT_FAILURE;
    if( !myFactory.loadLayout("data/layout/plane_layout_list.xml") )
        return EXIT_FAILURE;
    Model myModel(TileSet,LandTile,BlastImg,HudImg,myFactory);

    while (Running)
    {
        while (App.GetEvent(Event))
        {
            // Fenêtre fermée
            if (Event.Type == sf::Event::Closed)
            {
                Running = false;
            }
            // Touche 'echap' appuyée
            else if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            {
                Running = false;
            }
            else
            {
                myModel.ReadControl(Event);
            }
        }
        if( Clock.GetElapsedTime() > L_PERIOD)
        {
            myModel.Update(App);
            Clock.Reset();
        }
        if( TimeFPS.GetElapsedTime() > 1.f)
        {
            std::ostringstream oss;oss << countFPS;sFPS.SetText(oss.str());
            TimeFPS.Reset();
            countFPS = 0;
        }
        myModel.Draw(App);
        App.Draw(sFPS);
        countFPS++;
        App.Display();
    }
	return EXIT_SUCCESS;
}

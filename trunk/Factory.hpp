#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Plane.hpp"
#include "planeLayout.hpp"

class Factory
{
std::map<int,planeLayout *> m_map;
public :
    ~Factory();
    int   loadLayout(const char* Filename);
    void  Register(int key,planeLayout* obj);
    PlaneE* Create(int key,sf::Image &Img) const;
};

#endif

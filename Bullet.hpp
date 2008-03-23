#ifndef BULLET_HPP
#define BULLET_HPP
#include "unit.hpp"

class Bullet  : public Unit
{
    int mTicks;
public :
    Bullet();
    void Update_all();
};

#endif // BULLET_HPP

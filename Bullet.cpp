#include "Bullet.hpp"
#include "constant.hpp"

Bullet::Bullet() : Unit()
{
    mTicks = 0;
}

void Bullet::Update_all()
{
    Update_pos();
    mTicks++;
    if(mTicks > BULLET_LIFE_TIME)
        SetState(0);
}

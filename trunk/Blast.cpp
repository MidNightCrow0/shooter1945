#include "Blast.hpp"

Blast::Blast() : Unit(), ASprite()
{
    mTicks = 0;
}

void Blast::Update_all()
{
    Update_anm();
    mTicks++;
    if(mTicks > BLAST_LIFE_TIME)
        SetState(0);
}

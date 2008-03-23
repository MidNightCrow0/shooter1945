#ifndef BLAST_HPP
#define BLAST_HPP
#include "constant.hpp"
#include "unit.hpp"
#include "ASprite.hpp"

class Blast  : public Unit, public ASprite
{
    int mTicks;
public :
    Blast();
    void Update_all();
};

#endif // BLAST_HPP

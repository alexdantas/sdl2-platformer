#include "DamageableObject.hpp"

DamageableObject::DamageableObject(int initialHp):
    isAlive(true),
    hp(initialHp)
{ }
int DamageableObject::getHitpoints()
{
    return this->hp;
}
bool DamageableObject::isDead()
{
    return !(this->isAlive);
}
void DamageableObject::heal(int d)
{
    this->hp += d;
}
void DamageableObject::damage(int d)
{
    this->hp -= d;

    if (this->hp <= 0)
    {
        this->hp = 0;
        this->isAlive = false;
    }
}


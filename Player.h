#pragma once

#include <Ogre.h>
#include <GameObject.h>

class Player:public GameObject{
public:
    btScalar w,l,h;
    Player(Ogre::SceneManager* smp);
    void setPos(Ogre::Vector3 pos);
    btScalar getX();
    btScalar getY();
    btScalar getZ();
};

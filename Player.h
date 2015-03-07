#pragma once

#include <Ogre.h>
#include <GameObject.h>

class Player:public GameObject{
protected:

    //physics
    Ogre::Real restcoef;

public:
	Ogre::Vector3 pos;
	Ogre::Real radius;
    Player(Ogre::SceneManager* smp);
};

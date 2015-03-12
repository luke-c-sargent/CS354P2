#pragma once

#include <Ogre.h>
#include <GameObject.h>

class Ball:public GameObject{
protected:
    //geometry
    Ogre::Real radius;
    //physics
    Ogre::Real restcoef;

public:
    Ball(Ogre::SceneManager* smp);
};

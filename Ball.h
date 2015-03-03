#pragma once

#include <Ogre.h>
#include <GameObject.h>

class Ball:GameObject{
protected:
    //geometry
    Ogre::Real radius;
    //physics
    Ogre::Real restcoef;
    //wat
    float lastTime;

public:
    Ball(Ogre::SceneManager* smp);
    void update(float elapsedTime);
};

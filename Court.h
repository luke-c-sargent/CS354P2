#pragma once

#include <Ogre.h>
#include <GameObject.h>

class Court:GameObject{
protected:
    //geometry
    Ogre::Plane plane;

    //child scene nodes
    Ogre::SceneNode* wallnode;
	Ogre::SceneNode* frontnode;
	Ogre::SceneNode* backnode;
	Ogre::SceneNode* floornode;
	Ogre::SceneNode* ceilingnode;

    //dimensions - 1 unit = 1 inch
    Ogre::Real length;
    Ogre::Real width;
    Ogre::Real height;

public:
    Court(Ogre::SceneManager * smp);

    void createPlane(Ogre::String name, Ogre::Real x, Ogre::Real y, Ogre::String material, Ogre::Vector3 translation, Ogre::Vector3 rotationvector,Ogre::Real degree);

};

#pragma once

#include <Ogre.h>
#include <GameObject.h>

class Court:public GameObject{
protected:
    //geometry
    Ogre::Plane plane;

    //child scene nodes
    Ogre::SceneNode* wallnode;
	Ogre::SceneNode* frontnode;
	Ogre::SceneNode* backnode;
	Ogre::SceneNode* floornode;
	Ogre::SceneNode* ceilingnode;



public:
    Court(Ogre::SceneManager * smp);
    //dimensions - 1 unit = 1 inch
    Ogre::Real length;
    Ogre::Real width;
    Ogre::Real height;
	Ogre::Real goalline;
    void createPlane(Ogre::String name, Ogre::Real x, Ogre::Real y, Ogre::String material, Ogre::Vector3 translation, Ogre::Vector3 rotationvector,Ogre::Real degree);

};

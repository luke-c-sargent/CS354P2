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
    //wall bodies
    btRigidBody* body2,*body3,*body4,*body5,*body6;
    btMotionState *ms2,*ms3,*ms4,*ms5,*ms6;
    btCollisionShape *shape2,*shape3,*shape4,*shape5,*shape6;



public:
    Court(Ogre::SceneManager * smp);
    //dimensions - 1 unit = 1 inch
    Ogre::Real length;
    Ogre::Real width;
    Ogre::Real height;
	Ogre::Real goalline;
    void createPlane(Ogre::String name, Ogre::Real x, Ogre::Real y, Ogre::String material, Ogre::Vector3 translation, Ogre::Vector3 rotationvector,Ogre::Real degree);
    void addWalls();
    void addWall(btRigidBody*& bod, btCollisionShape*& shap, btMotionState*& ms, btVector3 normal, btVector3 pos, btQuaternion ori);
    void addToSimulator();
};

#pragma once

#include <Ogre.h>
//#include "Simulator.h"
//class OgreMotionState;

 

class GameObject {
protected:
    Ogre::String name;
    Ogre::SceneManager* sceneMgr;
    Ogre::SceneNode* rootNode;
    Ogre::Entity* geom;
//    OgreMotionState* motionState;
/*
    Simulator* simulator;
    btCollisionShape* shape;
    btRigidBody* body;
    btTransform tr;
    btVector3 inertia;

    btScalar mass;
    btScalar restitution;
    btScalar friction;
    bool kinematic;
    bool needsUpdates;

    CollisionContext* context;
    BulletContactCallback* cCallBack;
    */
};

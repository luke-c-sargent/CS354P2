#include "Ball.h"
#include <stdio.h>

//constructor
Ball::Ball(Ogre::SceneManager* smp){
    radius=6;//a diameter of a foot; this is a test value
    sceneMgr=smp;

    name = "Ball";

    position=btVector3(0,50,-60);
    inertia=btVector3(0,0,0);
    rotation=btQuaternion(0,0,0,1);

    mass=1.0f;
    restitution=0.835f;
    friction=0.5f;

    //bind ball to ogre
    rootNode=sceneMgr->getRootSceneNode()->createChildSceneNode("ballNode");
    Ogre::Entity * entity=sceneMgr->createEntity("ball","sphere.mesh");
    rootNode->attachObject(entity);

    //beautification
    entity->setCastShadows(true);
    entity->setMaterialName("Ball");
    //ogre sphere.mesh has radius 100;
    Ogre::Real scalefactor = Ogre::Real(radius/100.f);
    rootNode->scale(scalefactor,scalefactor,scalefactor);

    //bt values
    shape = new btSphereShape(radius);
    shape->calculateLocalInertia(mass,inertia);

    ms = new btDefaultMotionState(btTransform(rotation, position));

    btRigidBody::btRigidBodyConstructionInfo bodyCI(mass, ms, shape, inertia);

    //add other physics constants
    bodyCI.m_restitution=restitution;
    bodyCI.m_friction=friction;
    bodyCI.m_rollingFriction=friction;

    body = new btRigidBody(bodyCI);


}

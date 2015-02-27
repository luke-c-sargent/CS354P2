#include "Ball.h"

//constructor
Ball::Ball(Ogre::SceneManager* smp){
    restcoef=0.835;//avg of allowable extremes
    radius=6;//a diameter of a foot; this is a test value
    sceneMgr=smp;
    rootNode=sceneMgr->getRootSceneNode()->createChildSceneNode("ballNode");
    Ogre::Entity * entity=sceneMgr->createEntity("ball","sphere.mesh");
    rootNode->attachObject(entity);
    entity->setCastShadows(true);
    entity->setMaterialName("Ball");
    //ogre sphere.mesh has radius 100;
    Ogre::Real scalefactor = Ogre::Real(radius/100.f);
    rootNode->scale(scalefactor,scalefactor,scalefactor);

}

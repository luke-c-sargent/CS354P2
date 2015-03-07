#include "Ball.h"
#include "OgreMotionState.h"
#include <stdio.h>

//constructor
Ball::Ball(Ogre::SceneManager* smp){
    restcoef=10.835;//avg of allowable extremes
    radius=6;//a diameter of a foot; this is a test value
    lastTime=0.0f;
    sceneMgr=smp;

    name = "Ball";

    position = *(new btVector3(0,0,0));
    rotation = *(new btVector3(0,0,0));

    needsUpdates=true;

    rootNode=sceneMgr->getRootSceneNode()->createChildSceneNode("ballNode");
    Ogre::Entity * entity=sceneMgr->createEntity("ball","sphere.mesh");
    rootNode->attachObject(entity);
    entity->setCastShadows(true);
    entity->setMaterialName("Ball");
    //ogre sphere.mesh has radius 100;
    Ogre::Real scalefactor = Ogre::Real(radius/100.f);
    rootNode->scale(scalefactor,scalefactor,scalefactor);

    //tentative bt values
    shape = new btSphereShape(6.0f);
    btQuaternion rotation;
    rotation.setEulerZYX(rotation.z(),rotation.y(),rotation.x());

    tr= *(new btTransform(rotation,position));
    shape->calculateLocalInertia(mass,inertia);

    //inertia= *(new btVector3(0.0f,0.0f,0.0f));
    mass=1.0f;
    restitution=10.835f;
    friction=0.5f;
    motionState = new OgreMotionState(tr,rootNode);
    body = new btRigidBody(mass,motionState,shape,inertia);

}

/*
void Ball::update(float elapsedTime) {
    lastTime += elapsedTime;
    simulator->getWorld()->contactTest(body, *cCallBack);

    if (context->hit && (context->velNorm > 2.0 || context->velNorm < -2.0)
        && (lastTime > 0.5 || (context->lastBody != context->body && lastTime > 0.1))) {

        if (context->theObject->getName() == "Player") soundMgr->playClip(punchClip);
        else soundMgr->playClip(bounceClip);
        lastTime = 0.0f;
    }
    context->hit = false;
}
*/

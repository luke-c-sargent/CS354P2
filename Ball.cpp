#include "Ball.h"

//constructor
Ball::Ball(Ogre::SceneManager* smp){
    restcoef=0.835;//avg of allowable extremes
    radius=6;//a diameter of a foot; this is a test value
    lastTime=0.0f;
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

void Ball::update(float elapsedTime) {
    lastTime += elapsedTime;
    simulator->getWorld()->contactTest(body, *cCallBack);
    if (context->hit && (context->velNorm > 2.0 || context->velNorm < -2.0)
        && (lastTime > 0.5 || (context->lastBody != context->body && lastTime > 0.1))) {
        /*
        if (context->theObject->getName() == "Player") soundMgr->playClip(punchClip);
        else soundMgr->playClip(bounceClip);*/
        lastTime = 0.0f;
    }
    context->hit = false;
}

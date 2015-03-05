#include <Player.h>

Player::Player(Ogre::SceneManager* smp){
    restcoef=0.835;//avg of allowable extremes
    radius=6;//a diameter of a foot; this is a test value
    sceneMgr=smp;
    pos = Ogre::Vector3(0,-100,180);
    rootNode=sceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode"); // need unique identifier per object
    Ogre::Entity * entity=sceneMgr->createEntity("Player","ninja.mesh");
    rootNode->attachObject(entity);
    entity->setCastShadows(true);
    entity->setMaterialName("Ball");
    Ogre::Real scalefactor = Ogre::Real(radius/100.f);
    rootNode->scale(scalefactor*4,scalefactor*4,scalefactor*4);
}

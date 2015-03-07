#include <Player.h>

Player::Player(Ogre::SceneManager* smp){
    restcoef=0.835;//avg of allowable extremes
    sceneMgr=smp;
    radius=25/2;
    pos = Ogre::Vector3(0,-120,180);
    rootNode=sceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode"); // need unique identifier per object
    Ogre::Entity * entity=sceneMgr->createEntity("Player","cube.mesh");
    rootNode->attachObject(entity);
    entity->setCastShadows(true);
    entity->setMaterialName("Ball");
    rootNode->scale(.25,1,.25);
}

#include "GameObject.h"
#include <stdio.h>
#include <assert.h>

using std::cout;

GameObject::GameObject() :
    name(),
    sceneMgr(0),
    rootNode(0),
    geom(0),
    simulator(0),
    ms(0),
    shape(0),
    body(0),
    position(0.0f,0.0f,0.0f),
    rotation(0.0f,0.0f,0.0f){

}


void GameObject::addToSimulator() {
    simulator->addObject(this);
}

void GameObject::updateTransform(){
    btTransform tr;
    ms->getWorldTransform(tr);
    rootNode->setPosition(tr.getOrigin().getX(),
                          tr.getOrigin().getY(),
                          tr.getOrigin().getZ());
}

void GameObject::setSimulator(Simulator * insim){
    simulator=insim;
}

btRigidBody* GameObject::getBody(){
    return body;
}

void GameObject::printpos(){
    cout << "{"<< position.x()<<","<< position.y()<<","<< position.z()<<"}\n";
}

Ogre::SceneNode* GameObject::getNode(){
    return rootNode;
}
Ogre::String GameObject::getName(){
    return name;
}

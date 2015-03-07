#include "Simulator.h"
#include "GameObject.h"
#include "OgreMotionState.h"
#include <stdio.h>

using std::cout;

Simulator::Simulator(){
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    overlappingPairCache = new btDbvtBroadphase();
    solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, overlappingPairCache, solver, collisionConfiguration);
   dynamicsWorld->setGravity(btVector3(0,-386, 0));//386.09 inches/s^2 = 9.8m/s^2
   //keep track of the shapes, we release memory at exit.
   //make sure to re-use collision shapes among rigid bodies whenever possible!
   btAlignedObjectArray<btCollisionShape*> collisionShapes;
}

void Simulator::stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep) {
    for (int i = 0; i != objList.size(); i++) idList[i] = 0;
    dynamicsWorld->stepSimulation(elapsedTime, maxSubSteps, fixedTimestep);
    for (unsigned int i = 0; i < objList.size(); i++){
        if (objList[i]->doUpdates()){
            //checkHit(i);
            objList[i]->update(elapsedTime);
        }
    }
    //*/
    //Ogre::Vector3 pos= objList[0]->getNode()->getPosition();
    btVector3 bv=objList[0]->getBody()->getLinearVelocity();
    OgreMotionState *ms = objList[0]->getMotionState();
    btTransform newpos = ms->getPos();
    cout << bv.y()<<"\n";

/*
    if(pos.y<-114){
        cout <<"THIS\n";
        objList[0]->getNode()->translate(0,10,0);
    }
            */
    dynamicsWorld->stepSimulation(elapsedTime, fixedTimestep);
    //btTransform trans;
    //btScalar yv=objList[0]->context->velocity.getY();
//    Ogre::Vector3 pos= objList[0]->getNode()->getPosition();
    //cout <<objList[0]->getName() << "Y: " << pos.y << std::endl;
}

bool Simulator::checkHit(int o) {
    for (int i = idList[o]; i < objList.size(); i++) {
        if (i != o) {
            objList[o]->context->hit = false;
            dynamicsWorld->contactPairTest(objList[o]->getBody(), objList[i]->getBody(), *objList[o]->cCallBack);
            if (objList[o]->context->hit) {
                idList[o] = ++i;
                return true;
            }
        }
    }
    return false;
}

btDiscreteDynamicsWorld* Simulator::getWorld(){
    return dynamicsWorld;
}

void Simulator::addObject (GameObject* o) {
objList.push_back(o);
// use default collision group/mask values (dynamic/kinematic/static)
dynamicsWorld->addRigidBody(o->getBody());
}

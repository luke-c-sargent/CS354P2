#pragma once

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>

class GameObject;

class Simulator{
protected:
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btBroadphaseInterface* overlappingPairCache;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld; //inherits from CollisionWorld
    btConstraintSolver* mConstraintsolver;
    Ogre::SceneManager* sceneMgr;
    std::deque<GameObject*> objList;
    std::deque<int> idList;
public:
    Simulator();
    void stepSimulation(const Ogre::Real elapsedTime, int maxSubSteps, const Ogre::Real fixedTimestep);
    bool checkHit(int o);
    btDiscreteDynamicsWorld* getWorld();
    void addObject(GameObject* o);
};

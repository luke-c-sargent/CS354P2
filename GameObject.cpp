#include "GameObject.h"
#include "OgreMotionState.h"



void GameObject::checkCollisions(bool check) {
    needsUpdates = check;
    if (!cCallBack && needsUpdates) {
        context = new CollisionContext();
        cCallBack = new BulletContactCallback(*body,*context);
    }
}

void GameObject::addToSimulator() {
    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    motionState->updateTransform(*(new btTransform(*(new btMatrix3x3(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f)))));
    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    if (mass != 0.0f) shape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, inertia);
    rbInfo.m_restitution = restitution;
    rbInfo.m_friction = friction;
    body = new btRigidBody(rbInfo);
    body->setUserPointer(this);
    if (kinematic) {
        body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        body->setActivationState(DISABLE_DEACTIVATION);
    }
    simulator->addObject(this);
}

bool GameObject::doUpdates(){
    return needsUpdates;
}

void GameObject::update(float elapsedTime) {
    lastTime += elapsedTime;
    simulator->getWorld()->contactTest(body, *cCallBack);

    //DEBUG
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("%s\n", needsUpdates ? "true" : "false");

    if (context->hit && (context->velNorm > 2.0 || context->velNorm < -2.0)
        && (lastTime > 0.5 || (context->lastBody != context->body && lastTime > 0.1))) {
        /*
        if (context->theObject->getName() == "Player") soundMgr->playClip(punchClip);
        else soundMgr->playClip(bounceClip);*/
        lastTime = 0.0f;
    }
    context->hit = false;
}

btRigidBody* GameObject::getBody(){
    return body;

}

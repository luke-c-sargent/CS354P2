#pragma once
#include <Ogre.h>
#include <btBulletDynamicsCommon.h>

class OgreMotionState : public btMotionState {
protected:
    Ogre::SceneNode* mVisibleobj;
    btTransform mPos1;
public:
    OgreMotionState(const btTransform& initialpos, Ogre::SceneNode* node) {
    mVisibleobj = node;
    mPos1 = initialpos;
}
virtual ~OgreMotionState() {}

void setNode(Ogre::SceneNode* node) {
    mVisibleobj = node;
}
void updateTransform(btTransform& newpos) {
    mPos1 = newpos;
}
}

#pragma once

#include <Ogre.h>

class Court:GameObject{
protected:
	Ogre::SceneNode* wallnode;
	Ogre::SceneNode* frontnode;
	Ogre::SceneNode* backnode;
	Ogre::SceneNode* floornode;
	Ogre::SceneNode* ceilingnode;
}

#include "Court.h"

/*
Regulation Court Size: l:w:h 40:20:20 feet (480:240:240 inches)
*/

Court::Court(void){
//create court node
	rootNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("courtNode");

//declare plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y,0);

//Construct planes, bind nodes
	//front wall
	Ogre::MeshManager::getSingleton().createPlane("frontwall",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
240,240,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* frontE = mSceneMgr->createEntity("FrontWallEntity","frontwall");
	Ogre::SceneNode* frontN=rootNode->createChildSceneNode("frontwallNode");
	frontN->attachObject(frontE);	

	//frontE->setMaterialName("Examples/Rockwall");
	frontE->setCastShadows(false);
	frontE->translate(0,-240,0);

}

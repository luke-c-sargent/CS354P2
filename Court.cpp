#include "Court.h"
#include <stdio.h>

Court::Court(Ogre::SceneManager* smp){
    //init court vals
    length=480;
    width=240;
    height=240;
    sceneMgr=smp;

    //create court node
    rootNode=sceneMgr->getRootSceneNode()->createChildSceneNode("courtNode");

    //declare plane
    plane = Ogre::Plane(Ogre::Vector3::UNIT_Y,0);

    //Construct planes, bind nodes
        //front wall
    createPlane("frontwall",width,height,"Court/Front",Ogre::Vector3(0,0,-(length/2)),Ogre::Vector3(1,0,0),90);
        //back wall
    createPlane("backwall",width,height,"Court/Back",Ogre::Vector3(0,0,(length/2)),Ogre::Vector3(1,0,0),-90);
        //left wall
    createPlane("leftwall",height,length,"Court/Side",Ogre::Vector3(-(width/2),0,0),Ogre::Vector3(0,0,1),-90);
        //right wall
    createPlane("rightwall",height,length,"Court/Side",Ogre::Vector3((width/2),0,0),Ogre::Vector3(0,0,1),90);
        //ceiling
    createPlane("ceiling",height,length,"Court/Ceiling",Ogre::Vector3(0,(height/2),0),Ogre::Vector3(0,0,1),180);
        //floor
    createPlane("floor",height,length,"Court/Floor",Ogre::Vector3(0,-(height/2),0),Ogre::Vector3(0,0,1),0);
}

void Court::createPlane(Ogre::String name, Ogre::Real x, Ogre::Real y, Ogre::String material, Ogre::Vector3 translation, Ogre::Vector3 rotationvector,Ogre::Real degree){
    Ogre::MeshManager::getSingleton().createPlane(name,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
x,y,10,10,true,1,1,1,Ogre::Vector3::UNIT_Z);
    Ogre::Entity* entity = sceneMgr->createEntity( name);
    Ogre::SceneNode* node=rootNode->createChildSceneNode();
    node->attachObject(entity);

    entity->setMaterialName(material);
    entity->setCastShadows(true);
    node->rotate(Ogre::Quaternion(Ogre::Degree(degree),rotationvector));
    node->translate(translation);

}

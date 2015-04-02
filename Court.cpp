#include "Court.h"
#include <stdio.h>

using std::cout;

Court::Court(Ogre::SceneManager* smp){
    //init court vals
    name="Court";
    length=480;
    width=240;
    height=240;
    goalline=180;
    sceneMgr=smp;

    position=btVector3(0,0,0);
    inertia=btVector3(0,0,0);
    rotation=btQuaternion(0,0,0,1);
    mass=0;

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

    addWall(body,shape,ms,btVector3(0, 1, 0),btVector3(0, -120, 0),btQuaternion(0, 0, 0, 1));//bottom
    addWall(body2,shape2,ms2,btVector3(1,0,0),btVector3(-120,0,0),btQuaternion(0, 0, 0, 1));//left
    addWall(body3,shape3,ms3,btVector3(-1,0,0),btVector3(120,0,0),btQuaternion(0, 0, 0, 1));//right
    addWall(body4,shape4,ms4,btVector3(0,-1,0),btVector3(0,120,0),btQuaternion(0, 0, 0, 1));//top
    addWall(body5,shape5,ms5,btVector3(0,0,1),btVector3(0,0,-240),btQuaternion(0, 0, 0, 1));//front
    addWall(body6,shape6,ms6,btVector3(0,0,-1),btVector3(0,0,240),btQuaternion(0, 0, 0, 1));//back
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

void Court::addWalls(){


}

void Court::addWall(btRigidBody*& bod,
                    btCollisionShape*& shap,
                    btMotionState*& mos,
                    btVector3 normal,
                    btVector3 pos,
                    btQuaternion ori)
{
    shap = new btStaticPlaneShape(normal, 1);
    mos = new btDefaultMotionState(btTransform(ori, pos));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, mos, shap, btVector3(0, 0, 0));
    groundRigidBodyCI.m_restitution=1.0;
    groundRigidBodyCI.m_friction=0.5;
    groundRigidBodyCI.m_rollingFriction=0.5;
    bod = new btRigidBody(groundRigidBodyCI);
}

void Court::addToSimulator(){
    simulator->getWorld()->addRigidBody(body);//bottom
    simulator->getWorld()->addRigidBody(body2);//left
    simulator->getWorld()->addRigidBody(body3);//right
    simulator->getWorld()->addRigidBody(body4);//top
    simulator->getWorld()->addRigidBody(body5);//front
    simulator->getWorld()->addRigidBody(body6);//back

}

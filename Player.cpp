#include <Player.h>
#include <btBulletDynamicsCommon.h>

using std::cout;

Player::Player(Ogre::SceneManager* smp){
    //set scene manager pointer
    sceneMgr=smp;

    //physical constants
    l=25;
    w=25;
    h=50;

    restitution=0.835;//avg of allowable extremes

    name="Player";

    position = btVector3(0,-120+h/2,180);
    inertia= btVector3(0,0,0);
    rotation=btQuaternion(0,0,0,1);

    mass=1000.0f;
    restitution=0.9f;
    friction=0;


    //bind player
    rootNode=sceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode");
    Ogre::Entity * entity=sceneMgr->createEntity("Player","cube.mesh");
    rootNode->attachObject(entity);

    //purdiness
    entity->setCastShadows(true);
    entity->setMaterialName("PlayerWire");


    rootNode->scale(w/100,h/100,l/100);


    //bt values
    shape = new btBoxShape(btVector3(/*w/2.,l/2.,h/2.*/w/2.,h/2.,l/2.));
    shape->calculateLocalInertia(mass,inertia);



    ms = new btDefaultMotionState(btTransform(rotation, position));

    btRigidBody::btRigidBodyConstructionInfo bodyCI(mass, ms, shape, inertia);

    //add other physics constants
    bodyCI.m_restitution=restitution;
    bodyCI.m_friction=friction;
    bodyCI.m_rollingFriction=0.2;//!!!

    body = new btRigidBody(bodyCI);
    body->setActivationState(DISABLE_DEACTIVATION);
    btTransform btt;
    ms->getWorldTransform(btt);
    btVector3 org=btt.getOrigin();
    cout <<"\n" << org.getY() <<"\n";
}


void Player::setPos(Ogre::Vector3 pos){
    position = btVector3(pos.x,pos.y,pos.z);
}

btScalar Player::getX(){
    return position.getX();
}
btScalar Player::getY(){
    return position.getY();
}
btScalar Player::getZ(){
    return position.getZ();
}

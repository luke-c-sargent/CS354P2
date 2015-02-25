/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "TutorialApplication.h"

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3f,0.1f,0.3f));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	Ogre::Entity* ball = mSceneMgr->createEntity("ball","sphere.mesh");
	ball->setCastShadows(true);

	Ogre::SceneNode* ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ballNode");
	ballNode->attachObject(ball);
	ball->setMaterialName("Examples/Eyeball");


//walls
	//plane declaration
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y,0);
	//ground
	Ogre::MeshManager::getSingleton().createPlane("ground",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundE = mSceneMgr->createEntity("GroundEntity","ground");
	Ogre::SceneNode* groundNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("groundNode");
	groundNode->attachObject(groundE);
	groundE->setMaterialName("Examples/Rockwall");
	groundE->setCastShadows(false);
	groundNode->translate(0,-700,0);
	//right wall
	Ogre::MeshManager::getSingleton().createPlane("rightwall",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* rwallE = mSceneMgr->createEntity("RightWallEntity","rightwall");
	Ogre::SceneNode* rwallNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("rwallNode");
	rwallNode->attachObject(rwallE);
	rwallE->setMaterialName("Examples/Rockwall");
	rwallE->setCastShadows(false);
	rwallNode->rotate(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3(0,0,1)));
    rwallNode->translate(700,0,0);
	//left wall
    Ogre::MeshManager::getSingleton().createPlane("leftwall",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* lwallE = mSceneMgr->createEntity("LeftWallEntity","leftwall");
	Ogre::SceneNode* lwallNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("lwallNode");
	lwallNode->attachObject(lwallE);
	lwallE->setMaterialName("Examples/Rockwall");
	lwallE->setCastShadows(false);
	lwallNode->rotate(Ogre::Quaternion(Ogre::Degree(-90),Ogre::Vector3(0,0,1)));
    lwallNode->translate(-700,0,0);
    //back wall
    Ogre::MeshManager::getSingleton().createPlane("backwall",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* bwallE = mSceneMgr->createEntity("BackWallEntity","backwall");
	Ogre::SceneNode* bwallNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("bwallNode");
	bwallNode->attachObject(bwallE);
	bwallE->setMaterialName("Examples/Rockwall");
	bwallE->setCastShadows(false);
	bwallNode->rotate(Ogre::Quaternion(Ogre::Degree(90),Ogre::Vector3(1,0,0)));
    bwallNode->translate(0,0,-700);
	//ceiling
    Ogre::MeshManager::getSingleton().createPlane("ceiling",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,plane,
1500,1500,20,20,true,1,5,5,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* ceilingE = mSceneMgr->createEntity("CeilingEntity","ceiling");
	Ogre::SceneNode* ceilingNode=mSceneMgr->getRootSceneNode()->createChildSceneNode("ceilingNode");
	ceilingNode->attachObject(ceilingE);
	ceilingE->setMaterialName("Examples/Rockwall");
	ceilingE->setCastShadows(false);
	ceilingNode->rotate(Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3(1,0,0)));
    ceilingNode->translate(0,700,0);
    //lighting
	Ogre::Light * light = mSceneMgr->createLight("light1");
	light->setPosition(Ogre::Vector3(0,500,500));
	light->setDiffuseColour(1.0, 1.0, 1.0);
	light->setSpecularColour(1.0, 0.0, 0.0);
}

/*void TutorialApplication::createFrameListener(void)
{
    /*
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	OgreBites::InputContext inputContext;
	inputContext.mMouse = mMouse;
	inputContext.mKeyboard = mKeyboard;
    //mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, inputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();

    // create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}//*/

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

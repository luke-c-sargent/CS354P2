#include "BaseApplication.h"

//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mTrayMgr(0),
    mCameraMan(0),
    mDetailsPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0)
{
}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    if (mTrayMgr) delete mTrayMgr;
    if (mCameraMan) delete mCameraMan;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

void BaseApplication::createScene(void)
{
    // create your scene
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3f,0.1f,0.3f));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	Ogre::Entity* ball = mSceneMgr->createEntity("ball","sphere.mesh");
	ball->setCastShadows(true);

	ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ballNode");
	ballNode->attachObject(ball);
	ball->setMaterialName("Examples/Eyeball");
    //set ball initial values
    ballr=100;
    ballspd=100.0;
    srand(time(NULL));
    int rando = rand();

    //Ogre::LogManager::getSingletonPtr()->logMessage("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    //Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(rando));
    float x = (float)((rando%100)-50)/50.;
    rando=rando/100;
    float y = (float)((rando%100)-50)/50.;
    rando=rando/100;
    float z = (float)((rando%100)-50)/50.;
    rando=rando/100;
    balldir = Ogre::Vector3(x,y,z);
    roomsize=700;
    Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(balldir));
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

//-------------------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "Assignment 1 Render Window");

        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
}
//-------------------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,1800));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
//-------------------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
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
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, inputContext, this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();

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
}
//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//-------------------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}
//-------------------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();

    return true;
};
//-------------------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

    //Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::StringConverter::toString(mouseloc));


    return true;
}
//-------------------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }
    else if (arg.key == OIS::KC_1)
    {
        ballspd=0;
    }
    else if (arg.key == OIS::KC_2)
    {
        ballspd=100;
    }
    else if (arg.key == OIS::KC_3)
    {
        ballspd=200;
    }
    else if (arg.key == OIS::KC_4)
    {
        ballspd=400;
    }
    else if (arg.key == OIS::KC_5)
    {
        ballspd=600;
    }
    else if (arg.key == OIS::KC_6)
    {
        ballspd=900;
    }
    mCameraMan->injectKeyDown(arg);
    return true;
}

bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{
    mCameraMan->injectKeyUp(arg);
    return true;
}

bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    /*
    if (mTrayMgr->injectMouseMove(arg)) return true;
    mCameraMan->injectMouseMove(arg);
    */
    return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}

//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

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
        BaseApplication app;

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

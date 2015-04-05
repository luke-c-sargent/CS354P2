#include "BaseApplication.h"
#include <boost/lexical_cast.hpp>
#include <string>

using std::cout;


/* D-BUGZ */
int counter = 0;


//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mCameraMan(0),
    mDetailsPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    isPaused(true),
    mcapture(true)
    //ns(GAME_SINGLE)
{
  networkObject=new Network(0,this);
}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    if (mCameraMan) delete mCameraMan;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

void BaseApplication::createScene(void)
{
    //init sound
    sounds = new SoundEffects();
    event = new SDL_Event();
    sounds->init();
    sounds->load_files();
    sounds->playMusic();

    //init sim
    sim = new Simulator();

    // create your scene
    mSceneMgr->setAmbientLight(Ogre::ColourValue(.5f,0.45f,0.4f,.3f));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    //CEGUI
    mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
    gui = new BaseGui(this);
    gui->init();

    //create elements
    Court * court = new Court(mSceneMgr);
    ball = new Ball(mSceneMgr);
    player = new Player(mSceneMgr);


    ball->setSimulator(sim);
    court->setSimulator(sim);


    //create sim
    /* */
    sim->addObject(ball);
    sim->addObject(player);
    sim->addObject(court);
    court->addToSimulator();
    //mSceneMgr->getSceneNode("PlayerNode")->translate(player->getPos());

    //lighting
	  Ogre::Light * light = mSceneMgr->createLight("light1");
    light->setType(Ogre::Light::LT_POINT);
    light->setPosition(Ogre::Vector3(0,110,0));
    light->setDiffuseColour(1.0, 0.95, 0.6);
    light->setSpecularColour(1.0, 1.0, 1.0);
    light->setAttenuation(400,.1,.00001,.00004);

    SoundEffects *sounds = new SoundEffects();
    sounds->init();
    sounds->load_files();
    sounds->playMusic();

}

//kill music
void BaseApplication::musicOff()
{
    sounds->playMusic();
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

    // Position it
    mCamera->setPosition(Ogre::Vector3(0,0,400));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-200));
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
    pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));

//mouse capture
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

    up=down=left=right=false;


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

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    processUnbufferedInput(evt);

    static Ogre::Real mMove = 100;//0.8; // The movement constant, unit/sec
    Ogre::Vector3 transVector = Ogre::Vector3::ZERO;
    btVector3 playerLV=btVector3(transVector.x,transVector.y,transVector.z);


    if(!isPaused){
    	if(up){
    	    if(player->getZ() > -240 + (player->l)/2.0f) //up
    		transVector.z += -mMove;

    	}
    	if(left){
    	    //cout << player->getX();
    	    if (player->getX() > -120 + (player->w)/2.0f) // left
    		transVector.x += -mMove;
    	}
    	if(down){
    	    if (player->getZ() < 240 - (player->l)/2.0f) // Down
    		transVector.z += mMove;
    	}
    	if(right){
    	    if (player->getX() < 120 - (player->w)/2.0f) // right
    		transVector.x += mMove;
    	}

      //player->setPos( player->getPos() + (transVector) );
      //player->setTransform(player->getPos());
      //player->getNode()->translate(transVector, Ogre::Node::TS_LOCAL);
      playerLV=btVector3(transVector.x,transVector.y,transVector.z);
    }


    //place camera
    Ogre::Vector3 behindplayer;
    if(networkObject->curState==GAME_CLIENT){
      behindplayer = player2->getPos() + Ogre::Vector3(0,60,200);
    }
    else{
      behindplayer = player->getPos() + Ogre::Vector3(0,60,200);
    }
    mCamera->setPosition(behindplayer);
    // Look back along -Z
    Ogre::Vector3 target = behindplayer + Ogre::Vector3(0,-10,-10);
    //mCamera->lookAt(Ogre::Vector3(0,0,-200));

    //packetswap
    if(networkObject->connected){
      int packetsize;
      if(networkObject->curState==GAME_CLIENT){
        packetsize=sizeof(btVector3);
        clientPacket(networkObject->toSendPacket,&playerLV);
      }else{
        packetsize=sizeof(btVector3)*3;
        serverPacket(networkObject->toSendPacket);
      }

      //cout << "to send packet: ";
      //networkObject->printpacket(networkObject->toSendPacket);

      networkObject->sendPacket(packetsize);
      networkObject->receivePacket();
      }

    if(!isPaused){
      updateFromPacket();

      player->getBody()->setLinearVelocity(playerLV);

    	//simulator step
      if(networkObject->curState!=GAME_CLIENT){
        //if(networkObject->curState!=GAME_SINGLE)
        sim->stepSimulation(evt.timeSinceLastFrame,10,1./60.);
      }
      else{
        player2->setTransform(playerLV);
      }
        //updateFromPacket();

        //player->updateTransform();

    	if(player->getBody()->hasContactResponse()){}

    	gui->incrementTics();
    }

    counter++;
    return true;
}

void BaseApplication::updateFromPacket(){

  btVector3 * bp, *pp, *p2p;
  if(networkObject->curState==GAME_SERVER){
    p2p=(btVector3 *)(networkObject->toRecPacket);
    player2->getBody()->setLinearVelocity(*p2p);

    //player2->setPos(*p2p);
//    player2->updateTransform();
    if(counter%60==0){
      //cout << "P2:" <<p2p->getX() <<","<< p2p->getY() <<","<<p2p->getZ() <<"\n";
    }
  }else if(networkObject->curState==GAME_CLIENT){
    //networkObject->toRecPacket[0]
    bp = (btVector3 *)(networkObject->toRecPacket);
    pp = (btVector3 *)(networkObject->toRecPacket+sizeof(btVector3));
    p2p = (btVector3 *)(networkObject->toRecPacket+2*sizeof(btVector3));
    player->setPos(*pp);
    player->getNode()->setPosition(Ogre::Vector3(pp->getX(),pp->getY(),pp->getZ()));
    //cout << p2p->getX()<<" "<<p2p->getY()<<" "<<p2p->getZ();
    player2->setPos(*p2p);
    player2->getNode()->setPosition(Ogre::Vector3(p2p->getX(),p2p->getY(),p2p->getZ()));
//  player->updateTransform();
    ball->setPos(*bp);
    ball->getNode()->setPosition(Ogre::Vector3(bp->getX(),bp->getY(),bp->getZ()));
//  ball->updateTransform();


    //btVector3 * btpp=(btVector3 *)bp;
    /*if(counter%60==0){
      cout << "BP:"<<bp->getX() <<","<< bp->getY() <<","<<bp->getZ() <<"\n";
      cout << "PP:"<<pp->getX() <<","<< pp->getY() <<","<<pp->getZ() <<"\n";
      cout << "P2P:"<<p2p->getX() <<","<< p2p->getY() <<","<<p2p->getZ() <<"\n";

    }*/
  }
}

void BaseApplication::clientPacket(char * b,btVector3* bv){

  //btVector3 bp=btVector3(ball->getPos().x,ball->getPos().y,ball->getPos().z);
  //btVector3 pp=btVector3(player2->getPos().x,player2->getPos().y,player2->getPos().z);

  memcpy(b,bv,sizeof(btVector3));
  //memcpy(b+sizeof(btVector3),&pp,sizeof(btVector3));
}

void BaseApplication::serverPacket(char * b){

  btVector3 bp=btVector3(ball->getPos().x,ball->getPos().y,ball->getPos().z);
  btVector3 pp=btVector3(player->getPos().x,player->getPos().y,player->getPos().z);
  btVector3 p2p=btVector3(player2->getPos().x,player2->getPos().y,player2->getPos().z);
  //cout << player2->getPos().x<<","<<player2->getPos().y<<","<<player2->getPos().z<<"\n";
  memcpy(b,&bp,sizeof(btVector3));
  memcpy(b+sizeof(btVector3),&pp,sizeof(btVector3));
  memcpy(b+sizeof(btVector3)*2,&p2p,sizeof(btVector3));
}

void BaseApplication::togglemouse(){
  mcapture=!mcapture;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
	if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }
    else if(arg.key == OIS::KC_9)
        {
            sounds->pauseMusic();
        }
    else if(arg.key == OIS::KC_M)
        {
            sounds->playEffect(1);
        }
    else if(arg.key == OIS::KC_1)
        {
            sounds->enableSound();
        }
    else if (arg.key == OIS::KC_P)
    {
      if(isPaused)
        isPaused=false;
      else
        isPaused=true;
    }
    else if(arg.key == OIS::KC_W){
        up=true;
    }
    else if(arg.key == OIS::KC_A){
        left=true;
    }
    else if(arg.key == OIS::KC_S){
        down=true;
    }
    else if(arg.key == OIS::KC_D){
        right=true;
    }

		CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
		context.injectKeyDown((CEGUI::Key::Scan)arg.key);
		context.injectChar((CEGUI::Key::Scan)arg.text);

	return true;
}

bool BaseApplication::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
}


bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{
    if(arg.key == OIS::KC_W){
        up=false;

    }
    else if(arg.key == OIS::KC_A){
        left=false;

    }
    else if(arg.key == OIS::KC_S){
        down=false;
    }
    else if(arg.key == OIS::KC_D){
        right=false;
    }

    CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key);

	return true;
}

bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	// Scroll wheel.
	if (arg.state.Z.rel)
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
	return true;
}

bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
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
/*
void BaseApplication::changeNetworkState(NetworkState in){
    ns = in;
}
*/
void BaseApplication::togglePause(){
  if(isPaused)
    isPaused=false;
  else
    isPaused=true;
}

void BaseApplication::pause(){
  isPaused=true;
}

void BaseApplication::unpause(){
  isPaused=false;
}

void BaseApplication::insertP2(){
  player2= new Player(mSceneMgr,"Player2");
  player->setTransform(player->pos1);
  player->setPos(player->pos1);
  player2->setTransform(player->pos2);
  player2->setPos(player->pos2);
  sim->addObject(player2);
  player->updateTransform();
  player2->updateTransform();

}




//```````````````````````````


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

        //parse args

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
        app.networkObject->closeConnections();
        return 0;
    }

#ifdef __cplusplus
}
#endif

#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include "GameObject.h"
#include "Court.h"
#include "Ball.h"
#include "Player.h"
#include "Simulator.h"
#include "SoundEffects.h"



#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h> //from 0.8 it's just Ogre/Renderer.h

#include <SdkTrays.h>
#include <SdkCameraMan.h>

class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
    BaseApplication(void);
    ~BaseApplication(void);
    void go(void);
    void musicOff();
    int bouncest;

protected:
    bool setup();
    bool configure(void);
    void chooseSceneManager(void);
    void createCamera(void);
    void createFrameListener(void);
    void createScene(void);
    void destroyScene(void);
    void createViewports(void);
    void setupResources(void);
    void createResourceListener(void);
    void loadResources(void);
	CEGUI::Window *score;
	CEGUI::Window *bounces;
	CEGUI::Window *time;
	int scoret;
	int timet;
    //keys
    bool up,down,left,right;

    // Ogre::FrameListener
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    bool mouseMoved( const OIS::MouseEvent &arg );
    bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    bool processUnbufferedInput(const Ogre::FrameEvent& evt);

    // Ogre::WindowEventListener
    //Adjust mouse clipping area
    void windowResized(Ogre::RenderWindow* rw);
    //Unattach OIS before window shutdown (very important under Linux)
    void windowClosed(Ogre::RenderWindow* rw);

    Ogre::Root *mRoot;
    Ogre::Camera* mCamera;
    Ogre::SceneManager* mSceneMgr;
    Ogre::RenderWindow* mWindow;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
	Ogre::OverlaySystem *mOverlaySystem;
	
	CEGUI::OgreRenderer* mRenderer;

    // OgreBites
    OgreBites::SdkCameraMan* mCameraMan;       // basic camera controller
    OgreBites::ParamsPanel* mDetailsPanel;     // sample details panel
    bool mCursorWasVisible;                    // was cursor visible before dialog appeared
    bool mShutDown;

    //SoundEffects
    SoundEffects *sounds;
    SDL_Event *event;

    //OIS Input devices
    OIS::InputManager* mInputManager;
    OIS::Mouse*    mMouse;
    OIS::Keyboard* mKeyboard;

    //mouse location-unused
    //Ogre::Vector2 mouseloc;

    //simulator
    Simulator* sim;

    //ball mechanics
    Ogre::SceneNode* ballNode;
    Ogre::Vector3 balldir;
    Ogre::Real ballspd;
    Ogre::Real ballr;
    Ogre::Real roomsize;
    Player * player;
};

#endif // #ifndef __BaseApplication_h_

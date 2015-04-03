#include <string.h>
#include <boost/lexical_cast.hpp>

#include "BaseGui.h"
#include "BaseApplication.h"
#include "Network.h"

using std::string;
using std::cout;


CEGUI::Window * wp;

BaseGui::BaseGui(BaseApplication* ba){
	baseapp=ba;
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	
	mainsheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	timet = 0;
	scoret1 = 0;
	scoret2 = 0;
	bouncest = 0;
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainsheet);
}

bool BaseGui::init(){
	float bheight,bwidth,mx,my;
	//button dimensions
	bwidth = 0.25;
	bheight= 0.05;

	//center menu
	mx=0.5-bwidth/2.0;
	my=0.5-3*bheight/2.0;

  	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	
	CEGUI::WindowManager::getSingleton().destroyWindow( mainsheet );
	mainsheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	//mainsheet->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),CEGUI::UDim(0.5f, 0)));

	CEGUI::Window *single = wmgr.createWindow("TaharezLook/Button", "b1");
	CEGUI::Window *hostdouble = wmgr.createWindow("TaharezLook/Button", "b2");
	CEGUI::Window *joindouble = wmgr.createWindow("TaharezLook/Button", "b3");

	single->setText("Single Player");
	single->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	single->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my, 0)));
	single->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BaseGui::hudsingle,this));

	hostdouble->setText("Host Multiplayer");
	hostdouble->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	hostdouble->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my+bheight, 0)));
	hostdouble->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BaseGui::host,this));
	
	joindouble->setText("Join Multiplayer");
	joindouble->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	joindouble->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my+bheight*2, 0)));
	joindouble->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BaseGui::join,this));

	mainsheet->addChild(single);
	mainsheet->addChild(hostdouble);
	mainsheet->addChild(joindouble);
	
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainsheet);
}

bool BaseGui::title(const CEGUI::EventArgs& /*e*/){
	init();
}

bool BaseGui::connectTo(const CEGUI::EventArgs&){
     baseapp->networkObject = new Network(2);
     string networkname = "riesen-chocolate-chews";
     baseapp->networkObject->searchForConnection(55565, networkname);
}

bool BaseGui::incrementTics(){
    if (mainsheet->isChild("Time")){
      timet++;
      std::string str3 = boost::lexical_cast<std::string>(timet);
      CEGUI::Window *time = mainsheet->getChild("Time");
      time->setText("tics: " + str3);
    }
}

bool BaseGui::incrementScore1(){
    if (mainsheet->isChild("Score1")){
      scoret1++;
      std::string str3 = boost::lexical_cast<std::string>(scoret1);
      CEGUI::Window *score1 = mainsheet->getChild("Score1");
      score1->setText("score: " + str3);
    }
}

bool BaseGui::incrementScore2(){
  if (mainsheet->isChild("Score2")){
    scoret2++;
    std::string str3 = boost::lexical_cast<std::string>(scoret2);
    CEGUI::Window *score2 = mainsheet->getChild("Score2");
    score2->setText("score: " + str3);
  }
}

bool BaseGui::incrementBounces(){
  if (mainsheet->isChild("Bounces")){
    bouncest++;
    std::string str3 = boost::lexical_cast<std::string>(bouncest);
    CEGUI::Window *bounces = mainsheet->getChild("Bounces");
    bounces->setText("bounces: " + str3);
  }
}

// 	timet++;
// 	
// 	std::string str = boost::lexical_cast<std::string>(scoret);
// 	std::string str2 = boost::lexical_cast<std::string>(bouncest);
// 	std::string str3 = boost::lexical_cast<std::string>(timet);
// 	
// 	score->setText("score: " + str);
// 	bounces->setText("bounces: " + str2);
// 	time->setText("tics: " + str3);
// 	

bool BaseGui::join(const CEGUI::EventArgs& /*e*/){
	float mx=0.5-0.25/2.0;
	float my=0.5-3*0.05/2.0;

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::WindowManager::getSingleton().destroyWindow( mainsheet );
	mainsheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::Window *window = wmgr.createWindow("TaharezLook/FrameWindow", "Window");
    window->setText("Enter Address:");
	window->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.20, 0)));
	window->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my, 0)));
	CEGUI::Window *window2 = wmgr.createWindow("TaharezLook/Editbox", "Window2");
    wp=window2;
	window2->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.5, 0)));
	window2->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),CEGUI::UDim(0.00, 0)));
	CEGUI::Window *window3 = wmgr.createWindow("TaharezLook/Button", "Window3");
	window3->setText("Go!");
	window3->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.5, 0)));
	window3->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0),CEGUI::UDim(0.50, 0)));
    window3->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BaseGui::joingo,this));
	
	mainsheet->addChild(window);
	window->addChild(window2);
	window->addChild(window3);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainsheet);
	
	//client
// 	baseapp->networkObject = new Network(2);
// 	string networkname = "riesen-chocolate-chews";
// 	baseapp->networkObject->searchForConnection(55565, networkname);
}

bool BaseGui::joingo(const CEGUI::EventArgs& /*e*/){
    //client connection
    baseapp->networkObject = new Network(2);
    cout << wp->getText() << "\n\n\n";
    //string networkname = "riesen-chocolate-chews";
    string networkname = wp->getText().c_str();
    baseapp->networkObject->searchForConnection(55565, networkname);
}

bool BaseGui::host(const CEGUI::EventArgs& /*e*/){
	float mx=0.5-0.25/2.0;
	float my=0.5-3*0.05/2.0;

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::WindowManager::getSingleton().destroyWindow( mainsheet );
	mainsheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::Window *window = wmgr.createWindow("TaharezLook/Button", "Window");
	window->setText("Waiting...");
	window->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	window->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my, 0)));
	
	mainsheet->addChild(window);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainsheet);
	
	//server
    baseapp->networkObject = new Network(1);
    baseapp->networkObject->waitForConnection(55565);


}

bool BaseGui::hudsingle(const CEGUI::EventArgs& /*e*/){
	baseapp->unpause();

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::WindowManager::getSingleton().destroyWindow( mainsheet );
	mainsheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	CEGUI::Window *score;
	CEGUI::Window *bounces;
	CEGUI::Window *time;

	score = wmgr.createWindow("TaharezLook/Button", "Score1");
	bounces = wmgr.createWindow("TaharezLook/Button", "Bounces");
	time = wmgr.createWindow("TaharezLook/Button", "Time");

	scoret1 = 0;
	timet = 0;
	bouncest = 0;

	score->setText("score: 0");
	score->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	score->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.0f, 0)));
	bounces->setText("bounces: 0");
	bounces->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	bounces->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.05f, 0)));
	time->setText("time: 0");
	time->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	time->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.1f, 0)));
	mainsheet->addChild(score);
	mainsheet->addChild(bounces);
	mainsheet->addChild(time);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainsheet);
}

bool BaseGui::huddouble(const CEGUI::EventArgs& /*e*/){
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::WindowManager::getSingleton().destroyWindow( mainsheet );
	mainsheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	
	CEGUI::Window *score1;
	CEGUI::Window *score2;
	CEGUI::Window *bounces;
	CEGUI::Window *time;

	score1 = wmgr.createWindow("TaharezLook/Button", "Score1");
	score2 = wmgr.createWindow("TaharezLook/Button", "Score2");
	bounces = wmgr.createWindow("TaharezLook/Button", "Bounces");
	time = wmgr.createWindow("TaharezLook/Button", "Time");

	scoret1 = 0;
	scoret2 = 0;
	timet = 0;
	bouncest = 0;

	score1->setText("score: 0");
	score1->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	score1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.0f, 0)));
	score2->setText("score: 0");
	score2->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	score2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0),CEGUI::UDim(0.00f, 0)));
	bounces->setText("bounces: 0");
	bounces->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	bounces->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.05f, 0)));
	time->setText("time: 0");
	time->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	time->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.1f, 0)));
	mainsheet->addChild(score1);
	mainsheet->addChild(score2);
	mainsheet->addChild(bounces);
	mainsheet->addChild(time);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mainsheet);
	return true;
}

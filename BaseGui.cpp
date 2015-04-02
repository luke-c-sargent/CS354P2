#include "BaseGui.h"

BaseGui::BaseGui(){
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
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
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	//sheet->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),CEGUI::UDim(0.5f, 0)));

	CEGUI::Window *single = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/b1");
	CEGUI::Window *hostdouble = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/b2");
	CEGUI::Window *joindouble = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/b3");

	single->setText("Single Player");
	single->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	single->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my, 0)));
	single->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BaseGui::hudsingle,this));

	hostdouble->setText("Host Multiplayer");
	hostdouble->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	hostdouble->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my+bheight, 0)));

	joindouble->setText("Join Multiplayer");
	joindouble->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	joindouble->setPosition(CEGUI::UVector2(CEGUI::UDim(mx, 0),CEGUI::UDim(my+bheight*2, 0)));
	joindouble->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(&BaseGui::huddouble,this));

	sheet->addChild(single);
	sheet->addChild(hostdouble);
	sheet->addChild(joindouble);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

bool BaseGui::title(const CEGUI::EventArgs& /*e*/){
	init();
}

bool BaseGui::join(const CEGUI::EventArgs& /*e*/){
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

bool BaseGui::host(const CEGUI::EventArgs& /*e*/){
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

bool BaseGui::hudsingle(const CEGUI::EventArgs& /*e*/){
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	CEGUI::Window *score;
	CEGUI::Window *bounces;
	CEGUI::Window *time;

	score = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/Score");
	bounces = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/bounce");
	time = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/time");

	scoret1 = 0;
	timet = 0;
	bouncest = 0;

	score->setText("score: ");
	score->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	score->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.0f, 0)));
	bounces->setText("bounces: ");
	bounces->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	bounces->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.05f, 0)));
	time->setText("time: ");
	time->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	time->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.1f, 0)));
	sheet->addChild(score);
	sheet->addChild(bounces);
	sheet->addChild(time);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

bool BaseGui::huddouble(const CEGUI::EventArgs& /*e*/){
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

	CEGUI::Window *score1;
	CEGUI::Window *score2;
	CEGUI::Window *bounces;
	CEGUI::Window *time;

	score1 = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/Score1");
	score2 = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/Score2");
	bounces = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/bounce");
	time = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/time");

	scoret1 = 0;
	scoret2 = 0;
	timet = 0;
	bouncest = 0;

	score1->setText("score: ");
	score1->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	score1->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.0f, 0)));
	score2->setText("score: ");
	score2->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	score2->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0),CEGUI::UDim(0.00f, 0)));
	bounces->setText("bounces: ");
	bounces->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	bounces->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.05f, 0)));
	time->setText("time: ");
	time->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	time->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0),CEGUI::UDim(0.1f, 0)));
	sheet->addChild(score1);
	sheet->addChild(score2);
	sheet->addChild(bounces);
	sheet->addChild(time);

	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

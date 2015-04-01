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
void BaseGui::title(){
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
	
	CEGUI::Window *single = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/b1");
	CEGUI::Window *hostdouble = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/b2");
	CEGUI::Window *joindouble = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/b3");
	
	single->setText("single");
	single->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	single->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),CEGUI::UDim(0.50f, 0)));
	hostdouble->setText("hostdouble");
	hostdouble->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	hostdouble->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),CEGUI::UDim(0.60f, 0)));
	joindouble->setText("joindouble");
	joindouble->setSize(CEGUI::USize(CEGUI::UDim(0.25, 0), CEGUI::UDim(0.05, 0)));
	joindouble->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),CEGUI::UDim(0.70f, 0)));
	sheet->addChild(single);
	sheet->addChild(hostdouble);
	sheet->addChild(joindouble);
	
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
}

void BaseGui::hudsingle(){
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
  
	CEGUI::Window *score;
	CEGUI::Window *bounces;
	CEGUI::Window *time;
	
	score = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/Score");
	bounces = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/bounce");
	time = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/time");
	
	scoret = 0;
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
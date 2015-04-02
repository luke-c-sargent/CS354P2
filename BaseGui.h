#pragma once

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h> //from 0.8 it's just Ogre/Renderer.h

class BaseApplication;

class BaseGui{
  protected:
    bool title(const CEGUI::EventArgs& /*e*/);
    bool host(const CEGUI::EventArgs& /*e*/);
    bool join(const CEGUI::EventArgs& /*e*/);
    bool hudsingle(const CEGUI::EventArgs& /*e*/);
    bool huddouble(const CEGUI::EventArgs& /*e*/);
    CEGUI::Window *mainsheet;
    BaseApplication * baseapp;
  public:
    BaseGui(BaseApplication* ba);
    bool init();
    bool pause();
    bool updateScore(int a, int b);
    bool updateBounces(int a);
    bool incrementTime(int a);
    int scoret1;
    int scoret2;
    int timet;
    int bouncest;
    int ipt;
    int paused;
};
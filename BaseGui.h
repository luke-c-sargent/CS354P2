#pragma once

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h> //from 0.8 it's just Ogre/Renderer.h

class BaseApplication;

class BaseGui{
  protected:
    bool connectTo(const CEGUI::EventArgs& /*e*/);
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
    bool incrementScore1();
    bool incrementScore2();
    bool incrementBounces();
    bool incrementTics();
    int scoret1;
    int scoret2;
    int timet;
    int bouncest;
};

#pragma once

#include <Ogre.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h> //from 0.8 it's just Ogre/Renderer.h

class BaseGui{
  protected:
  public:
    BaseGui();
    void title();
    void host();
    void join();
    void hudsingle();
    void huddouble();
    
    int scoret;
    int timet;
    int bouncest;
    int ipt;
    int paused;
};
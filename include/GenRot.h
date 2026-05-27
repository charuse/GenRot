#pragma once
#include "syati.h"

class GenRot : public NameObj {
public:
    GenRot(const char *pName);

    virtual bool rotater();
    virtual void init(const JMapInfoIter &rIter);
    virtual void movement();
    
    s32 mGenID;
    LiveActorGroup* mGroup;
    Rotater mRot;
  
};

struct Rotater {
    s32 x;
    s32 y;
    s32 z;
};
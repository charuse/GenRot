#pragma once
#include "syati.h"

struct Rotater {
    s32 x;
    s32 y;
    s32 z;
};

class GenRot : public NameObj {
public:
    GenRot(const char *pName);

    virtual bool rotater();
    virtual void init(const JMapInfoIter &rIter);
    virtual void control();
    
    LiveActorGroup* mGroup;
    Rotater mRot;
    s32 mGenID;
    bool mGo;
};
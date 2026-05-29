#pragma once
#include "syati.h"

class GenRot : public NameObj {
public:
    GenRot(const char *pName);

    virtual bool rotater();
    virtual void init(const JMapInfoIter &rIter);
    virtual void control();
    
    LiveActorGroup* mGroup;
    TVec3f mRot;
    s32 mGenID;
    bool mGo;
};
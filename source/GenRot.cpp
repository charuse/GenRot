#include "GenRot.h"
using namespace MR;

GenRot::GenRot(const char *pName) : NameObj(pName) {
    mGo = true;
}

bool GenRot::rotater() {
    s32 x = 0; 
    s32 grpSz = mGroup->mNumObjs;
    if (grpSz < 1) return false;

    while (x < grpSz) {
        LiveActor *currAct = mGroup->getActor(x);
        currAct->mRotation.x += mRot.x;
        currAct->mRotation.y += mRot.y;
        currAct->mRotation.z += mRot.z;
        ++x;
    }
    
    if (x == grpSz) return true;
    else {
        OSReport("[GenRot] Object amount inconsistent with amount rotated, failing. X: %d, GrpSz: %d\n", x, grpSz);
        return false;
    }
}

void GenRot::init(const JMapInfoIter &rIter) {
    connectToSceneMapObjMovement(this);
    getGeneratorID(rIter, &mGenID);
    getJMapInfoArg0NoInit(rIter, &mRot.x);
    getJMapInfoArg1NoInit(rIter, &mRot.y);
    getJMapInfoArg2NoInit(rIter, &mRot.z);

    AllLiveActorGroup* alag = getAllLiveActorGroup();
    s32 alSz = alag->mNumObjs;
    mGroup = new LiveActorGroup("GRGroup", alSz);

    for (s32 i = 0; i < alSz; i++) {
        LiveActor* currActor = alag->getActor(i);
        s16 matchid = currActor->mLinkedInfo.mLinkId;
        s16 checkid = mGenID;
        OSReport("[GenRot] Object: %s, mLinkID: %hd vs GenID: %hd\n", currActor->mName, matchid, checkid);
        if (matchid == checkid) {
            mGroup->registerActor(currActor);
            OSReport("[GenRot] Added Object %d to mGroup\n", currActor->mName);
        }
    }
}

void GenRot::control() {
    if (mGo) {
        mGo == false;

        rotater()
        ? OSReport("[GenRot] Rotated %d objects with ID %hd\n", mGroup->mNumObjs, mGroup->getActor(0)->mLinkedInfo.mLinkId) 
        , OSReport("[GenRot] Rotated by X: %d, Y: %d, Z: %d\n", mRot.x, mRot.y, mRot.z)
        : OSReport("[GenRot] Failed Rotate or 0 objects found\n");
    }
}
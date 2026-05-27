#include "GenRot.h"

GenRot::GenRot(const char *pName) : NameObj(pName) {/**/}

bool GenRot::rotater() {
    s32 grpSz = mGroup->mNumObjs;
    if (grpSz < 1) return false;
    for (s32 x = 0; x < grpSz; x++) {
        LiveActor *currAct = mGroup->getActor(x);
        currAct->mRotation.x += mRot.x;
        currAct->mRotation.y += mRot.y;
        currAct->mRotation.z += mRot.z;
    }
    return true;
}

void GenRot::init(const JMapInfoIter &rIter) {
    MR::connectToSceneMapObjMovement(this);
    MR::getGeneratorID(rIter, &mGenID);
    MR::getJMapInfoArg0NoInit(rIter, &mRot.x);
    MR::getJMapInfoArg1NoInit(rIter, &mRot.y);
    MR::getJMapInfoArg2NoInit(rIter, &mRot.z);
    AllLiveActorGroup* alag = MR::getAllLiveActorGroup();
    s32 alSz = alag->mNumObjs;
    mGroup = new LiveActorGroup("GenRotGroup", alSz);
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

    rotater()
    ? OSReport("[GenRot] Rotated %d objects with ID %hd\n", mGroup->mNumObjs, mGroup->getActor(0)->mLinkedInfo.mLinkId) 
    , OSReport("[GenRot] Rotated by X: %d, Y: %d, Z: %d\n", mRot.x, mRot.y, mRot.z)
    : OSReport("[GenRot] Failed Rotate or 0 objects found\n");
}

void GenRot::movement() {/**/}
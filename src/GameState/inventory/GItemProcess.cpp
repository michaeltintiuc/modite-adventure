#include "GItemProcess.h"
#include "GResources.h"
#include "GPlayer.h"
#include "Items.h"
#include "GStatSprite.h"
#include "GStatProcess.h"

GItemProcess *GItemProcess::SpawnItem(GGameState *aGameState, TInt aIp, TInt aItemNumber, TFloat aX, TFloat aY) {
  if (aItemNumber && aItemNumber < sizeof(items)) {
    GItemProcess *p = new GItemProcess(aGameState, aIp, aItemNumber, aX, aY);
    aGameState->AddProcess(p);
    return p;
  }
  else {
    return ENull;
  }
}

GItemProcess::GItemProcess(GGameState *aGameState, TInt aIp, TInt aItemNumber, TFloat aX, TFloat aY) : BProcess() {
  mGameState = aGameState;
  mIp = aIp;
  mItemNumber = aItemNumber;
  if (mItemNumber && mItemNumber < sizeof(items)) {
    mSprite = new GAnchorSprite(mGameState, ITEM_PRIORITY, ENVIRONMENT_SLOT, items[mItemNumber]);
    mSprite->type = STYPE_OBJECT;
    mSprite->cMask = STYPE_PLAYER;
    mSprite->w = mSprite->h = 32;
    mSprite->cx = -16;
    mSprite->x = aX;
    mSprite->y = aY;
    mGameState->AddSprite(mSprite);
//    mGameState->EndProgram(mIp, ATTR_KEEP, mItemNumber);
  }
  else {
    Panic("GItemProcess contructor: invalid item number: %d\n", mItemNumber);
  }
}

GItemProcess::~GItemProcess() {
  if (mSprite) {
    mSprite->Remove();
    delete mSprite;
    mSprite = ENull;
  }
}

TBool GItemProcess::RunBefore() {
  return ETrue;
}

TBool GItemProcess::RunAfter() {
  if (mSprite->cType & STYPE_PLAYER) {
    GStatProcess *p = new GStatProcess(mSprite->x, mSprite->y, itemNames[mItemNumber]);
    p->SetImageNumber(mSprite->mImageNumber);
    p->SetTimeout(5 * FRAMES_PER_SECOND);
    mGameState->AddProcess(p);
    GPlayer::mInventoryList.PickupItem(mItemNumber);
    // mark ObjectProgram at mIp that item has been picked up (don't persist it)
    mGameState->EndProgram(mIp, ATTR_KEEP, ATTR_GONE);
    GPlayer::mInventoryList.Dump();
    return EFalse;
  }
  return ETrue;
}
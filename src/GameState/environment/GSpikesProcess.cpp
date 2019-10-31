#include "GSpikesProcess.h"

TInt GSpikesProcess::mNumber = 0;

const TUint16 SPIKE_SPEED = 3;

static const ANIMSCRIPT spikesAnimation[] = {
  ABITMAP(ENVIRONMENT_SLOT),
  ASTEP(SPIKE_SPEED, IMG_SPIKES),
  ASTEP(SPIKE_SPEED, IMG_SPIKES + 1),
  ATYPE(STYPE_EBULLET),
  ASTEP(SPIKE_SPEED, IMG_SPIKES + 2),
  ASTEP(SPIKE_SPEED, IMG_SPIKES + 3),
  ATYPE(STYPE_DEFAULT),
  ASTEP(SPIKE_SPEED, IMG_SPIKES + 2),
  ASTEP(SPIKE_SPEED, IMG_SPIKES + 1),
  ASTEP(SPIKE_SPEED, IMG_SPIKES),
  AEND,
};

GSpikesProcess::GSpikesProcess(GGameState *aGameState, TInt aIp, TFloat aX, TFloat aY, TUint16 aParam)
    : GEnvironmentProcess(aGameState, aIp, aParam, aX, aY) {
  mParam = aParam;
  mGameState = aGameState;
  mSprite = new GAnchorSprite(mGameState, SPIKES_PRIORITY, ENVIRONMENT_SLOT, IMG_SPIKES);
  mSprite->cMask = STYPE_PLAYER;
  mSprite->w = mSprite->h = 24;
  mSprite->cx = -8;
  mSprite->cy = -4;
  mSprite->x = aX;
  mSprite->y = aY;
  mSprite->mSpriteSheet = gResourceManager.LoadSpriteSheet(DUNGEON_TILESET_OBJECTS_BMP);
  mGameState->AddSprite(mSprite);
  mState = EFalse;
  mTime = (7 * SPIKE_SPEED);
  mTimer = mParam * mTime;
}

GSpikesProcess::~GSpikesProcess() {
}

TBool GSpikesProcess::RunBefore() {
  if (mState) {
    if (mSprite->AnimDone()) {
      mTimer = mTime * mNumber;
      mState = EFalse;
    }
  }
  else {
    if (--mTimer <= 0) {
      mState = ETrue;
      mSprite->StartAnimation(spikesAnimation);
    }
  }
  return ETrue;
}

TBool GSpikesProcess::RunAfter() {
  return ETrue;
}

#ifndef MODITE_GENEMYPROCESS_H
#define MODITE_GENEMYPROCESS_H

#include <BProcess.h>
#include "GGameState.h"
#include "GGamePlayfield.h"
#include "GAnchorSprite.h"

const TFloat SEEK_Y = COLLISION_DELTA_Y;  // seek to player Y within this many pixels
const TFloat SEEK_X = 40; // seek to player X within this many pixels

enum {
  IDLE_STATE,
  WALK_STATE,
  ATTACK_STATE,
  HIT_STATE,
  DEATH_STATE,
};

static const char *stateMessages[] = {
  "IDLE STATE",
  "WALK STATE",
  "ATTACK STATE",
  "HIT STATE",
  "DEATH STATE",
};

class GEnemyProcess : public BProcess {
public:
  GEnemyProcess(GGameState *aGameState, TUint16 aSlot, TUint16 aParams);

  ~GEnemyProcess() OVERRIDE;

protected:
  GGameState *mGameState;
  GGamePlayfield *mPlayfield;
  TUint16 mParams;
  GAnchorSprite *mSprite;
  TFloat mStartX, mStartY;
  TUint16 mState;
  TUint16 mDirection;
  TUint16 mStep;
  TInt16 mAttackTimer;
  TInt16 mStateTimer;
  TInt16 mHitPoints;

  GAnchorSprite *mPlayerSprite;

public:
  TBool RunBefore() OVERRIDE;
  TBool RunAfter() OVERRIDE;

protected:
  // test if a wall in the specified direction from sprite's current location
  TBool IsWall(DIRECTION aDirection, TFloat aDx = 0.0, TFloat aDy = 0.0);

protected:
  TBool MaybeAttack();
  TBool MaybeHit();

protected:
  virtual void NewState(TUint16 aState, DIRECTION aDirection) = 0;

  virtual TBool IdleState() = 0;

  virtual TBool WalkState() = 0;

  TBool AttackState();

  TBool HitState();

  TBool DeathState();
};


#endif //MODITE_GENEMYPROCESS_H
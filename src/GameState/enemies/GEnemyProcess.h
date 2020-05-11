#ifndef MODITE_GENEMYPROCESS_H
#define MODITE_GENEMYPROCESS_H

#include "GProcess.h"
#include "GResources.h"
#include "GPlayer.h"
#include "GEnemySprite.h"

class GEnemyProcess : public GProcess {
public:
  EXPLICIT GEnemyProcess(GGameState *aGameState, TFloat aX, TFloat aY, TUint16 aSlot, TUint16 aAttribute);
  ~GEnemyProcess() OVERRIDE;

  void SetStatMultipliers(TFloat aModHitPoints = 1.0, TFloat aModStrength = 1.0, TFloat aModExperience = 1.0);

  TBool MaybeDamage(TBool aIsSpell);

protected:
  void StartBlink(TUint16 aTime) {
    mBlinkTimer = aTime;
  }

public:
  TBool RunBefore() OVERRIDE;

  TBool RunAfter() OVERRIDE;

public:
  GEnemySprite *mSprite;
  TBool mInvulnerable;   // cannot be attacked
  TInt16 mHitPoints, mMaxHitPoints;
  TInt32 mExperienceYield;

protected:
  GGameState *mGameState;
  GGamePlayfield *mPlayfield;
  TFloat mStartX, mStartY;
  DIRECTION mDirection;
  TUint16 mState, mStep; // state variables

private:
  TUint16 mBlinkTimer;
};

#endif //MODITE_GENEMYPROCESS_H

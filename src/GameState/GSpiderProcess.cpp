#include "GSpiderProcess.h"

/*********************************************************************************
 *********************************************************************************
 *********************************************************************************/

const TInt HIT_POINTS = 5;
const TInt IDLE_SPEED = 5;
const TInt SELECT_SPEED = 5;
const TInt WALK_SPEED = 5;
const TInt DEATH_SPEED = 5;
const TFloat VELOCITY = 2;

/*********************************************************************************
 *********************************************************************************
 *********************************************************************************/

/**
 * Animations
 */

/*
 ___    _ _         ______       _           _           _
|_ _|__| | | ___   / / ___|  ___| | ___  ___| |_ ___  __| |
 | |/ _` | |/ _ \ / /\___ \ / _ \ |/ _ \/ __| __/ _ \/ _` |
 | | (_| | |  __// /  ___) |  __/ |  __/ (__| ||  __/ (_| |
|___\__,_|_|\___/_/  |____/ \___|_|\___|\___|\__\___|\__,_|
 */

ANIMSCRIPT idleAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ALABEL,
  ASTEP(40, IMG_SPIDER_IDLE),
  ASTEP(4, IMG_SPIDER_IDLE + 1),
  ASTEP(40, IMG_SPIDER_IDLE + 2),
  ASTEP(4, IMG_SPIDER_IDLE + 1),
  ALOOP
};

static ANIMSCRIPT selectAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ALABEL,
  ASTEP(SELECT_SPEED, IMG_SPIDER_SELECTED + 0),
  ASTEP(SELECT_SPEED, IMG_SPIDER_SELECTED + 1),
  ASTEP(SELECT_SPEED, IMG_SPIDER_SELECTED + 2),
  ALOOP
};

static ANIMSCRIPT deathAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(DEATH_SPEED, IMG_SPIDER_WALK_RIGHT + 0),
  ASTEP(DEATH_SPEED, IMG_SPIDER_WALK_UP + 0),
  AFLIP(DEATH_SPEED, IMG_SPIDER_WALK_RIGHT + 0),
  ASTEP(DEATH_SPEED, IMG_SPIDER_WALK_DOWN + 0),
  ASTEP(DEATH_SPEED, IMG_SPIDER_WALK_RIGHT + 0),
  ASTEP(DEATH_SPEED, IMG_SPIDER_WALK_UP + 0),
  AFLIP(DEATH_SPEED, IMG_SPIDER_WALK_RIGHT + 0),
  ASTEP(DEATH_SPEED, IMG_SPIDER_WALK_DOWN + 0),
  AEND
};

/*
 ____
|  _ \  _____      ___ __
| | | |/ _ \ \ /\ / / '_ \
| |_| | (_) \ V  V /| | | |
|____/ \___/ \_/\_/ |_| |_|
*/

static ANIMSCRIPT idleDownAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ALABEL,
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 0),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 1),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 2),
  ALOOP
};

static ANIMSCRIPT walkDownAnimation1[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_DOWN + 0),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_DOWN + 1),
  AEND
};

static ANIMSCRIPT walkDownAnimation2[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_DOWN + 2),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_DOWN + 3),
  AEND
};

static ANIMSCRIPT attackDownAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_DOWN + 3),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_DOWN + 0),
  ATYPE(STYPE_EBULLET),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_DOWN + 1),
  ATYPE(STYPE_ENEMY),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_DOWN + 2),
  AEND
};

static ANIMSCRIPT hitDownAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_DOWN + 3),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_DOWN + 0),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_DOWN + 1),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_DOWN + 2),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_DOWN + 3),
  AEND
};

/*
 _          __ _
| |    ___ / _| |_
| |   / _ \ |_| __|
| |__|  __/  _| |_
|_____\___|_|  \__|

 */

static ANIMSCRIPT idleLeftAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ALABEL,
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 0),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 1),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 2),
  ALOOP
};

static ANIMSCRIPT walkLeftAnimation1[] = {
  ABITMAP(SPIDER_SLOT),
  AFLIP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 0),
  AFLIP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 1),
  AEND
};

static ANIMSCRIPT walkLeftAnimation2[] = {
  ABITMAP(SPIDER_SLOT),
  AFLIP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 2),
  AFLIP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 3),
  AEND
};

static ANIMSCRIPT attackLeftAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  AFLIP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 3),
  AFLIP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 0),
  ATYPE(STYPE_EBULLET),
  AFLIP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 1),
  ATYPE(STYPE_ENEMY),
  AFLIP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 2),
  AEND
};

static ANIMSCRIPT hitLeftAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  AFLIP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 3),
  AFLIP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 0),
  AFLIP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 1),
  AFLIP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 2),
  AFLIP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 3),
  AEND
};

/*
 ____  _       _     _
|  _ \(_) __ _| |__ | |_
| |_) | |/ _` | '_ \| __|
|  _ <| | (_| | | | | |_
|_| \_\_|\__, |_| |_|\__|
         |___/
 */

static ANIMSCRIPT idleRightAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ALABEL,
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 0),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 1),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 2),
  ALOOP
};

static ANIMSCRIPT walkRightAnimation1[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 0),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 1),
  AEND
};

static ANIMSCRIPT walkRightAnimation2[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 2),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_RIGHT + 3),
  AEND
};

static ANIMSCRIPT attackRightAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 3),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 0),
  ATYPE(STYPE_EBULLET),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 1),
  ATYPE(STYPE_ENEMY),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_RIGHT + 2),
  AEND
};

static ANIMSCRIPT hitRightAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 3),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 0),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 1),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 2),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_RIGHT + 3),
  AEND
};

/*
 _   _
| | | |_ __
| | | | '_ \
| |_| | |_) |
 \___/| .__/
      |_|
 */

static ANIMSCRIPT idleUpAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ALABEL,
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 0),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 1),
  ASTEP(IDLE_SPEED, IMG_SPIDER_IDLE + 2),
  ALOOP
};


static ANIMSCRIPT walkUpAnimation1[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_UP + 0),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_UP + 1),
  AEND
};

static ANIMSCRIPT walkUpAnimation2[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_UP + 2),
  ASTEP(SELECT_SPEED, IMG_SPIDER_WALK_UP + 3),
  AEND
};

static ANIMSCRIPT attackUpAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_UP + 3),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_UP + 0),
  ATYPE(STYPE_EBULLET),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_UP + 1),
  ATYPE(STYPE_ENEMY),
  ASTEP(SELECT_SPEED, IMG_SPIDER_ATTACK_UP + 2),
  AEND
};

static ANIMSCRIPT hitUpAnimation[] = {
  ABITMAP(SPIDER_SLOT),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_UP + 3),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_UP + 0),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_UP + 1),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_UP + 2),
  ASTEP(SELECT_SPEED, IMG_SPIDER_DAMAGE_UP + 3),
  AEND
};

/*********************************************************************************
 *********************************************************************************
 *********************************************************************************/

// constructor
GSpiderProcess::GSpiderProcess(GGameState *aGameState, GGamePlayfield *aGamePlayfield)
  : GEnemyProcess(aGameState,
                  aGamePlayfield,
                  SPIDER_SLOT,
                  SPIDER_PALETTE,
                  SPIDER_COLORS) {
  mSprite->x = 150.0;
  mSprite->y = 150.0;
  mSprite->mHitPoints = HIT_POINTS;
  NewState(IDLE_STATE, DIRECTION_DOWN);
}

GSpiderProcess::~GSpiderProcess() {
  //
}

/*********************************************************************************
 *********************************************************************************
 *********************************************************************************/

void GSpiderProcess::NewState(TUint16 aState, DIRECTION aDirection) {
  mState = aState;
  mSprite->mDirection = aDirection;
  mSprite->mDx = 0;
  mSprite->mDy = 0;
  switch (aState) {
    case IDLE_STATE:
      mStep = 0;
      mSprite->vx = 0;
      mSprite->vy = 0;
      switch (mSprite->mDirection) {
        case DIRECTION_UP:
          mSprite->StartAnimation(idleUpAnimation);
          break;
        case DIRECTION_DOWN:
          mSprite->StartAnimation(idleDownAnimation);
          break;
        case DIRECTION_LEFT:
          mSprite->StartAnimation(idleLeftAnimation);
          break;
        case DIRECTION_RIGHT:
          mSprite->StartAnimation(idleRightAnimation);
          break;
      }
      break;
    case WALK_STATE:
      mSprite->vx = 0;
      mSprite->vy = 0;
      switch (mSprite->mDirection) {
        case DIRECTION_UP:
          mStep = 1 - mStep;
          mSprite->StartAnimation(mStep ? walkUpAnimation1 : walkUpAnimation2);
          mSprite->vy = -VELOCITY;
          break;
        case DIRECTION_DOWN:
          mStep = 1 - mStep;
          mSprite->vy = VELOCITY;
          mSprite->StartAnimation(mStep ? walkDownAnimation1 : walkDownAnimation2);
          break;
        case DIRECTION_LEFT:
          mStep = 1 - mStep;
          mSprite->vx = -VELOCITY;
//          mSprite->mDx = -36;
          mSprite->StartAnimation(mStep ? walkLeftAnimation1 : walkLeftAnimation2);
          break;
        case DIRECTION_RIGHT:
          mStep = 1 - mStep;
          mSprite->vx = VELOCITY;
          mSprite->StartAnimation(mStep ? walkRightAnimation1 : walkRightAnimation2);
          break;
      }
      break;
    case ATTACK_STATE:
      mSprite->vx = 0;
      mSprite->vy = 0;
      mStep = 0;
      switch (mSprite->mDirection) {
        case DIRECTION_UP:
          mSprite->StartAnimation(attackUpAnimation);
          break;
        case DIRECTION_DOWN:
          mSprite->StartAnimation(attackDownAnimation);
          break;
        case DIRECTION_LEFT:
          mSprite->StartAnimation(attackLeftAnimation);
          break;
        case DIRECTION_RIGHT:
          mSprite->StartAnimation(attackRightAnimation);
          break;
      }
      break;
    case HIT_STATE:
      mSprite->vx = 0;
      mSprite->vy = 0;
      mStep = 0;
      switch (mSprite->mDirection) {
        case DIRECTION_UP:
          mSprite->StartAnimation(hitUpAnimation);
          break;
        case DIRECTION_DOWN:
          mSprite->StartAnimation(hitDownAnimation);
          break;
        case DIRECTION_LEFT:
          mSprite->StartAnimation(hitLeftAnimation);
          break;
        case DIRECTION_RIGHT:
          mSprite->StartAnimation(hitRightAnimation);
          break;
      }
      break;
    default:
      break;
  }
}

/*********************************************************************************
 *********************************************************************************
 *********************************************************************************/

TBool GSpiderProcess::MaybeHit() {
  if (mSprite->cType & STYPE_PBULLET) {
    printf("BULLET\n");
    if (--mSprite->mHitPoints <= 0) {
      mSprite->StartAnimation(deathAnimation);
      mState = DEATH_STATE;
      return ETrue;
    }
  }

  if (mSprite->cType & (STYPE_PLAYER | STYPE_PBULLET)) {
    GAnchorSprite *other = mSprite->mCollided;
    switch (other->mDirection) {
      case DIRECTION_RIGHT:
        printf("RIGHT animation\n");
        mSprite->StartAnimation(hitLeftAnimation);
        break;
      case DIRECTION_LEFT:
        printf("LEFT animation\n");
        mSprite->StartAnimation(hitRightAnimation);
        break;
      case DIRECTION_UP:
        printf("UP animation\n");
        mSprite->StartAnimation(hitDownAnimation);
        break;
      case DIRECTION_DOWN:
        printf("DOWN animation\n");
        mSprite->StartAnimation(hitUpAnimation);
        break;
    }
    mState = HIT_STATE;
    mSprite->cType &= ~(STYPE_PLAYER|STYPE_PBULLET);
    return ETrue;
  }
  return EFalse;
}

TBool GSpiderProcess::IdleState() {
  if (MaybeHit()) {
    return ETrue;
  }
  return ETrue;
}

TBool GSpiderProcess::WalkState() {
  if (MaybeHit()) {
    return ETrue;
  }
  return ETrue;
}

TBool GSpiderProcess::AttackState() {
  if (MaybeHit()) {
    return ETrue;
  }
  return ETrue;
}

TBool GSpiderProcess::HitState() {
  if (mSprite->AnimDone()) {
    NewState(IDLE_STATE, mSprite->mDirection);
    mSprite->cType &= STYPE_PLAYER;
  }

  return ETrue;
}

TBool GSpiderProcess::DeathState() {
  if (mSprite->AnimDone()) {
    NewState(IDLE_STATE, mSprite->mDirection);
    mSprite->cType &= STYPE_PLAYER|STYPE_PBULLET;
    mSprite->mHitPoints = HIT_POINTS;
  }

  return ETrue;
}

/*********************************************************************************
 *********************************************************************************
 *********************************************************************************/

TBool GSpiderProcess::RunBefore() {
  switch (mState) {
    case IDLE_STATE:
      return IdleState();
    case WALK_STATE:
      return WalkState();
    case ATTACK_STATE:
      return AttackState();
    case HIT_STATE:
      return HitState();
    case DEATH_STATE:
      return DeathState();
    default:
      return ETrue;
  }
}

TBool GSpiderProcess::RunAfter() {
  return ETrue;
}

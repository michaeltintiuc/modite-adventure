#include "GEnemyProcess.h"
#include "GStatProcess.h"
#include "GPlayer.h"
#include "GGameState.h"
#include "inventory/GItemProcess.h"
#include "Items.h"
#include "common/GSpellOverlayProcess.h"
#include "GEnemyDeathOverlayProcess.h"

TInt16 GEnemyProcess::mCount = 0;

GEnemyProcess::GEnemyProcess(GGameState *aGameState, TInt aIp, TUint16 aSlot, TUint16 aParams, TFloat aVelocity, TUint16 aAttribute)
    : GProcess(aAttribute), mGameState(aGameState), mIp(aIp), mPlayfield(aGameState->mGamePlayfield), mParams(aParams) {
  mSaveToStream = ETrue;
  mVelocity = aVelocity;
  mStateTimer = 0;
  mState = IDLE_STATE;
  mSprite = new GEnemySprite(mGameState, ENEMY_PRIORITY, aSlot);
  mSprite->type = STYPE_ENEMY;
  mSprite->cMask = STYPE_PLAYER | STYPE_PBULLET;
  mSprite->SetFlags(SFLAG_CHECK | SFLAG_RENDER_SHADOW);
  mSprite->w = 32;
  mSprite->h = 16;
  mSprite->cy = 4;
  mSprite->Name("ENEMY");
  mGameState->AddSprite(mSprite);
  mDirection = DIRECTION_DOWN;
  mState = IDLE_STATE;
  mStep = 0;

  mStartX = mStartY = 0;
  mPlayerSprite = GPlayer::mSprite;
  mAttackTimer = 1;

  mEnemyDeathOverlayProcess = ENull;
  mSpellOverlayProcess = ENull;
  mCount++;
}

GEnemyProcess::~GEnemyProcess() {
  if (mSprite) {
    mSprite->Remove();
    delete mSprite;
    mSprite = ENull;
  }
  mCount--;
}

TBool GEnemyProcess::IsWall(DIRECTION aDirection, TFloat aDx, TFloat aDy) {
  return !mSprite->IsFloor(aDirection, aDx, aDy);
}

TBool GEnemyProcess::CanWalk(DIRECTION aDirection, TFloat aVx, TFloat aVy) {
  return mSprite->CanWalk(aDirection, aVx, aVy);
}

/*********************************************************************************
 *********************************************************************************
 *********************************************************************************/

void GEnemyProcess::NewState(TUint16 aState, DIRECTION aDirection) {
  mState = aState;
  mSprite->mDirection = aDirection;
  mSprite->mDx = 0;
  mSprite->mDy = 0;

  switch (aState) {

    case IDLE_STATE:
      mStep = 0;
      mSprite->vx = 0;
      mSprite->vy = 0;
      Idle(aDirection);
      break;

    case WALK_STATE:
      mStep = 1 - mStep;
      Walk(aDirection);
      break;

    case ATTACK_STATE:
      mSprite->vx = 0;
      mSprite->vy = 0;
      mStep = 0;
      mAttackTimer = GPlayer::mGameOver ? (1 * FRAMES_PER_SECOND) : ATTACK_TIME;
      Attack(aDirection);
      break;

    case HIT_STATE:
      mSprite->vx = 0;
      mSprite->vy = 0;
      mStep = 0;
      mSprite->cMask &= ~STYPE_EBULLET;
      Hit(aDirection);
      break;

    case SPELL_STATE:
      mSprite->vx = 0;
      mSprite->vy = 0;
      mStep = 0;
      mSprite->cMask &= ~STYPE_EBULLET;
      Spell(aDirection);
      break;

    case DEATH_STATE: {
      //      Death(aDirection);
      auto *p = new GEnemyDeathOverlayProcess(mGameState, mSprite->x + 16, mSprite->y);
      mEnemyDeathOverlayProcess = p;
      mGameState->AddProcess(p);
    } break;

    default:
      break;
  }
}

void GEnemyProcess::Spell(DIRECTION aDirection) {
  auto *p = new GSpellOverlayProcess(mGameState, mSprite->x, mSprite->y);
  mSpellOverlayProcess = p;
  mGameState->AddProcess(p);
  Hit(mSprite->mDirection);
}

TBool GEnemyProcess::MaybeHit() {
  if (mSprite->TestCType(STYPE_SPELL)) {
    mSprite->ClearCType(STYPE_SPELL);
    if (!mSprite->mInvulnerable) {
      mSprite->mInvulnerable = ETrue;
      // TODO take into account which spellbook is being wielded
      TInt hitAmount = GPlayer::mHitStrength + round(RandomFloat() * GPlayer::mHitStrength / 2);
      mSprite->mHitPoints -= hitAmount;
      auto *p = new GStatProcess(mSprite->x + 68, mSprite->y + 32, "%d", hitAmount);
      p->SetMessageType(STAT_ENEMY_HIT);
      mGameState->AddProcess(p);
      if (mSprite->mHitPoints <= 0) {
        auto *p = new GStatProcess(mSprite->x + 72, mSprite->y, "EXP +%d", mSprite->mExperience);
        p->SetMessageType(STAT_EXPERIENCE);
        mGameState->AddProcess(p);
      }
      NewState(SPELL_STATE, mSprite->mDirection);
      return ETrue;
    }
  }

  GAnchorSprite *other = mSprite->mCollided;
  if (mSprite->TestCType(STYPE_PBULLET)) {
    mSprite->ClearCType(STYPE_PBULLET);
    if (!mSprite->mInvulnerable) {
      mSprite->Nudge(); // move sprite so it's not on top of player
      mSprite->mInvulnerable = ETrue;
      // random variation from 100% to 150% base damage
      TInt hitAmount = GPlayer::mHitStrength + round(RandomFloat() * GPlayer::mHitStrength / 2);
      mSprite->mHitPoints -= hitAmount;
      auto *p = new GStatProcess(mSprite->x + 68, mSprite->y + 32, "%d", hitAmount);
      p->SetMessageType(STAT_ENEMY_HIT);
      mGameState->AddProcess(p);
      if (mSprite->mHitPoints <= 0) {
        auto *p = new GStatProcess(mSprite->x + 72, mSprite->y, "EXP +%d", mSprite->mExperience);
        p->SetMessageType(STAT_EXPERIENCE);
        mGameState->AddProcess(p);
      }
      switch (other->mDirection) {
        case DIRECTION_RIGHT:
          NewState(HIT_STATE, DIRECTION_LEFT);
          break;
        case DIRECTION_LEFT:
          NewState(HIT_STATE, DIRECTION_RIGHT);
          break;
        case DIRECTION_UP:
          NewState(HIT_STATE, DIRECTION_DOWN);
          break;
        case DIRECTION_DOWN:
          NewState(HIT_STATE, DIRECTION_UP);
          break;
      }
      return ETrue;
    }
  }

  if (mSprite->TestCType(STYPE_PLAYER)) {
    mSprite->ClearCType(STYPE_PLAYER);
    mSprite->Nudge();
    NewState(IDLE_STATE, mSprite->mDirection);
    return EFalse;
  }

  return EFalse;
}

static const TInt DX = 8,
  DY = 8;

TBool GEnemyProcess::MaybeAttack() {
  TRect myRect, hisRect;
  mSprite->GetRect(myRect);
  mPlayerSprite->GetRect(hisRect);

  if (!mPlayerSprite->mInvulnerable) {
    if (myRect.y1 <= hisRect.y2 && myRect.y2 >= hisRect.y1) {
      // vertical overlap
      if (myRect.x1 >= hisRect.x2 && myRect.x1 - hisRect.x2 < DX) {
        // to right of player
        if (--mAttackTimer <= 0) {
          NewState(ATTACK_STATE, DIRECTION_LEFT);
        }
        return ETrue;
      }
      if (myRect.x2 <= hisRect.x1 && hisRect.x1 - myRect.x2 < DX) {
        // to left of player
        if (--mAttackTimer <= 0) {
          NewState(ATTACK_STATE, DIRECTION_RIGHT);
        }
        return ETrue;
      }
    } else if (myRect.x1 <= hisRect.x2 && myRect.x2 >= hisRect.x1) {
      // horizontal overlap
      if (myRect.y1 >= hisRect.y2 && myRect.y1 - hisRect.y2 < DY) {
        // below player
        if (--mAttackTimer <= 0) {
          NewState(ATTACK_STATE, DIRECTION_UP);
        }
        return ETrue;
      }
      if (myRect.y2 <= hisRect.y1 && hisRect.y1 - myRect.y2 < DY) {
        // above player
        if (--mAttackTimer <= 0) {
          NewState(ATTACK_STATE, DIRECTION_DOWN);
        }
        return ETrue;
      }
    }

    // player not near us
    mAttackTimer = 1;
    return EFalse;
  }
  else {
    //    printf("Player Invulnerable\n");
  }

  return EFalse;
}

TBool GEnemyProcess::AttackState() {
  if (mSprite->AnimDone()) {
    NewState(IDLE_STATE, mSprite->mDirection);
  }
  return ETrue;
}

TBool GEnemyProcess::HitState() {
  if (mSprite->AnimDone()) {
    if (mSprite->mHitPoints <= 0) {
      NewState(DEATH_STATE, mSprite->mDirection);
      return ETrue;
    }
    mSprite->mInvulnerable = EFalse;
    mSprite->ClearCType(STYPE_PBULLET);
    NewState(IDLE_STATE, mSprite->mDirection);
  }
  return ETrue;
}

TBool GEnemyProcess::SpellState() {
  auto *p = mSpellOverlayProcess;
  if (!p) {
    return ETrue;
  }
  GAnchorSprite *s = mSpellOverlayProcess->GetSprite();
  if (mSprite->AnimDone() && s && s->AnimDone()) {
    if (mSprite->mHitPoints <= 0) {
      mSpellOverlayProcess = ENull;
      NewState(DEATH_STATE, mSprite->mDirection);
      return ETrue;
    }

    mSprite->mInvulnerable = EFalse;
    mSprite->ClearCType(STYPE_PBULLET);
    NewState(IDLE_STATE, mSprite->mDirection);
  }
  return ETrue;
}

TBool GEnemyProcess::DeathState() {
  if (mSprite->AnimDone()) {
    GAnchorSprite *s = mEnemyDeathOverlayProcess->GetSprite();
    if (s) {
      if (s->AnimDone()) {
        GPlayer::AddExperience(mSprite->mExperience);
        // drop a potion
        switch (Random(0, 3)) {
          case 0:
            GItemProcess::SpawnItem(mGameState, -1, ITEM_BLUE_POTION1, mSprite->x + 16, mSprite->y);
            break;
          case 1:
            GItemProcess::SpawnItem(mGameState, -1, ITEM_BLUE_POTION2, mSprite->x + 16, mSprite->y);
            break;
          case 2:
            GItemProcess::SpawnItem(mGameState, -1, ITEM_RED_POTION1, mSprite->x + 16, mSprite->y);
            break;
          case 3:
            GItemProcess::SpawnItem(mGameState, -1, ITEM_RED_POTION2, mSprite->x + 16, mSprite->y);
            break;
        }
        return EFalse;
      }
      else {
        return ETrue;
      }
    }
  }

  return ETrue;
}

TBool GEnemyProcess::IdleState() {
  if (MaybeHit()) {
    return ETrue;
  }

  if (MaybeAttack()) {
    return ETrue;
  }

  if (--mStateTimer < 0) {
    // Set distance to walk for WALK_STATE
    for (TInt retries = 0; retries < 8; retries++) {
      DIRECTION direction = GAnchorSprite::RandomDirection();
      TFloat vx = direction == DIRECTION_LEFT ? -mVelocity : mVelocity,
             vy = direction == DIRECTION_UP ? -mVelocity : mVelocity;

      if (CanWalk(direction, vx, vy)) {
        NewState(WALK_STATE, direction);
        return ETrue;
      }
    }

    // after 8 tries, we couldn't find a direction to walk.
    NewState(IDLE_STATE, mSprite->mDirection);
  }

  return ETrue;
}

TBool GEnemyProcess::WalkState() {
  if (MaybeAttack()) {
    return ETrue;
  }

  if (MaybeHit()) {
    return ETrue;
  }

  mAttackTimer = 1;

  if (--mStateTimer < 0) {
    NewState(IDLE_STATE, mSprite->mDirection);
    return ETrue;
  }

  if (!CanWalk(mSprite->mDirection, mSprite->vx, mSprite->vy)) {
    NewState(IDLE_STATE, mSprite->mDirection);
    return ETrue;
  }

  if (mSprite->AnimDone()) {
    // done with left/right step, start animation for the other foot
    NewState(WALK_STATE, mSprite->mDirection);
  }

  return ETrue;
}

TBool GEnemyProcess::RunBefore() {
  if (mSprite->Clipped()) {
    NewState(IDLE_STATE, mSprite->mDirection);
    return ETrue;
  }
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
    case SPELL_STATE:
      return SpellState();
    default:
      return ETrue;
  }
}

TBool GEnemyProcess::RunAfter() {
  mSprite->ClearCType(STYPE_PLAYER);

  return ETrue;
}

void GEnemyProcess::WriteToStream(BMemoryStream &aStream) {
  aStream.Write(&mIp, sizeof(mIp));
  aStream.Write(&mParams, sizeof(mParams));
  aStream.Write(&mStartX, sizeof(mStartX));
  aStream.Write(&mStartY, sizeof(mStartY));
  aStream.Write(&mState, sizeof(mState));
  aStream.Write(&mDirection, sizeof(mDirection));
  aStream.Write(&mStep, sizeof(mStep));
  aStream.Write(&mAttackTimer, sizeof(mAttackTimer));
  aStream.Write(&mStateTimer, sizeof(mStateTimer));
  aStream.Write(&mHitPoints, sizeof(mHitPoints));
  aStream.Write(&mVelocity, sizeof(mVelocity));
  mSprite->WriteToStream(aStream);
}

void GEnemyProcess::ReadFromStream(BMemoryStream &aStream) {
  aStream.Read(&mIp, sizeof(mIp));
  aStream.Read(&mParams, sizeof(mParams));
  aStream.Read(&mStartX, sizeof(mStartX));
  aStream.Read(&mStartY, sizeof(mStartY));
  aStream.Read(&mState, sizeof(mState));
  aStream.Read(&mDirection, sizeof(mDirection));
  aStream.Read(&mStep, sizeof(mStep));
  aStream.Read(&mAttackTimer, sizeof(mAttackTimer));
  aStream.Read(&mStateTimer, sizeof(mStateTimer));
  aStream.Read(&mHitPoints, sizeof(mHitPoints));
  aStream.Read(&mVelocity, sizeof(mVelocity));
  mSprite->ReadFromStream(aStream);
}

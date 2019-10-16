/**
 * GPlayer
 *
 * Contains player info like experience, strength, gold, inventory, etc.
 */
#ifndef MODITE_GPLAYER_H
#define MODITE_GPLAYER_H

#include "Game.h"
#include "inventory/GItemProcess.h"
#include "GPlayerProcess.h"
#include "GPlayer.h"

struct GInventoryItem : public BNode {
  GInventoryItem(TInt aItemNumber);

  TInt mItemNumber;
  TInt mImage;
  TInt mCount;

  void Render();
};

struct GInventoryList : public BList {
  GInventoryList();

  void AddItem(GInventoryItem *aItem) {
    AddHead(*aItem);
  }

  void RemoveItem(GInventoryItem *aItem) {
    aItem->Remove();
  }

  void DropItem(GInventoryItem *aItem);

  void PickupItem(TInt aItemNumber);

  GInventoryItem *First() {
    return (GInventoryItem *)BList::First();
  }

  TBool End(GInventoryItem *item) {
    return BList::End((BNode *)item);
  }

  GInventoryItem *Next(GInventoryItem *item) {
    return (GInventoryItem *)BList::Next((BNode *)item);
  }

  void Dump();
};

struct GEquipped {
  GInventoryItem *mAmulet,
      *mRing,
      *mGloves,
      *mBoots,
      *mWeapon,
      *mSpellbook;
};

struct GPlayer {
  static void Init() {
    printf("Construct GPlayer\n");
    mLevel = 1;
    mNextLevel = 10;
    mExperience = 0;
    mMaxHitPoints = 20;
    mHitPoints = mMaxHitPoints;
    mStrength = 10;
    mDexterity = 10;
    mHitStrength = 1;
    mHealthPotion = mManaPotion = 100;
    mGold = 0;
    //
    mEquipped.mAmulet = ENull;
    mEquipped.mRing = ENull;
    mEquipped.mGloves = ENull;
    mEquipped.mBoots = ENull;
    mEquipped.mWeapon = ENull;
    mEquipped.mSpellbook = ENull;
  }

  static void AddExperience(TInt aExperience) {
    mExperience += aExperience;
    if (mExperience >= mNextLevel) {
      mLevel++;
      mExperience -= mNextLevel;
      mNextLevel += mLevel * 2;
      mMaxHitPoints += 2;
      mHitPoints = mMaxHitPoints;
      mHitStrength++;
    }
  }

  static TInt16 mLevel, mNextLevel, mExperience;
  static TInt16 mHitPoints, mMaxHitPoints;
  static TInt16 mStrength, mDexterity;
  static TInt mHitStrength;
  static TInt mHealthPotion, mManaPotion;   // 100, 75, 50, 25, 0 are possible values
  static TInt mGold;
  static GInventoryList mInventoryList;
  static GPlayerProcess *mProcess;
  static GAnchorSprite *mSprite;
  static GGameState *mGameState;
  static GEquipped mEquipped;
};

#endif //MODITE_GPLAYER_H

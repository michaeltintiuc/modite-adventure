#ifndef GENUS_TOPTIONS_H
#define GENUS_TOPTIONS_H

#include "BTypes.h"
#include "BStore.h"
#include "Panic.h"

struct GameProgress {
  TBool          savedState;
  TInt           level;

  GameProgress() {
    savedState = EFalse;
    level = 1;
  }
};

struct TOptions {
  static constexpr TInt RUMBLE_MAX = 8;

  TInt   version;
  TBool  muted;
  TFloat music;
  TFloat sfx;
  TFloat brightness;
  GameProgress gameProgress;
  TInt rumble;

  TOptions();

  void SetDefaults();
  void Reset(TBool aSave = ETrue);
  void ResetGameProgress();
  void Save();
  void Load();
};

#endif

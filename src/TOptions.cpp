#include "TOptions.h"
#include <cstddef>

// bump this each time the struct is edited in IDE/debugger!
static const TInt VERSION = 2;
static constexpr TInt DEFAULT_RUMBLE = 4;

TOptions::TOptions() {
  Load();
}

void TOptions::SetDefaults() {
  version = VERSION;
  muted = EFalse;
  music = 0.5f;
  sfx = 0.5f;
  brightness = 0.875f;
  rumble = DEFAULT_RUMBLE;

  ResetGameProgress();
}

void TOptions::Reset(TBool aSave) {
  SetDefaults();

  if (aSave) {
    Save();
  }
}

void TOptions::ResetGameProgress() {
  gameProgress = GameProgress();
}

void TOptions::Save() {
  version = VERSION;
  BStore f("ModiteAdventure");
  f.Set("options", this, sizeof(TOptions));
}

void TOptions::Load() {
  BStore f("ModiteAdventure");
  if (f.Get("options", this, sizeof(TOptions)) && version == VERSION) {
    if (rumble < 0 || rumble > RUMBLE_MAX) {
      rumble = DEFAULT_RUMBLE;
    }
    return;
  }

  // Version 1 stored the same fields up to the newly appended rumble setting.
  if (f.Get("options", this, offsetof(TOptions, rumble)) && version == 1) {
    rumble = DEFAULT_RUMBLE;
    Save();
    return;
  }

  Reset();
}

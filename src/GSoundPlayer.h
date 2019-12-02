//
// Created by Jesus Garcia on 10/2/18.
//
#ifndef GSOUNDPLAYER_H
#define GSOUNDPLAYER_H

#include "BSoundPlayer.h"

#include "Resources.h"


class GSoundPlayer : public BSoundPlayer {


public:
  void Init(TUint8 aNumberFxChannels);

  TBool LoadSongSlot(TInt16 aResourceId) override;
  TBool LoadEffects() override;
  BRaw* LoadEffectResource(TUint16 aResourceId, TInt16 aSlotNumber) override;
  TBool PlayMusic(TInt16 aResourceId);

  // SFX Methods //

  void SfxSaveGame();
  void SfxStartGame();
  void SfxMenuNavDown();
  void SfxMenuNavUp();
  void SfxMenuIn();
  void SfxMenuOut();

  void SfxOptionSelect();

  // SFX PLAYER //

  void SfxPlayerSlash();
  void SfxPlayerQuaffHealthPotion();
  void SfxPlayerQuaffWaterSpell();
  void SfxPlayerQuaffEarthSpell();
  void SfxPlayerQuaffFireSpell();
  void SfxPlayerQuaffEnergySpell();
  void SfxPlayerTakeDamage();

  // SFX Enemy (general)
  void SfxEnemyDeath();
  void SfxEnemyTakeDamage();

  // SFX Playfield
  void SfxPlayfieldSpikeRaise();
};


extern GSoundPlayer gSoundPlayer;

#endif //GSOUNDPLAYER_H

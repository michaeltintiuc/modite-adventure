#ifndef MODITE_GRESOURCES_H
#define MODITE_GRESOURCES_H

#include <BTypes.h>
#include "Resources.h"

enum {
  FONT_8x8_SLOT,
  FONT_16x16_SLOT,
  BKG_SLOT,
  PLAYER_SLOT,
  TILESET_SLOT,
  ENVIRONMENT_SLOT,
  // enemies
  PROJECTILE_ARROW_SLOT,
  BAT_SLOT,
  GOBLIN_SLOT,
  GOBLIN_SNIPER_SLOT,
  ORC_SLOT,
  RAT_SLOT,
  SLIME_SLOT,
  SPIDER_SLOT,
  TROLL_SLOT,
  SLOT_MAX,
};

// BRaw slots
enum {
  SONG0_SLOT,
  SONG1_SLOT,
  SONG2_SLOT,
  SONG3_SLOT,
  SONG4_SLOT,
  SONG5_SLOT,
  SONG6_SLOT,
  SONG7_SLOT,
  SONG8_SLOT,
  SONG9_SLOT,
  SONG10_SLOT,
  SONG11_SLOT,
  SFX1_SLOT,
  SFX2_SLOT,
  SFX3_SLOT,
  SFX4_SLOT,
  SFX5_SLOT,
  SFX6_SLOT,
  SFX7_SLOT,
  SFX8_SLOT,
  SFX9_SLOT,
  SFX10_SLOT,
  SFX11_SLOT,
  SFX12_SLOT,
  SFX13_SLOT,
  SFX14_SLOT,
};

// SPLASH_SPRITES.BMP
const TUint16 IMG_DROP1 = 0;
const TUint16 IMG_DROP2 = 4;
const TUint16 IMG_DROP3 = 8;
const TUint16 IMG_DROP4 = 16;
const TUint16 IMG_DROP5 = 24;
const TUint16 IMG_DROP6 = 32;

// PLAYER.BMP
const TUint16 IMG_IDLE         = 0;
const TUint16 IMG_SELECTED     = 4;
const TUint16 IMG_WALK_DOWN    = 8;
const TUint16 IMG_WALK_RIGHT   = 12;
const TUint16 IMG_WALK_UP      = 16;
const TUint16 IMG_SWORD_DOWN   = 20;
const TUint16 IMG_SWORD_RIGHT  = 24;
const TUint16 IMG_SWORD_UP     = 28;
const TUint16 IMG_DAMAGE_DOWN  = 32;
const TUint16 IMG_DAMAGE_RIGHT = 36;
const TUint16 IMG_DAMAGE_UP    = 40;

// CHARA_SPIDER_BMP
const TUint16 IMG_SPIDER_IDLE         = 0;
const TUint16 IMG_SPIDER_SELECTED     = 4;
const TUint16 IMG_SPIDER_WALK_DOWN    = 8;
const TUint16 IMG_SPIDER_WALK_RIGHT   = 12;
const TUint16 IMG_SPIDER_WALK_UP      = 16;
const TUint16 IMG_SPIDER_ATTACK_DOWN  = 20;
const TUint16 IMG_SPIDER_ATTACK_RIGHT = 24;
const TUint16 IMG_SPIDER_ATTACK_UP    = 28;
const TUint16 IMG_SPIDER_DAMAGE_DOWN  = 32;
const TUint16 IMG_SPIDER_DAMAGE_RIGHT = 36;
const TUint16 IMG_SPIDER_DAMAGE_UP    = 40;

// CHARA_BAT_BMP
const TUint16 IMG_BAT_IDLE         = 0;
const TUint16 IMG_BAT_SELECTED     = 4;
const TUint16 IMG_BAT_WALK_DOWN    = 8;
const TUint16 IMG_BAT_WALK_RIGHT   = 12;
const TUint16 IMG_BAT_WALK_UP      = 16;
const TUint16 IMG_BAT_ATTACK_DOWN  = 20;
const TUint16 IMG_BAT_ATTACK_RIGHT = 24;
const TUint16 IMG_BAT_ATTACK_UP    = 28;
const TUint16 IMG_BAT_DAMAGE_DOWN  = 32;
const TUint16 IMG_BAT_DAMAGE_RIGHT = 36;
const TUint16 IMG_BAT_DAMAGE_UP    = 40;

// CHARA_GOBLIN_BMP
const TUint16 IMG_GOBLIN_IDLE         = 0;
const TUint16 IMG_GOBLIN_SELECTED     = 4;
const TUint16 IMG_GOBLIN_WALK_DOWN    = 8;
const TUint16 IMG_GOBLIN_WALK_RIGHT   = 12;
const TUint16 IMG_GOBLIN_WALK_UP      = 16;
const TUint16 IMG_GOBLIN_ATTACK_DOWN  = 20;
const TUint16 IMG_GOBLIN_ATTACK_RIGHT = 24;
const TUint16 IMG_GOBLIN_ATTACK_UP    = 28;
const TUint16 IMG_GOBLIN_DAMAGE_DOWN  = 32;
const TUint16 IMG_GOBLIN_DAMAGE_RIGHT = 36;
const TUint16 IMG_GOBLIN_DAMAGE_UP    = 40;

// CHARA_GOBLIN_SNIPER_BMP
const TUint16 IMG_GOBLIN_SNIPER_IDLE         = 0;
const TUint16 IMG_GOBLIN_SNIPER_SELECTED     = 4;
const TUint16 IMG_GOBLIN_SNIPER_WALK_DOWN    = 8;
const TUint16 IMG_GOBLIN_SNIPER_WALK_RIGHT   = 12;
const TUint16 IMG_GOBLIN_SNIPER_WALK_UP      = 16;
const TUint16 IMG_GOBLIN_SNIPER_ATTACK_DOWN  = 20;
const TUint16 IMG_GOBLIN_SNIPER_ATTACK_RIGHT = 24;
const TUint16 IMG_GOBLIN_SNIPER_ATTACK_UP    = 28;
const TUint16 IMG_GOBLIN_SNIPER_DAMAGE_DOWN  = 32;
const TUint16 IMG_GOBLIN_SNIPER_DAMAGE_RIGHT = 36;
const TUint16 IMG_GOBLIN_SNIPER_DAMAGE_UP    = 40;

// CHARA_ORC_BMP
const TUint16 IMG_ORC_IDLE         = 0;
const TUint16 IMG_ORC_SELECTED     = 4;
const TUint16 IMG_ORC_WALK_DOWN    = 8;
const TUint16 IMG_ORC_WALK_RIGHT   = 12;
const TUint16 IMG_ORC_WALK_UP      = 16;
const TUint16 IMG_ORC_ATTACK_DOWN  = 20;
const TUint16 IMG_ORC_ATTACK_RIGHT = 24;
const TUint16 IMG_ORC_ATTACK_UP    = 28;
const TUint16 IMG_ORC_DAMAGE_DOWN  = 32;
const TUint16 IMG_ORC_DAMAGE_RIGHT = 36;
const TUint16 IMG_ORC_DAMAGE_UP    = 40;

// CHARA_RAT_BMP
const TUint16 IMG_RAT_IDLE         = 0;
const TUint16 IMG_RAT_SELECTED     = 4;
const TUint16 IMG_RAT_WALK_DOWN    = 8;
const TUint16 IMG_RAT_WALK_RIGHT   = 12;
const TUint16 IMG_RAT_WALK_UP      = 16;
const TUint16 IMG_RAT_ATTACK_DOWN  = 20;
const TUint16 IMG_RAT_ATTACK_RIGHT = 24;
const TUint16 IMG_RAT_ATTACK_UP    = 28;
const TUint16 IMG_RAT_DAMAGE_DOWN  = 32;
const TUint16 IMG_RAT_DAMAGE_RIGHT = 36;
const TUint16 IMG_RAT_DAMAGE_UP    = 40;

// CHARA_SLIME_BMP
const TUint16 IMG_SLIME_IDLE         = 0;
const TUint16 IMG_SLIME_SELECTED     = 4;
const TUint16 IMG_SLIME_WALK_DOWN    = 8;
const TUint16 IMG_SLIME_WALK_RIGHT   = 12;
const TUint16 IMG_SLIME_WALK_UP      = 16;
const TUint16 IMG_SLIME_ATTACK_DOWN  = 20;
const TUint16 IMG_SLIME_ATTACK_RIGHT = 24;
const TUint16 IMG_SLIME_ATTACK_UP    = 28;
const TUint16 IMG_SLIME_DAMAGE_DOWN  = 32;
const TUint16 IMG_SLIME_DAMAGE_RIGHT = 36;
const TUint16 IMG_SLIME_DAMAGE_UP    = 40;

// CHARA_TROLL_BMP
const TUint16 IMG_TROLL_IDLE         = 0;
const TUint16 IMG_TROLL_SELECTED     = 4;
const TUint16 IMG_TROLL_WALK_DOWN    = 8;
const TUint16 IMG_TROLL_WALK_RIGHT   = 12;
const TUint16 IMG_TROLL_WALK_UP      = 16;
const TUint16 IMG_TROLL_ATTACK_DOWN  = 20;
const TUint16 IMG_TROLL_ATTACK_RIGHT = 24;
const TUint16 IMG_TROLL_ATTACK_UP    = 28;
const TUint16 IMG_TROLL_DAMAGE_DOWN  = 32;
const TUint16 IMG_TROLL_DAMAGE_RIGHT = 36;
const TUint16 IMG_TROLL_DAMAGE_UP    = 40;

// DUNGEON_TILESET_OBJECTS_BMP
const TUint16 IMG_WOOD_DOOR_H       = 10;
const TUint16 IMG_METAL_DOOR_H      = 11;
const TUint16 IMG_POT               = 12;      // through 14
const TUint16 IMG_SPIKES            = 15;      // through 19
const TUint16 IMG_CHEST             = 22;      // closed, open is 23
const TUint16 IMG_CRATE             = 24;      // through 28
const TUint16 IMG_WOOD_DOOR_V       = 30;      // top, bottom is 30
const TUint16 IMG_METAL_DOOR_V      = 31;      // top, bottom is 31
const TUint16 IMG_FLOOR_SWITCH      = 32;      // grey, 33 is pressed
const TUint16 IMG_FLOOR_SWITCH_WOOD = 34;      // brown, 35 is pressed
const TUint16 IMG_LEVER             = 36;      // left, center = 36, right = 37
const TUint16 IMG_STONE_STAIRS_DOWN = 48;
const TUint16 IMG_STONE_STAIRS_UP   = 49;      // 39 is the upper sprite image for the very top stairs
const TUint16 IMG_WOOD_STAIRS_DOWN  = 68;
const TUint16 IMG_WOOD_STAIRS_UP    = 69;      // 59 is the upper sprite image for the very top stairs
const TUint16 IMG_BLUE_SPELLBOOK    = 80;
const TUint16 IMG_RED_SPELLBOOK     = 81;
const TUint16 IMG_GREEN_SPELLBOOK   = 82;
const TUint16 IMG_YELLOW_SPELLBOOK  = 83;
const TUint16 IMG_SILVER_KEY        = 85;
const TUint16 IMG_GOLD_KEY          = 86;
const TUint16 IMG_BLUE_RING         = 90;
const TUint16 IMG_RED_RING          = 91;
const TUint16 IMG_GREEN_RING        = 92;
const TUint16 IMG_YELLOW_RING       = 93;
const TUint16 IMG_BOOTS             = 94;
const TUint16 IMG_GLOVES            = 95;
const TUint16 IMG_SWORD             = 96;
const TUint16 IMG_BLUE_AMULET       = 100;
const TUint16 IMG_RED_AMULET        = 101;
const TUint16 IMG_GREEN_AMULET      = 102;
const TUint16 IMG_YELLOW_AMULET     = 103;
const TUint16 IMG_GREEN_POTION1     = 110;
const TUint16 IMG_GREEN_POTION2     = 111;
const TUint16 IMG_BLUE_POTION1      = 112;
const TUint16 IMG_BLUE_POTION2      = 113;
const TUint16 IMAGE_EMPTY_BOTTLE    = 114;      // EMPTY
const TUint16 IMG_BLUE_BOTTLE1      = 120;      // 25% full
const TUint16 IMG_BLUE_BOTTLE2      = 121;      // 50% full
const TUint16 IMG_BLUE_BOTTLE3      = 122;      // 75% full
const TUint16 IMG_BLUE_BOTTLE4      = 123;      // 100% full
const TUint16 IMG_GREEN_BOTTLE1     = 124;      // 25% full
const TUint16 IMG_GREEN_BOTTLE2     = 125;      // 50% full
const TUint16 IMG_GREEN_BOTTLE3     = 126;      // 75% full
const TUint16 IMG_GREEN_BOTTLE4     = 127;      // 100% full


//// RESERVED COLORS
const TUint8 COLOR_SHMOO       = 252;
const TUint8 COLOR_TEXT_SHADOW = 253;
const TUint8 COLOR_TEXT_BG     = 254;
const TUint8 COLOR_TEXT        = 255;

#define MAX_BBITMAP 5

#endif //MODITE_GRESOURCES_H

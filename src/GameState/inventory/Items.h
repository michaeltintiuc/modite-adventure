#ifndef MODITE_ITEMS_H
#define MODITE_ITEMS_H

#include "GGamePlayfield.h"
#include "GResources.h"

const TUint16 ITEM_EMPTY = ATTR_EMPTY;
const TUint16 ITEM_BLUE_SPELLBOOK = ATTR_BLUE_SPELLBOOK;
const TUint16 ITEM_RED_SPELLBOOK = ATTR_RED_SPELLBOOK;
const TUint16 ITEM_GREEN_SPELLBOOK = ATTR_GREEN_SPELLBOOK;
const TUint16 ITEM_YELLOW_SPELLBOOK = ATTR_YELLOW_SPELLBOOK;
const TUint16 ITEM_SLIVER_KEY = ATTR_SILVER_KEY;
const TUint16 ITEM_GOLD_KEY = ATTR_GOLD_KEY;
const TUint16 ITEM_BLUE_RING = ATTR_BLUE_RING;
const TUint16 ITEM_RED_RING = ATTR_RED_RING;
const TUint16 ITEM_GREEN_RING = ATTR_GREEN_RING;
const TUint16 ITEM_YELLOW_RING = ATTR_YELLOW_RING;
const TUint16 ITEM_BOOTS = ATTR_BOOTS;
const TUint16 ITEM_GLOVES = ATTR_GLOVES;
const TUint16 ITEM_SWORD = ATTR_SWORD;
const TUint16 ITEM_BLUE_BRACELET = ATTR_BLUE_BRACELET;
const TUint16 ITEM_RED_BRACELET = ATTR_RED_BRACELET;
const TUint16 ITEM_GREEN_BRACELET = ATTR_GREEN_BRACELET;
const TUint16 ITEM_YELLOW_BRACELET = ATTR_YELLOW_BRACELET;
const TUint16 ITEM_RED_POTION1 = ATTR_RED_POTION1;
const TUint16 ITEM_RED_POTION2 = ATTR_RED_POTION2;
const TUint16 ITEM_BLUE_POTION1 = ATTR_BLUE_POTION1;
const TUint16 ITEM_BLUE_POTION2 = ATTR_BLUE_POTION2;
const TUint16 ITEM_EMPTY_BOTTLE = ATTR_EMPTY_BOTTLE;    // empty bottle
const TUint16 ITEM_BLUE_BOTTLE1 = ATTR_BLUE_BOTTLE1;   // 25% full
const TUint16 ITEM_BLUE_BOTTLE2 = ATTR_BLUE_BOTTLE2;   // 50% full
const TUint16 ITEM_BLUE_BOTTLE3 = ATTR_BLUE_BOTTLE3;   // 75% full
const TUint16 ITEM_BLUE_BOTTLE4 = ATTR_BLUE_BOTTLE4;   // 100% full
const TUint16 ITEM_RED_BOTTLE1 = ATTR_RED_BOTTLE1; // 25% full
const TUint16 ITEM_RED_BOTTLE2 = ATTR_RED_BOTTLE2; // 50% full
const TUint16 ITEM_RED_BOTTLE3 = ATTR_RED_BOTTLE3; // 75% full
const TUint16 ITEM_RED_BOTTLE4 = ATTR_RED_BOTTLE4; // 100% full

static const TInt items[] = {
  0, // 0 = no item
  IMG_BLUE_SPELLBOOK,
  IMG_RED_SPELLBOOK,
  IMG_GREEN_SPELLBOOK,
  IMG_YELLOW_SPELLBOOK,
  IMG_SILVER_KEY,
  IMG_GOLD_KEY,
  IMG_BLUE_RING,
  IMG_RED_RING,
  IMG_GREEN_RING,
  IMG_YELLOW_RING,
  IMG_BOOTS,
  IMG_GLOVES,
  IMG_SWORD,
  IMG_BLUE_BRACELET,
  IMG_RED_BRACELET,
  IMG_GREEN_BRACELET,
  IMG_YELLOW_BRACELET,
  IMG_GREEN_POTION1,
  IMG_GREEN_POTION2,
  IMG_BLUE_POTION1,
  IMG_BLUE_POTION2,
  IMAGE_EMPTY_BOTTLE,
  IMG_BLUE_BOTTLE1,
  IMG_BLUE_BOTTLE2,
  IMG_BLUE_BOTTLE3,
  IMG_BLUE_BOTTLE4,
  IMG_GREEN_BOTTLE1,
  IMG_GREEN_BOTTLE2,
  IMG_GREEN_BOTTLE3,
  IMG_GREEN_BOTTLE4,
};

static const char *itemNames[] = {
  "INVALID ITEM",
  "Water Spellbook",
  "Red Spellbook",
  "Green Spellbook",
  "Yellow Spellbook",
  "Silver Key",
  "Gold Key",
  "Blue Ring",
  "Red Ring",
  "Green Ring",
  "Yellow Ring",
  "Boots",
  "Gloves",
  "Sword",
  "Blue Amulet",
  "Red Amulet",
  "Green Amulet",
  "Yellow Amulet",
  "Small Red Potion",
  "Big Red Potion",
  "Small Blue Potion",
  "Big Blue Potion",
  "Empty Bottle",
  "Blue Bottle 25%",
  "Blue Bottle 50%",
  "Blue Bottle 75%",
  "Blue Bottle Full",
  "Red Bottle 25%",
  "Red Bottle 50%",
  "Red Bottle 75%",
  "Red Bottle Full",
};

#endif //MODITE_ITEMS_H

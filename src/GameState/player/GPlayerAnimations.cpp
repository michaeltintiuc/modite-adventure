#include "Game.h"
#include "GPlayerAnimations.h"

const TInt16 HITSPEED_FIRST = TInt(1.5 * HITSPEED);

/*
 __  __             _        ____             _ _  
|  \/  | __ _  __ _(_) ___  / ___| _ __   ___| | | 
| |\/| |/ _` |/ _` | |/ __| \___ \| '_ \ / _ \ | | 
| |  | | (_| | (_| | | (__   ___) | |_) |  __/ | | 
|_|  |_|\__,_|\__, |_|\___| |____/| .__/ \___|_|_| 
              |___/               |_|              
*/

const TInt16 SPELL_SPEED = 3;

ANIMSCRIPT spell1Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(SPELL_SPEED, IMG_IDLE + 0),
  ASTEP(SPELL_SPEED, IMG_IDLE + 1),
  ASTEP(SPELL_SPEED, IMG_IDLE + 2),
  ASTEP(SPELL_SPEED, IMG_IDLE + 5),
  ASTEP(SPELL_SPEED, IMG_IDLE + 6),
  AEND,
};

ANIMSCRIPT spell2Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(SPELL_SPEED, IMG_IDLE + 2),
  ASTEP(SPELL_SPEED, IMG_IDLE + 1),
  ASTEP(SPELL_SPEED, IMG_IDLE + 0),
  ASTEP(SPELL_SPEED, IMG_IDLE + 8),
  ASTEP(SPELL_SPEED, IMG_IDLE + 0),
  AEND,
};

ANIMSCRIPT spellOverlayAnimation[] = {
  ABITMAP(PLAYER_SPELL_SLOT),
  ASTEP(SPELL_SPEED, IMG_SPELL + 0),
  ASTEP(SPELL_SPEED, IMG_SPELL + 1),
  ASTEP(SPELL_SPEED, IMG_SPELL + 2),
  ASTEP(SPELL_SPEED, IMG_SPELL + 3),
  ASTEP(SPELL_SPEED, IMG_SPELL + 4),
  ASTEP(SPELL_SPEED, IMG_SPELL + 5),
  ASTEP(SPELL_SPEED, IMG_SPELL + 6),
  ASTEP(SPELL_SPEED, IMG_SPELL + 7),
  ASTEP(SPELL_SPEED, IMG_SPELL + 8),
  AEND,
};

/*
 ____       _       _      ____       _   _              
|  _ \ _ __(_)_ __ | | __ |  _ \ ___ | |_(_) ___  _ __   
| | | | '__| | '_ \| |/ / | |_) / _ \| __| |/ _ \| '_ \  
| |_| | |  | | | | |   <  |  __/ (_) | |_| | (_) | | | | 
|____/|_|  |_|_| |_|_|\_\ |_|   \___/ \__|_|\___/|_| |_| 
*/

const TInt16 QUAFF_SPEED = 3;

ANIMSCRIPT quaff1Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 0),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 1),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 2),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 5),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 6),
  AEND,
};

ANIMSCRIPT quaff2Animation[] = {
  ABITMAP(PLAYER_SLOT),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 2),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 1),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 0),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 8),
  ASTEP(QUAFF_SPEED, IMG_IDLE + 0),
  AEND,
};

ANIMSCRIPT quaffOverlayAnimation[] = {
  ABITMAP(PLAYER_HEAL_SLOT),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 0),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 1),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 2),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 3),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 4),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 5),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 6),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 7),
  ASTEP(QUAFF_SPEED, IMG_HEAL + 8),
  AEND,
};

/*
 ___    _ _         ______       _           _           _
|_ _|__| | | ___   / / ___|  ___| | ___  ___| |_ ___  __| |
 | |/ _` | |/ _ \ / /\___ \ / _ \ |/ _ \/ __| __/ _ \/ _` |
 | | (_| | |  __// /  ___) |  __/ |  __/ (__| ||  __/ (_| |
|___\__,_|_|\___/_/  |____/ \___|_|\___|\___|\__\___|\__,_|
 */
ANIMSCRIPT idleAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ALABEL,
  ASTEP(40, IMG_IDLE),
  ASTEP(4, IMG_IDLE + 1),
  ASTEP(40, IMG_IDLE + 2),
  ASTEP(4, IMG_IDLE + 1),
  ALOOP,
};

ANIMSCRIPT selectedAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ALABEL,
  ASTEP(40, IMG_SELECTED),
  ASTEP(4, IMG_SELECTED + 1),
  ASTEP(40, IMG_SELECTED + 2),
  ASTEP(4, IMG_SELECTED + 1),
  ALOOP,
};

ANIMSCRIPT fallAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  ALABEL,
  ADELTA(1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 1),
  ALOOP,
};

ANIMSCRIPT landAnimation[] = {
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  ADELTA(0, -2),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  AEND,
};
/*
 ____
|  _ \  _____      ___ __
| | | |/ _ \ \ /\ / / '_ \
| |_| | (_) \ V  V /| | | |
|____/ \___/ \_/\_/ |_| |_|
*/

ANIMSCRIPT idleDownAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(4, -2),
  ASTEP(1, IMG_WALK_DOWN),
  AEND,
};
//
//ANIMSCRIPT walkDownAnimation1[] = {
//  ABITMAP(PLAYER_SLOT),
////  ADELTA(2, -2),
////  ASTEP(WALKSPEED, IMG_WALK_DOWN + 3),
//  ADELTA(1, 0),
//  ASTEP(WALKSPEED, IMG_WALK_DOWN + 2),
//  ADELTA(4, 0),
//  ASTEP(WALKSPEED, IMG_WALK_DOWN + 0),
//  AEND,
//};
//
//ANIMSCRIPT walkDownAnimation2[] = {
//  ABITMAP(PLAYER_SLOT),
//  ADELTA(1, 0),
//  ASTEP(WALKSPEED, IMG_WALK_DOWN + 2),
//  ADELTA(5, 0),
//  ASTEP(WALKSPEED, IMG_WALK_DOWN + 1),
//  ADELTA(1, 0),
//  ASTEP(WALKSPEED, IMG_WALK_DOWN + 3),
////  ADELTA(4, -2),
////  ASTEP(WALKSPEED, IMG_WALK_DOWN + 0),
//  AEND,
//};


ANIMSCRIPT walkDownAnimation1[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, 0),
  ASTEP(WALKSPEED, IMG_WALK_DOWN + 3),
  ADELTA(4, -1),
  ASTEP(WALKSPEED, IMG_WALK_DOWN + 0),
  ADELTA(1, 1),
  ASTEP(WALKSPEED, IMG_WALK_DOWN + 2),
  AEND,
};

ANIMSCRIPT walkDownAnimation2[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(5, 0),
  ASTEP(WALKSPEED, IMG_WALK_DOWN + 1),
  ADELTA(1, 1),
  ASTEP(WALKSPEED, IMG_WALK_DOWN + 2),
  ADELTA(4, -1),
  ASTEP(WALKSPEED, IMG_WALK_DOWN + 0),
//    ADELTA(1, 0),
//    ASTEP(WALKSPEED, IMG_WALK_DOWN + 3),
//  ADELTA(4, -2),
//  ASTEP(WALKSPEED, IMG_WALK_DOWN + 0),
  AEND,
};

ANIMSCRIPT swordChargeDownAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -2),
  ASTEP(WALKSPEED * 4, IMG_SWORD_DOWN),
  ADELTA(2, -2),
  ASTEP(WALKSPEED * 2, IMG_SWORD_DOWN + 26),
  AEND,
};

ANIMSCRIPT swordDownAnimationNoGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, 20),
  ASTEP(SWORDSPEED, IMG_SWORD_DOWN + 1),
  ADELTA(2, 20),
  ASTEP(SWORDSPEED, IMG_SWORD_DOWN + 2),
  ADELTA(2, 5),
  ASTEP(SWORDSPEED, IMG_SWORD_DOWN + 3),
  AEND,
};
ANIMSCRIPT swordDownAnimationWithGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, 20),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_DOWN + 1),
  ADELTA(2, 20),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_DOWN + 2),
  ADELTA(2, 5),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_DOWN + 3),
  AEND,
};

ANIMSCRIPT hitLightDownAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -6),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_DOWN + 3),
  ADELTA(2, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 0),
  ADELTA(0, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 1),
  ADELTA(-1, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  ADELTA(2, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 3),
  AEND
};

ANIMSCRIPT hitMediumDownAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -6),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_DOWN + 3),
  ADELTA(2, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 0),
  ADELTA(0, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 1),
  ADELTA(-1, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  ADELTA(0, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 1),
  ADELTA(-1, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  ADELTA(2, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 3),
  AEND
};

ANIMSCRIPT hitHardDownAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -6),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_DOWN + 3),
  ADELTA(2, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 0),
  ADELTA(0, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 1),
  ADELTA(-1, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  ADELTA(0, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 1),
  ADELTA(-1, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 2),
  ADELTA(2, -6),
  ASTEP(HITSPEED, IMG_DAMAGE_DOWN + 3),
  AEND
};

/*
 _          __ _
| |    ___ / _| |_
| |   / _ \ |_| __|
| |__|  __/  _| |_
|_____\___|_|  \__|

 */
ANIMSCRIPT idleLeftAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-12, -4),
  AFLIP(1, IMG_WALK_RIGHT),
  AEND,
};

ANIMSCRIPT walkLeftAnimation1[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-8, -5),
  AFLIP(WALKSPEED, IMG_WALK_RIGHT + 1),
  ADELTA(-10, -4),
  AFLIP(WALKSPEED, IMG_WALK_RIGHT + 0),
  ADELTA(-8, -4),
  AFLIP(WALKSPEED, IMG_WALK_RIGHT + 2),
  AEND,
};

ANIMSCRIPT walkLeftAnimation2[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-6, -5),
  AFLIP(WALKSPEED, IMG_WALK_RIGHT + 3),
  ADELTA(-10, -4),
  AFLIP(WALKSPEED, IMG_WALK_RIGHT + 0),
  AEND,
};


ANIMSCRIPT swordChargeLeftAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -4),
  AFLIP(WALKSPEED * 4, IMG_SWORD_RIGHT + 20),
  ADELTA(2, -4),
  AFLIP(WALKSPEED * 2, IMG_SWORD_RIGHT),
  AEND,
};


ANIMSCRIPT swordLeftAnimationNoGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-23, -3),
  AFLIP(SWORDSPEED, IMG_SWORD_RIGHT + 1),
  ADELTA(-23, -3),
  AFLIP(SWORDSPEED, IMG_SWORD_RIGHT + 2),
  ADELTA(-12, -3),
  AFLIP(SWORDSPEED, IMG_SWORD_RIGHT + 3),
  AEND,
};

ANIMSCRIPT swordLeftAnimationWithGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-23, -3),
  AFLIP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_RIGHT + 1),
  ADELTA(-23, -3),
  AFLIP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_RIGHT + 2),
  ADELTA(-12, -3),
  AFLIP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_RIGHT + 3),
  AEND,
};

ANIMSCRIPT hitLightLeftAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-4, -4),
  AFLIP(HITSPEED_FIRST, IMG_DAMAGE_RIGHT + 3),
  ADELTA(0, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 0),
  ADELTA(2, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 3),
  AEND
};

ANIMSCRIPT hitMediumLeftAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-4, -4),
  AFLIP(HITSPEED_FIRST, IMG_DAMAGE_RIGHT + 3),
  ADELTA(0, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 0),
  ADELTA(2, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(2, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 3),
  AEND
};

ANIMSCRIPT hitHardLeftAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-4, -4),
  AFLIP(HITSPEED_FIRST, IMG_DAMAGE_RIGHT + 3),
  ADELTA(0, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 0),
  ADELTA(2, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(2, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(-4, -4),
  AFLIP(HITSPEED, IMG_DAMAGE_RIGHT + 3),
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
ANIMSCRIPT idleRightAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-2, -4),
  ASTEP(1, IMG_WALK_RIGHT),
  AEND,
};

ANIMSCRIPT walkRightAnimation1[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -5),
  ASTEP(WALKSPEED, IMG_WALK_RIGHT + 1),
  ADELTA(0, -4),
  ASTEP(WALKSPEED, IMG_WALK_RIGHT + 0),
  ADELTA(4, -4),
  ASTEP(WALKSPEED, IMG_WALK_RIGHT + 2),
  AEND,
};

ANIMSCRIPT walkRightAnimation2[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(0, -5),
  ASTEP(WALKSPEED, IMG_WALK_RIGHT + 3),
  ADELTA(-2, -4),
  ASTEP(WALKSPEED, IMG_WALK_RIGHT),
  AEND,
};

ANIMSCRIPT swordChargeRightAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(0, -4),
  ASTEP(WALKSPEED * 4, IMG_SWORD_RIGHT + 20),
  ADELTA(0, -4),
  ASTEP(WALKSPEED * 2, IMG_SWORD_RIGHT),
  AEND,
};

ANIMSCRIPT swordRightAnimationNoGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(13, -3),
  ASTEP(SWORDSPEED, IMG_SWORD_RIGHT + 1),
  ADELTA(13, -3),
  ASTEP(SWORDSPEED, IMG_SWORD_RIGHT + 2),
  ADELTA(4, -3),
  ASTEP(SWORDSPEED, IMG_SWORD_RIGHT + 3),
  AEND,
};

ANIMSCRIPT swordRightAnimationWithGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(13, -3),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_RIGHT + 1),
  ADELTA(13, -3),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_RIGHT + 2),
  ADELTA(4, -3),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_RIGHT + 3),
  AEND,
};

ANIMSCRIPT hitLightRightAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -4),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_RIGHT + 3),
  ADELTA(4, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 0),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 3),
  AEND
};

ANIMSCRIPT hitMediumRightAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -4),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_RIGHT + 3),
  ADELTA(4, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 0),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 3),
  AEND
};

ANIMSCRIPT hitHardRightAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -4),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_RIGHT + 3),
  ADELTA(4, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 0),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 1),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 2),
  ADELTA(2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_RIGHT + 3),
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
ANIMSCRIPT idleUpAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(0, -4),
  ASTEP(1, IMG_WALK_UP + 0),
  AEND,
};

ANIMSCRIPT walkUpAnimation1[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-2, -4),
  ASTEP(WALKSPEED, IMG_WALK_UP + 1),
  ADELTA(-1, -4),
  ASTEP(WALKSPEED, IMG_WALK_UP + 3),
  AEND,
};

ANIMSCRIPT walkUpAnimation2[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(-7, -4),
  ASTEP(WALKSPEED, IMG_WALK_UP + 2),
  ADELTA(0, -4),
  ASTEP(WALKSPEED, IMG_WALK_UP + 0),
//  ADELTA(-7, -4),
//  ASTEP(WALKSPEED, IMG_WALK_UP + 2),
  AEND,
};

ANIMSCRIPT swordChargeUpAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(4, -4),
  ASTEP(WALKSPEED * 2, IMG_SWORD_UP),
  ADELTA(4, -4),
  ASTEP(WALKSPEED * 4, IMG_SWORD_UP + 17),
  AEND,
};

ANIMSCRIPT swordUpAnimationNoGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -6),
  ASTEP(SWORDSPEED, IMG_SWORD_UP + 1),
  ADELTA(4, -6),
  ASTEP(SWORDSPEED, IMG_SWORD_UP + 2),
  ADELTA(-2, -6),
  ASTEP(SWORDSPEED, IMG_SWORD_UP + 3),
  AEND,
};

ANIMSCRIPT swordUpAnimationWithGloves[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(2, -6),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_UP + 1),
  ADELTA(4, -6),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_UP + 2),
  ADELTA(-2, -6),
  ASTEP(SWORDSPEED_WITH_GLOVE, IMG_SWORD_UP + 3),
  AEND,
};

ANIMSCRIPT hitLightUpAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(1, -4),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_UP + 3),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 0),
  ADELTA(-2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 1),
  ADELTA(-1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 2),
  ADELTA(1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 3),
  AEND
};

ANIMSCRIPT hitMediumUpAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(1, -4),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_UP + 3),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 0),
  ADELTA(-2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 1),
  ADELTA(-1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 2),
  ADELTA(-2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 1),
  ADELTA(-1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 2),
  ADELTA(1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 3),
  AEND
};

ANIMSCRIPT hitHardUpAnimation[] = {
  ABITMAP(PLAYER_SLOT),
  ADELTA(1, -4),
  ASTEP(HITSPEED_FIRST, IMG_DAMAGE_UP + 3),
  ADELTA(0, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 0),
  ADELTA(-2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 1),
  ADELTA(-1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 2),
  ADELTA(-2, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 1),
  ADELTA(-1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 2),
  ADELTA(1, -4),
  ASTEP(HITSPEED, IMG_DAMAGE_UP + 3),
  AEND
};

ANIMSCRIPT* idleAnimations[] = {idleUpAnimation, idleDownAnimation, idleLeftAnimation, idleRightAnimation};
ANIMSCRIPT* walkAnimations1[] = {walkUpAnimation1, walkDownAnimation1, walkLeftAnimation1, walkRightAnimation1};
ANIMSCRIPT* walkAnimations2[] = {walkUpAnimation2, walkDownAnimation2, walkLeftAnimation2, walkRightAnimation2};
ANIMSCRIPT* swordAnimationsNoGloves[] = {
  swordUpAnimationNoGloves,
  swordDownAnimationNoGloves,
  swordLeftAnimationNoGloves,
  swordRightAnimationNoGloves,
};
ANIMSCRIPT* swordAnimationsWithGloves[] = {
  swordUpAnimationWithGloves,
  swordDownAnimationWithGloves,
  swordLeftAnimationWithGloves,
  swordRightAnimationWithGloves,
};
ANIMSCRIPT* hitLightAnimations[] = {hitLightUpAnimation, hitLightDownAnimation, hitLightLeftAnimation, hitLightRightAnimation};
ANIMSCRIPT* hitMediumAnimations[] = {hitMediumUpAnimation, hitMediumDownAnimation, hitMediumLeftAnimation, hitMediumRightAnimation};
ANIMSCRIPT* hitHardAnimations[] = {hitHardUpAnimation, hitHardDownAnimation, hitHardLeftAnimation, hitHardRightAnimation};

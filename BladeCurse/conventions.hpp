#ifndef _CONVENTIONS_H
#define _CONVENTIONS_H

#include <cmath>
#include <math.h>

#define PlayerMoveSpeed 3
#define DEG_TO_RAD(angle) (angle * M_PI/ 180)
#define RAD_TO_DEG(angle) (angle * 180/M_PI)
#define CONVENTIONAL_PLAYER_DIRECTION 1 
#define DIRECTIONAL_LENGTH 60 
#define CONVENTIONAL_ANGLE 0
#define ROTATION_SPEED 0.000009 // Very precise Constant given by many over 100 experiments(tukka)
#define FRICTIONAL_CONSTANT_ROUGH 1.7
#define IMAGECUTOFFCONSTANT 65
#define CLOSE_COMBAT_BOSS_DAMAGE 2
#define PLAYER_HEALTH 10
#define CLOSE_COMBAT_BOSS_HEALTH 100
#define RANGED_BOSS_DAMAGE 4 
#define RANGED_BOSS_HEALTH 60
#define PLAYER_DAMAGE_BASIC 5
#define SCREENWIDTH 1200

#define SCREENHEIGHT 600
#define SCENE_INDEX 1

#endif
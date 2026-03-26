#ifndef _CLOSE_BOSS_H
#define _CLOSE_BOSS_H

#include "Boss.hpp"

class CloseBoss : public Boss{

public :
    CloseBoss(Vector pos, Vector dimensions) {
        SetPos(pos);
        SetDimensions(dimensions);
    }

    void Init(SDL_Renderer *renderer,const char *path){
        damage = CLOSE_COMBAT_BOSS_DAMAGE;
        health = CLOSE_COMBAT_BOSS_HEALTH;
        
        LoadTexture(path,renderer);

    }

    

};

#endif
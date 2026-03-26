#ifndef _BOSS_H
#define _BOSS_H

#include "Player.hpp"
#include <SDL_image.h>
class Boss{

public:
    Vector pos,dimensions;
    int type; // 1 for close combat boss , 2 for spawner(coming soon) ,3 for ranged boss
    SDL_Rect Body_Rect; 
    SDL_Texture *texture;
    int health;
    int damage; 

    Boss() = default;

    Boss(Vector pos, Vector dimensions,int type) : pos(pos) , dimensions(dimensions){}

    void SetPos(Vector position) { pos = position; }
    Vector& GetPos() { return pos; }
    void SetDimensions(Vector d) { dimensions = d; }
    int getType() {return type; }
    void LoadTexture(const char* path,SDL_Renderer *renderer){ texture = IMG_LoadTexture(renderer,path); }

    int DrawSelf(SDL_Renderer *renderer){
        SDL_Rect rect;
        rect.x = static_cast<int>(pos.Get_X());
        rect.y = static_cast<int>(pos.Get_Y());
        rect.w = static_cast<int>(dimensions.Get_X());
        rect.h = static_cast<int>(dimensions.Get_Y());

        return SDL_RenderCopy(renderer,texture,NULL,&rect);
    }

    void GetCollider(){
        Body_Rect.x = static_cast<int>(pos.Get_X());
        Body_Rect.y = static_cast<int>(pos.Get_Y());
        Body_Rect.w = static_cast<int>(dimensions.Get_X());
        Body_Rect.h = static_cast<int>(dimensions.Get_Y());
    }

    void Update(SDL_Renderer *renderer){
        DrawSelf(renderer);
        GetCollider();
    }
    void TakeDamage(int damage){
        health -= damage;
        if(health <= 0){
            Die();
        }
    }
    void Die(){
        // Add Animation , dialogues 
    }

};

#endif
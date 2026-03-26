#ifndef _NPC_H
#define _NPC_H

#include "Player.hpp"
#include <SDL_image.h>

class NPC {
private:
    Vector Position, Dimensions;
    SDL_Texture *Npc_image = nullptr; // Initialize to nullptr
    SDL_Rect Body_Rect;

public:
    NPC(Vector Position, Vector Dimensions) 
        : Position(Position), Dimensions(Dimensions) {}

    ~NPC() {
        if (Npc_image) {
            SDL_DestroyTexture(Npc_image); // Free texture memory
        }
    }

    void LoadImage(const char *path, SDL_Renderer* renderer) {
        Npc_image = IMG_LoadTexture(renderer, path);
        if (!Npc_image) {
            SDL_Log("Failed to load NPC image: %s", IMG_GetError());
        }
    }

    int DrawSelf(SDL_Renderer *renderer) {
        SDL_Rect rect;
        rect.x = static_cast<int>(Position.Get_X());
        rect.y = static_cast<int>(Position.Get_Y());
        rect.w = static_cast<int>(Dimensions.Get_X());
        rect.h = static_cast<int>(Dimensions.Get_Y());

        return SDL_RenderCopy(renderer, Npc_image, NULL, &rect);
    }

    void Update(SDL_Renderer *renderer) {
        Body_Rect.x = Position.Int_X();
        Body_Rect.y = Position.Int_Y();
        Body_Rect.w = Dimensions.Int_X();
        Body_Rect.h = Dimensions.Int_Y();

        DrawSelf(renderer);
    }

    void DrawCollider(SDL_Renderer *renderer) {
        SDL_RenderDrawRect(renderer, &Body_Rect);
    }

    SDL_Rect& GetRect()  {
        return Body_Rect;
    }

    void SetPosition(Vector pos) { 
        Position = pos; 
    }

    SDL_Texture *getTexture(){
        return Npc_image;
    }
};

#endif

#ifndef _SCENE_HPP
#define _SCENE_HPP

#include "Player.hpp"
#include "MapLoader.hpp"


class Scene{

private:
    int current_index;
public:
    // id(1) = main map , (2) == boss 
    Scene(int id) : current_index(id) {} 

    void Load_Scene(Loader &Loader,MapReader &reader,SDL_Renderer *renderer){
        reader.Draw(renderer,Loader);

    }

};

#endif
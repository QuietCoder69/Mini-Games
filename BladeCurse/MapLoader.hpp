#ifndef _MAPLOADER_H
#define _MAPLOADER_H

#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include "Vector.hpp"
#include "conventions.hpp"
#include "Player.hpp"
class Loader {
private:
    std::map<int, SDL_Texture*> textures; // Map of texture ID to texture pointer
    Vector tileSize;

public:
    Loader(Vector tileSize)
        : tileSize(tileSize) {}

    // Load a texture and store it in the map with a unique ID
    bool LoadTexture(SDL_Renderer* renderer, int id, const char* filePath) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
        if (!texture) {
            std::cerr << "Failed to load texture " << filePath << ": " << SDL_GetError() << std::endl;
            return false;
        }
        textures[id] = texture;
        return true;
    }
    Vector& getTileSize() {return tileSize;}

    // Draw a specific texture at the given position (x, y) using the texture ID
    void Load_Single_Image(SDL_Renderer* renderer, int textureID, int x, int y) {
        if (textures.find(textureID) == textures.end()) {
            std::cerr << "Texture ID " << textureID << " not found!" << std::endl;
            return;
        }

        SDL_Rect rect;
        rect.x = x * tileSize.Get_X(); // Convert tile grid position to pixel position
        rect.y = y * tileSize.Get_Y();
        rect.h = static_cast<int>(tileSize.Get_Y());
        rect.w = static_cast<int>(tileSize.Get_X());
        

        SDL_RenderCopy(renderer, textures[textureID], NULL, &rect);
    }


    // Clean up textures
    ~Loader() {
        for (auto& pair : textures) {
            SDL_DestroyTexture(pair.second);
        }
    }
};





class MapReader{
private:
    std::vector<std::vector<int>> map; 
    int width;
    int height;
    int max;

     // ha ye class reader class h chal chodd , hindi mein padhle woh sunegi ok, whytatt?ttttttttttttt sahi me ????? sunegi kya,fierst mein sun rhi thi , abhi bhi sunegi bhai,sst wale period me karenge , abwe last peroid ok? ok 

public:
    enum Type_Collidable{
        TREE = 0,
        ROCK,
        HOUSE,
        FENCE,
    };
    MapReader(const std::string& filename, int _max) {
        LoadMap(filename);
        max = _max;
    }

    void LoadMap(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            for (char& ch : line) {
                row.push_back(ch - '0'); // Convert char to int
            }
            map.push_back(row);
        }

        height = map.size();
        width = !map.empty() ? map[0].size() : 0;
        file.close();
    }

    void Draw(SDL_Renderer* renderer, Loader& loader) {
        
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                SDL_Rect rect = {x * loader.getTileSize().Int_X() , y * loader.getTileSize().Int_Y(), loader.getTileSize().Int_X(), loader.getTileSize().Int_Y()};
                int type = map[y][x];
                if (TileExists(type)) {
                    loader.Load_Single_Image(renderer,type, x, y); // Pass x and y for positioning
                }
            }
        }
    }
    bool TileExists(int tileType) {
        // Check if the tile type is valid
        return tileType >= 0 && tileType < max; // Assuming `totalTiles` is the maximum number of tiles.
    }

     
};

 
#endif
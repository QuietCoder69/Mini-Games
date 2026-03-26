#ifndef _ANIMATIONS_H
#define _ANIMATIONS_H

#include "Player.hpp"
#include <vector>
class Animation{

private:
    std::vector<SDL_Texture* > frames; // Array of frames for each animation
    int currentFrame = 0;// the current no. of frame being displayed
    int frameDelay = 0;// delay b/w each frame
    int frameCounter = 0;

public:
    Animation() = default;
    Animation(int frameDelay) : frameDelay(frameDelay) {}

    // Must be called after initialization
    void AddFrame(SDL_Texture* texture) { 
        frames.push_back(texture);
    }

    SDL_Texture* GetCurrentFrame() {
        return frames.empty() ? nullptr : frames[currentFrame];
    }

    void RemoveFrame(int index){
        frames[index] = NULL;
    }

    void Remove_All(){
        frames.clear();
        frames.shrink_to_fit();
    }

    void Update() {
        frameCounter++;
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            currentFrame = (currentFrame + 1) % frames.size();  // Loop to start of frames
        }
    }

    void Reset() {
        currentFrame = 0;
        frameCounter = 0;
    } 
};


#endif
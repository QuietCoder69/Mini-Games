#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Vector.hpp"
#include <SDL.h>
#include "conventions.hpp"
#include "Animations.hpp"
#include <map>
#include "NPC.hpp"
#include "MapLoader.hpp"


class Player{

private:
    SDL_Texture *self_image; // image of player
    Vector position; // position of player
    Vector dimensions; // dimensions of player ( height, width )
    Vector Velocity_mag; // Magnitude ofr velocities X -> x , Y -> y
    int direction; // direction of Player .. MUST BE CALCULATED USING FORMULA DURING MOVEMENT ONLY GIVES THE
    std::map < std::string , Animation> Animations; // map of Animations of each category ( run, idle,jump etc.)
    std::string current_animation; // name of the current animation being displayed
    Uint32 lastKeyPressTime = 0; // Track when the key was last pressed
    Uint32 keyCooldown = 5;    // Cooldown duration in milliseconds
    SDL_Rect Body_Rect;
    std::vector<SDL_Texture *> dialogs;
    int currentDialog = 0;
    bool showdialog = false;
    float player_angle = 0; // initialize to 0
    bool invisible = false;

public : 
     
    Player(SDL_Texture* text, Vector pos, Vector dimensions, Vector Velocity , int direction) : position(pos) , dimensions(dimensions) , self_image(text) ,Velocity_mag(Velocity) , direction(direction)
    {
        
    }
    void AddDialog(SDL_Renderer *renderer,const char* path){
        dialogs.push_back(IMG_LoadTexture(renderer,path));
    }
    void setAngle(float angle){player_angle = angle;}
    float GetAngle(){return player_angle;}

    // Adds a animation to the main Animation Map
    void AddAnimation(const std::string& name, Animation animation){
        Animations[name] = animation;
    }
    // sets the currrent animation to the provided string name
    void SetAnimation(const std::string& name){
         if (current_animation != name && Animations.count(name)) {
            current_animation = name;
            Animations[current_animation].Reset();  // Reset animation on switch
        }
    }

    void UpdateAnimations() {
        if (Animations.find(current_animation) != Animations.end()) {
            Animations[current_animation].Update();
        }
    }

    // Only For Forward And Backward Movements 
    void Move(float angle,int d){
        // checking for angle if it is negative or pi-periodic
        float a = RAD_TO_DEG(angle);
        
        position.Set_X(position.Get_X() + (sinf(a) * Velocity_mag.Get_X() * d)); // d stands for the direction if 1 then forward
        position.Set_Y(position.Get_Y() - (cosf(a) * Velocity_mag.Get_Y() * d)); // if negative then backwards
    }
    
    void Move(int dx){
        
        position.Set_X(position.Get_X() +( Velocity_mag.Get_X() *dx)); // if movement is towards left dx = (-)ve
        
    }

    void Update(SDL_Renderer *renderer,NPC &jack){
            if(!invisible){DrawSelf(renderer);
            UpdateAnimations();
            UpdateBodyRect();
            DrawCollider(renderer);
            Collision();
            if(dialogs.empty()){
                CheckForDialogs(jack);
            }
        }
        
    }
    void Invisible(bool _t){
        invisible = _t;
    }
    
    void CheckForDialogs(NPC &npc){
        
        npc.SetPosition(Vector(SCREENWIDTH - 80, 60));
    }

    int DrawSelf(SDL_Renderer *renderer){

        


        SDL_Rect rect;
        rect.x = static_cast<int>(position.Get_X());
        rect.y = static_cast<int>(position.Get_Y());
        rect.h = static_cast<int>(dimensions.Get_Y());
        rect.w = static_cast<int>(dimensions.Get_X());

         // Get the current animation frame texture
        SDL_Texture* currentTexture = Animations[current_animation].GetCurrentFrame();
        int result = SDL_RenderCopy(renderer, currentTexture, NULL, &rect);

        // Update the animation frame
        Animations[current_animation].Update();

        return result;
    }
    const std::string GetCurrentAnimation() {return current_animation; }

    bool DialogsEmpty() { return dialogs.empty(); }
    
    Vector GetPos(){
        return position;
    }

    void SetPos(Vector pos){
        position.Set_X(pos.Get_X());
        position.Set_Y(pos.Get_Y());
    }

    const Vector GetDimensions(){
        return dimensions;
    }

    int DrawDirection(SDL_Renderer *renderer,float angle){
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        float x = position.Get_X() + dimensions.Get_X()/2;
        float y = position.Get_Y() + dimensions.Get_Y()/2;

        // Only reason for using sine for x intercept and cos for y intercept for y is because the sdl coordinate system is differerent than normal cartesian plane
        return SDL_RenderDrawLine(renderer,static_cast<int>(x) , static_cast<int>(y),x + sinf(RAD_TO_DEG(angle))  * DIRECTIONAL_LENGTH ,y - cosf(RAD_TO_DEG(angle))  * DIRECTIONAL_LENGTH );
    }

    bool CanProcessKey(Uint32 currentTime) {
        return (currentTime - lastKeyPressTime) > keyCooldown;
    }

    void ProcessKey(Uint32 currentTime) {
        lastKeyPressTime = currentTime;
        // Process the key press action here
    }

    void DrawCollider(SDL_Renderer *renderer){
        SDL_RenderDrawRect(renderer,&Body_Rect);
    }
     
    


    int CheckCollider(SDL_Rect &rect ,int id ){ // id = 1 (jack) , 2(coming soon)
        if( SDL_HasIntersection(&rect,&Body_Rect) != 0 &&  id == 1){
            showdialog = true;

            return 0;
        }

        if(SDL_HasIntersection(&Body_Rect,&rect) && id == 2){
            // id == 2 = bossfight
        }
        return 1;
    }

    int ShowDialog(SDL_Renderer* renderer, SDL_Texture* npc) {
    if (showdialog && currentDialog < dialogs.size()) {
        // Render dialog box
        SDL_Rect dialogRect = {400, 300, 500, 200}; // Adjust position and size as needed
        SDL_RenderCopy(renderer, dialogs[currentDialog], NULL, &dialogRect);

        // Set position for character image (NPC or Player)
        SDL_Rect placeHolder = {200, 300, 200, 200};

        // Alternate between NPC and Player image based on dialog order
        if (currentDialog % 2 == 0) {
            // Even index: NPC dialog
            SDL_RenderCopy(renderer, npc, NULL, &placeHolder);
        } else {
            // Odd index: Player dialog
            placeHolder = {0, 0, 600, 600}; // Resize and reposition as needed
            SDL_RenderCopy(renderer, self_image, NULL, &placeHolder);
            }

            return 0;
        }
        return 1;
    }

    void HandleDialogInput(SDL_Event& e) {
        if (showdialog && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
            currentDialog++;
            if (currentDialog >= dialogs.size()) {
                showdialog = false; // End dialog
                currentDialog = 0;  // Reset for future interactions
                dialogs.clear();
                dialogs.shrink_to_fit();
            }
        }
         
    }


    SDL_Rect& GetRect() { return Body_Rect; }
    


    Vector& GetVelocity() { return Velocity_mag; }
    void SetVelocity(Vector Velocity) { Velocity_mag = Velocity; }

void Reflect(const SDL_Rect &obstacle) {
    float shiftAmount = 1.0f; // Amount to push the player backward upon collision
    float angle_i = player_angle; // Current player angle

    // Determine direction vector based on the angle (for reflective movement)
    float xShift = -sinf(angle_i) * shiftAmount;
    float yShift = cosf(angle_i) * shiftAmount;

    // Check for collision
    if (SDL_HasIntersection(&Body_Rect, &obstacle)) {
        // Calculate the amount of overlap on each side of the obstacle
        int leftOverlap = (Body_Rect.x + Body_Rect.w) - obstacle.x;
        int rightOverlap = (obstacle.x + obstacle.w) - Body_Rect.x;
        int topOverlap = (Body_Rect.y + Body_Rect.h) - obstacle.y;
        int bottomOverlap = (obstacle.y + obstacle.h) - Body_Rect.y;

        // Manually determine the minimum overlap
        int minOverlap = leftOverlap;
        std::string collisionSide = "left";

        if (rightOverlap < minOverlap) {
            minOverlap = rightOverlap;
            collisionSide = "right";
        }
        if (topOverlap < minOverlap) {
            minOverlap = topOverlap;
            collisionSide = "top";
        }
        if (bottomOverlap < minOverlap) {
            minOverlap = bottomOverlap;
            collisionSide = "bottom";
        }

        // Adjust position based on the collision side
        if (collisionSide == "left") {
            // Collision from the left side of the obstacle
            SetPosX(obstacle.x + obstacle.w + shiftAmount);
        } 
        else if (collisionSide == "right") {
            // Collision from the right side of the obstacle
            SetPosX(obstacle.x - Body_Rect.w - shiftAmount);
        } 
        else if (collisionSide == "top") {
            // Collision from the top of the obstacle
            SetPosY(obstacle.y + obstacle.h + shiftAmount);
        } 
        else if (collisionSide == "bottom") {
            // Collision from the bottom of the obstacle
            SetPosY(obstacle.y - Body_Rect.h - shiftAmount);
        }

        // Update Body_Rect to the new position after collision adjustment
        UpdateBodyRect();
    }
}


void SetPosX(float x)
{
    position = Vector(x,position.Get_Y());
}
void SetPosY(float y)
{
    position = Vector(position.Get_X(),y);
}

void Collision(){
    if(position.Int_X() <= 0) position.Set_X(position.Int_X() + 1);
    if(position.Int_X() + dimensions.Int_X() >= SCREENWIDTH) position.Set_X(position.Int_X() - 1);
    if(position.Int_Y() <= 0) position.Set_Y(position.Int_Y() + 1);
    if(position.Int_Y() + dimensions.Int_Y() >= SCREENHEIGHT) position.Set_Y(position.Int_Y() - 1);

    UpdateBodyRect();
}


    void UpdateBodyRect() {
        Body_Rect.x = position.Int_X() + IMAGECUTOFFCONSTANT ;
        Body_Rect.y = position.Int_Y() + IMAGECUTOFFCONSTANT ;
        Body_Rect.w = dimensions.Int_X() - IMAGECUTOFFCONSTANT - 5 - 5 - 50;
        Body_Rect.h = dimensions.Int_Y() - IMAGECUTOFFCONSTANT - 4 - 4 - 30;
    }

};

#endif
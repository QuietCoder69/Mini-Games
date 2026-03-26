#ifndef _MISC_H
#define _MISC_H

#include "Player.hpp"
#include <SDL_image.h>
#include "Text.hpp"
#include <istream>
#include <iostream>
#include <sstream>

enum Machine_States{
    MACHINE_STATE_ACT_ONE = 0,
    MACHINE_STATE_INTERVAL,
    MACHINE_STATE_ACT_ONE_END,
    MACHINE_STATE_ACT_TWO,
};

void GetKeyInputs(Player &player,const Uint8* keystates){
    // MOVES.
            if(keystates[SDL_SCANCODE_W] && !keystates[SDL_SCANCODE_D] && !keystates[SDL_SCANCODE_A]){
                player.Move(0,1);
                player.SetAnimation("walk");
                player.setAngle(3*M_PI/2);
            }
            //MOVES.
            if(keystates[SDL_SCANCODE_S] && !keystates[SDL_SCANCODE_D] && !keystates[SDL_SCANCODE_A]){
                player.Move(0,-1);
                player.SetAnimation("walk");
                player.setAngle(M_PI/2);
            }
            if(keystates[SDL_SCANCODE_A]  ){
                player.setAngle(M_PI);
                player.Move(-1);
                player.SetAnimation("walk");
            }
            if(keystates[SDL_SCANCODE_D]  ){
                player.setAngle(2*M_PI);
                player.Move(1);
                player.SetAnimation("walk");
            }
}

void Initiate_Sword(Animation &animation, SDL_Renderer *renderer) {
    animation.Remove_All();
    SDL_Texture* frame = IMG_LoadTexture(renderer, "assets/playerImages/player-idle-sword (1).png");
    if (frame) animation.AddFrame(frame);

    frame = IMG_LoadTexture(renderer, "assets\\playerImages\\player-idle-sword (2).png");
    if (frame) animation.AddFrame(frame);

    frame = IMG_LoadTexture(renderer, "assets\\playerImages\\player-idle-sword (3).png");
    if (frame) animation.AddFrame(frame);

    frame = IMG_LoadTexture(renderer, "assets\\playerImages\\player-idle-sword (4).png");
    if (frame) animation.AddFrame(frame);
}

void Initiate_Sword_Run(Animation &animation, SDL_Renderer *renderer) {
    animation.Remove_All();
    SDL_Texture* frame = IMG_LoadTexture(renderer, "assets\\playerImages\\player-run-sword (1).png");
    if (frame) animation.AddFrame(frame);

    frame = IMG_LoadTexture(renderer, "assets\\playerImages\\player-run-sword (2).png");
    if (frame) animation.AddFrame(frame);

    frame = IMG_LoadTexture(renderer, "assets\\playerImages\\player-run-sword (3).png");
    if (frame) animation.AddFrame(frame);

    frame = IMG_LoadTexture(renderer, "assets\\playerImages\\player-run-sword (4).png");
    if (frame) animation.AddFrame(frame);
}
bool IsAnyKeyPressed() {
    const Uint8* state = SDL_GetKeyboardState(NULL); // Get the current state of the keyboard

    // Iterate through all keys; SDL_NUM_SCANCODES is defined in SDL
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        if (state[i]) { // If any key is pressed
            return true; // Return true if any key is pressed
        }
    }
    return false; // Return false if no key is pressed
}

void Init_Player_Idle(SDL_Renderer *renderer,Animation &animation){

    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-idle (1).png"));
    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-idle (2).png"));
    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-idle (3).png"));
    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-idle (4).png"));
}
void Init_Player_Walk(SDL_Renderer *renderer,Animation &animation){

    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-run (1).png"));
    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-run (3).png"));
    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-run (2).png"));
    animation.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages/player-run (4).png"));
}

int Act_One(SDL_Renderer *renderer,NPC &jack,Text &order_text,bool IscollidingIwhtJack,bool GetSword,Player &player,const Uint8* keystates, SDL_Color text_color,Animation &idle,Animation &walk){
    if(IscollidingIwhtJack && !GetSword){
                std::string current_order = "Hold 'E' , Press 'Enter' To Proceed";
                order_text.SetText(current_order,text_color);
            }
            if (IscollidingIwhtJack && keystates[SDL_SCANCODE_E] && !player.DialogsEmpty() && !GetSword) {
                player.ShowDialog(renderer,jack.getTexture());
                 
            }
            if(player.DialogsEmpty() && !GetSword){
                std::string current_order = "Walk To The Villager , Press 'F' ";
                order_text.SetText(current_order,text_color);
            }
            if (IscollidingIwhtJack && player.DialogsEmpty() && !GetSword && keystates[SDL_SCANCODE_F]) {
                Initiate_Sword(idle, renderer);
                Initiate_Sword_Run(walk, renderer);
                player.AddAnimation("idle",idle);
                player.AddAnimation("walk",walk);
                GetSword = true;
                
            }
            if(GetSword) {

                return MACHINE_STATE_ACT_ONE_END;
            }
        return MACHINE_STATE_ACT_ONE;

}

bool isBlackScreenActive = false;
Uint32 blackScreenStartTime = 0;
Uint32 blackScreenDuration = 0;

// Function to initiate the black screen effect
void StartBlackScreen(Uint32 duration,Player &player,Text &text,SDL_Color color,int &current_state) {
    isBlackScreenActive = true;
    blackScreenStartTime = SDL_GetTicks();
    blackScreenDuration = duration;

    player.SetPos(Vector(800,800));
    text.SetText(std::string(""),color);
    current_state = MACHINE_STATE_ACT_TWO;

}

// Function to render the black screen
void RenderBlackScreen(SDL_Renderer* renderer) {
    if (isBlackScreenActive) {
        Uint32 elapsedTime = SDL_GetTicks() - blackScreenStartTime;

        // If the duration has passed, stop the black screen effect
        if (elapsedTime >= blackScreenDuration) {
            isBlackScreenActive = false;
            return;
        }

        // Render the black screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

Text _timeSkip_text;
std::string _current_text;
std::vector<std::string> _text_to_display; // Holds the entire message split into words
SDL_Color color = {210, 210, 210};
Uint32 _last_update_time = 0; // Tracks the last time a word was added
int _current_word_index = 0;  // Index of the next word to display

void InitTimeSkip(SDL_Renderer *renderer) {
    std::string path = "assets/fonts/RubikBurned-Regular.ttf";
    _current_text = ""; // Initialize with empty text

    // Example text to display
    std::string full_text = ". . . . .  where am i ?";
    std::istringstream iss(full_text);
    std::string word;
    
    // Split the full text into words and store in the vector
    while (iss >> word) {
        _text_to_display.push_back(word);
    }

    _timeSkip_text = Text(path, _current_text, renderer, 40, color);
    _timeSkip_text.Load_Font(renderer,path,_current_text,40,color);
}

void SickTimeSkip(SDL_Renderer *renderer, bool &IsTextFinished) {
    Uint32 current_time = SDL_GetTicks();

    // Check if 2 seconds have passed since the last update
     static Uint32 last_update_time = 0; // Tracks the last time a word was added
    static size_t word_index = 0;      // Current index in the split_text array

    if (word_index < _text_to_display.size()) {
        // Check if it's time to add the next word
        if (current_time - last_update_time >= 1000) { // 500 ms = 0.5 seconds
            if (!_current_text.empty()) {
                _current_text += " ";
            }
            _current_text += _text_to_display[word_index];
            word_index++;
            _timeSkip_text.SetText(_current_text, color);
            last_update_time = current_time;
        }
    } else {
        // All words have been added
        IsTextFinished = true;
    }

    // Render the current text
    _timeSkip_text.Display(renderer, 50, 200);

}


#endif
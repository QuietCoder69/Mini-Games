#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Text{
private:
    SDL_Rect _text_rect;
    SDL_Texture *_text_texture = nullptr;
    TTF_Font *font = nullptr;
    SDL_Renderer *renderer = nullptr;

public:
    Text(std:: string &path,std::string &text,SDL_Renderer *renderer,int size_font,SDL_Color color) : renderer(renderer){
        
    }
    Text() = default;

    void Load_Font(SDL_Renderer *renderer,std::string &path,std::string &text,int size_font,SDL_Color color){
        font = TTF_OpenFont(path.c_str(),size_font);
        if(!font){
            std::cerr << " Error in Loading Font : " << TTF_GetError() << std::endl;
        }
        SetText(text,color);
         
    }

    void Display(SDL_Renderer *renderer,int x , int y){
        _text_rect.x = x;
        _text_rect.y = y;
        SDL_RenderCopy(renderer,_text_texture,NULL,&_text_rect);
    }

    void SetText(const std::string &text, SDL_Color color) {
        if (_text_texture) {
            SDL_DestroyTexture(_text_texture); // Destroy old texture before creating a new one
        }

        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!surface) {
            std::cerr << "Error in creating surface" << std::endl;
            return;
        }

        _text_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (_text_texture) {
            SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
        }
    }
      ~Text() {
        if (_text_texture) {
            SDL_DestroyTexture(_text_texture);
        }
        if (font) {
            TTF_CloseFont(font);
        }
    }

};
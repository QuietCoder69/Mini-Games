#include "include/raylib.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

const int screenheight = 600;
const int screenwidth = 500;

typedef struct Fruit{
    Texture text;
    Vector2 position;
    float velocity;
    bool IsCatched;

}Fruit;

float add = 0.01;
float velocity = .1f;



Fruit Init_Fruit(Fruit fruit,Texture2D banana,Texture2D apple,Texture2D orange){
    int n = GetRandomValue(1,3);
    int xpos = GetRandomValue(0,screenwidth - 64);
     

    if(n == 1){
        fruit.text = banana;
    }
    if(n==2){
        fruit.text = apple;
    }
    if(n == 3){
        fruit.text = orange;
    }
    fruit.IsCatched =  false;
    fruit.position = (Vector2){ xpos,0};
    fruit.velocity = velocity;

    return fruit;
}

int main(){
     
    InitWindow(screenwidth,screenheight,"CATCH THE FRUITS");
    Texture2D Basket = LoadTexture("Images\\basket.png");
    Rectangle Player = {screenwidth/2,screenheight - 70,Basket.width,Basket.height};
    
    Texture2D banana = LoadTexture("Images\\banana.png");
    Texture2D orange =  LoadTexture("Images\\orange.png");
    Texture2D apple = LoadTexture("Images\\apple.png");
      
     
    Fruit fruit;
    Fruit fruit2;
    Fruit fruit3;
    int Score = 0;
    
    float PlayerVelocity = .1f;
    fruit = Init_Fruit(fruit,banana,apple,orange);
    
    Texture2D background = LoadTexture("Images\\background.png");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawTexture(background,0,0,WHITE);
            
            DrawTexture(Basket,Player.x,Player.y,WHITE);
             
            if(IsKeyDown(KEY_LEFT)){
                Player.x -= PlayerVelocity;
            }
            if(IsKeyDown(KEY_RIGHT)){
                Player.x += PlayerVelocity;
            }
            if(Player.x < 0)Player.x += PlayerVelocity;
            if(Player.x > screenwidth - Player.width){
                Player.x -= PlayerVelocity;
            }
            if(!fruit.IsCatched){
                DrawTextureV(fruit.text,fruit.position,WHITE);
                fruit.position.y += fruit.velocity;
                
            
        }
         

        if(CheckCollisionRecs(Player,(Rectangle){fruit.position.x,fruit.position.y,fruit.text.width,fruit.text.height})){
            fruit.IsCatched = true;
            Score++;
            velocity += add;
            
            
        }
        if(CheckCollisionRecs(Player,(Rectangle){fruit2.position.x,fruit2.position.y,fruit2.text.width,fruit2.text.height})){
            fruit2.IsCatched = true;
            Score++;
            
        }
        if(CheckCollisionRecs(Player,(Rectangle){fruit3.position.x,fruit3.position.y,fruit3.text.width,fruit3.text.height})){
            fruit3.IsCatched = true;
            Score++;
            
        }
        
        if(fruit.IsCatched){
            fruit = Init_Fruit(fruit,banana,apple,orange);
            
        }
        if(fruit2.IsCatched){
            fruit2 = Init_Fruit(fruit2,banana,apple,orange);
            
        }
        if(fruit3.IsCatched){
            fruit3 = Init_Fruit(fruit3,banana,apple,orange);
            
        }
        DrawText(TextFormat("%d",Score),0,0,40,WHITE);

        if(fruit.position.y > screenheight){
            CloseWindow();

            
        }
            


        EndDrawing();

         

    }
    



    return 0;
}

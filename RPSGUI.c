#include"include/raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int screenwidth = 800;
const int screenheight = 600;
int ComputerScore = 0;
int MyScore = 0;
int main(void){
    char *choice;
    InitWindow(screenwidth,screenheight,"RockPaperScissors");
    Rectangle  Rock = {0 + 0,GetScreenHeight() - 300,250,300};
    Rectangle Paper = {Rock.width + 30,Rock.y,Rock.width,Rock.height};
    Rectangle Scissor = {Rock.width*2 + 60,Rock.y,Rock.width,Rock.height};
    Color Rocolor = BLUE;
    srand(time(0));
    int Rbc;
    char choices[][10] = {{"rock"},{"paper"},{"scissors"}};
    while (!WindowShouldClose())
    {

         
        Rectangle cursor = {GetMousePosition().x,GetMousePosition().y,20,20};
        BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangleRec( Rock,Rocolor);
            DrawRectangleRec(Paper,WHITE);
            DrawRectangleRec(Scissor,YELLOW);

            DrawText(TextFormat("%d",MyScore),50,180,40,WHITE);
            DrawText(TextFormat("%d",ComputerScore),GetScreenWidth()/2 + 30,180,40,WHITE);
             
            DrawText("Rock",Rock.x + 30,Rock.y + 30,20,BLACK);
            DrawText("Paper",Paper.x + 30,Paper.y + 30,20,BLACK);
            DrawText("Scissor",Scissor.x + 30,Scissor.y + 30,20,BLACK);
            if(CheckCollisionRecs( Rock,cursor)){
                DrawRectangleLinesEx(Rock,10,DARKBLUE);
                if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
                    choice = "rock";
                    Rbc = rand() % 3;
                    if(!strcmp(choices[Rbc],choice)){
                        DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                        sleep(1);
                        system("winm");
                            
                         
                
                    }
                    if(!strcmp(choices[Rbc],"scissors")){
                        DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                        system("Won");
                        MyScore ++;
                        sleep(1);
                         
                    }
                    if(!strcmp(choices[Rbc],"paper")){
                         DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                        system("Lost");
                        ComputerScore ++;
                        sleep(1);
                         
                    }

                }
            }
            if(CheckCollisionRecs( Paper,cursor)){
                DrawRectangleLinesEx(Paper,10,(Color){200,200,200,200}); 
                if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                    choice = "paper";
                    Rbc = rand() % 3;
                    if(!strcmp(choices[Rbc],choice)){
                         DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                         system("winm");
                         sleep(1);
                
                    }
                    if(!strcmp(choices[Rbc],"rock")){
                         DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                        system("Won");
                        MyScore ++;
                          
                         
                    }
                    if(!strcmp(choices[Rbc],"scissors")){
                         DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                        system("Lost");
                        ComputerScore ++;
                         sleep(1);
                         
                    }
                }
            }
            if(CheckCollisionRecs(Scissor,cursor)){
                DrawRectangleLinesEx(Scissor,10,GOLD);
                if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
                    choice = "scissors";
                      Rbc = rand() % 3;
                    if(!strcmp(choices[Rbc],choice)){
                          DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                         system("winm");
                         sleep(1);
                
                    }
                    if(!strcmp(choices[Rbc],"paper")){
                         DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                        system("Won");
                        MyScore ++;
                         sleep(1);
                         
                    }
                    if(!strcmp(choices[Rbc],"rock")){
                         DrawText(choices[Rbc],GetScreenWidth()/2, 90,50,WHITE);
                        system("Lost");
                        ComputerScore++;
                          sleep(1);
                         
                    }
                     

            } 
            }
             
             
             
            
             
            

             
        

        EndDrawing();    
    }
    

    return 0;
}

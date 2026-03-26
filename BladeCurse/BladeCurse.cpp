#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "src/conventions.hpp"
#include "src/Player.hpp"
#include "src/Vector.hpp"
#include "src/MapLoader.hpp"
#include <string>
#include "src/NPC.hpp"
#include "src/Close_Boss.hpp"
#include "src/Misc.hpp"
#include "src/Scene.hpp"
#include <SDL_ttf.h>
#include "src/Text.hpp"
 

int main(int argc, char* argv[]){
    // basic Loaders
    SDL_Window *window;
    SDL_Renderer *renderer;
    //  is baar achha likha h maine
    // comments h har jagah jo sb explain kr rhe h , asaare aja sb explain krta hu neeche aana 
    TTF_Init();
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image Error: " << IMG_GetError() << std::endl;
        return 1;
    }


    // Create window and renderer
    window = SDL_CreateWindow("Vector Space",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREENWIDTH,SCREENHEIGHT,SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED );
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");

    int logicalWidth, logicalHeight;
SDL_RenderGetLogicalSize(renderer, &logicalWidth, &logicalHeight);
std::cout << "Logical Size: " << logicalWidth << "x" << logicalHeight << std::endl;


    if(window != 0){
        std::cout << " " << SDL_GetError();
    }
    if(renderer!= 0){
        std::cout << " " << SDL_GetError();
    }
    // KeyBoard / Key Uses 
    // isko samjhaata hu , ye function   nhi dikhega images teri file main hain na toh nhi khulega ek array deta h keys ki , agar wo keys us frame me press hoti h to unki value true ho jaati h 
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    // Load player image
    // ye payer ki image h , mai run krunga to terko dikhega? run krta hu ek baar chal kr dikha ?error bta rha hain shit chal chhod
    SDL_Texture* player_image = IMG_LoadTexture(renderer, "assets/playerImages/player-idle (1).png");
    if (!player_image) {
        std::cout << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return 1;
    }
    
    // Initialize map Loader
    // yaha se shuru hoti  oi mereko ek cheez sikhA , KI MULTuiple maps load toh karlunga par har map mki waals define aur collision detection kaise karuh meri "self" made classes
    // mera bhi dimag kharab hua tha bhot isliye mainje collision add nhi kra pr bta deta hu
    //aaja Maploader file me aa
    MapReader reader = MapReader("assets/map.txt",7);
    Loader Map_Loader = Loader(Vector(40,40));
    
    
    //Load Images
    Map_Loader.LoadTexture(renderer,0,"assets/grass.png");
    Map_Loader.LoadTexture(renderer,1,"assets/yellow_grass.png");
    Map_Loader.LoadTexture(renderer,2,"assets/tree.png");
    Map_Loader.LoadTexture(renderer,3,"assets/yellow_grass_side.png");
    Map_Loader.LoadTexture(renderer,4,"assets/yellow_grass_center.png");
    Map_Loader.LoadTexture(renderer,5,"assets/house.png");
    Map_Loader.LoadTexture(renderer,6,"assets/rock.png");
    Map_Loader.LoadTexture(renderer,7,"assets/flower.png");
    

    // Initialize Animations and Animator
    Animation idle(100);
    Animation walk(200000);
    Animation idle_left(200);
    Animation walk_left(200000);

    idle_left.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages(inverted)/player-idle (1).png"));
    idle_left.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages(inverted)/player-idle (2).png"));
    idle_left.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages(inverted)/player-idle (3).png"));
    idle_left.AddFrame(IMG_LoadTexture(renderer,"assets/playerImages(inverted)/player-idle (4).png"));    
    Init_Player_Idle(renderer,idle);
    Init_Player_Walk(renderer,walk);

    // Player Initialisations                                                                  
    Player player = Player(player_image,Vector(SCREENWIDTH / 2, SCREENHEIGHT / 2),Vector(200,200), Vector(0.8,0.8), CONVENTIONAL_PLAYER_DIRECTION);
    float player_angle = CONVENTIONAL_ANGLE; // Angle of player '0' by deafult REQUIRED FOR MOVEMENT
    player.AddDialog(renderer,"assets/Dialogues/dialog1.png");
    player.AddDialog(renderer,"assets/Dialogues/dialog2.png"); // this order is really important !!!!!!!!!!!!!! dont know why, just works tho ?,
    player.AddDialog(renderer,"assets/Dialogues/dialog3.png");
    player.AddDialog(renderer,"assets/Dialogues/dialog4.png");


    //ADDING Texts
    std::string current_order = "Talk With The Villager";
    std::string path = "assets/fonts/ChelseaMarket-Regular.ttf";
    SDL_Color color = {210,210,210};
    Text order = Text(path,current_order,renderer,28,color);
    order.Load_Font(renderer,path,current_order,28,color);

    //Initiate NPC
    NPC jack = NPC(Vector(430,220),Vector(60,60));
    jack.LoadImage("assets/npc_1.png",renderer);

    // Add Animations TO Player
    player.AddAnimation("idle",idle);
    player.AddAnimation("idle_left",idle_left);
    player.AddAnimation("walk",walk);
    player.AddAnimation("walk_left",walk_left);

    player.SetAnimation("idle");

    // ADD Bosses And Init Them
    CloseBoss boss();

    //Initiate Sceneloader
    int current_scene = SCENE_INDEX ;
    Scene scene(current_scene);

    // Main Loop
    bool run = true;
    bool getSword = false;
    int current_state = Machine_States::MACHINE_STATE_ACT_ONE;
    
    while (run)
    {   
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                run = false;
            }
         player.HandleDialogInput(e);
        }
            Uint32 current_time = SDL_GetTicks();
            GetKeyInputs(player,keystates);
            SDL_RenderClear(renderer);

            // Testing For Loading Maps 
            if(current_scene == 1&& current_state == Machine_States::MACHINE_STATE_ACT_ONE) {
                scene.Load_Scene(Map_Loader,reader,renderer);
                jack.Update(renderer);
            }
            // do All drawings after this POint so it does not underlay the map

            //Act One - Getting Sword
            bool isCollidingWithJack = player.CheckCollider(jack.GetRect(),1) == 0;
            if(current_state == MACHINE_STATE_ACT_ONE){
               current_state =  Act_One(renderer,jack,order,isCollidingWithJack,getSword,player,keystates,color,idle,walk);
            }
            if(current_state == MACHINE_STATE_ACT_ONE_END){
                current_order = "&*#$????";
                order.SetText(current_order,color);
                SDL_SetRenderDrawColor(renderer,0,0,0,0);
                player.Invisible(true);
                current_state = MACHINE_STATE_INTERVAL;
            }
            static bool isTimeSkipInitialized = false;
            bool isTextFinished = false;
            if(current_state == Machine_States::MACHINE_STATE_INTERVAL){
                 

                if (!isTimeSkipInitialized) {
                    std::cout << "Initializing Time Skip..." << std::endl;
                    InitTimeSkip(renderer); // Ensure _timeSkip_text is initialized
                    isTimeSkipInitialized = true;
                }

                if(!isTextFinished)SickTimeSkip(renderer,isTextFinished); // Handle cutscene rendering
                if(isTextFinished){
                    
                    current_state = Machine_States::MACHINE_STATE_ACT_TWO;
                    
                }

            }
            // Act 2 Demonic Awakening
            if(current_state == Machine_States::MACHINE_STATE_ACT_TWO){

            }

            
            // Drawing The Player
            player.Update(renderer,jack);
            // Drawing text
            order.Display(renderer,250,10);
            player.SetAnimation("idle");
            
            // Clear Renderer for next frame
            SDL_RenderPresent(renderer);

            
        

    }
    // Free Up Memory
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

    return 0;
}

 





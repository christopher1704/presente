
#include <raylib.h>
#include <math.h>

#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width,screen_height,"Presente - the game");
    //SetTargetFPS(60);
    
    //Cargar Imagenes de los Sprites
    Image rigth_player = LoadImage("./images/playerder.png");
    Image left_player = LoadImage("./images/playerizq.png");
    Image image_minion = LoadImage("./images/minion.png");
    Image image_brute = LoadImage("./images/brute.png");
    
    //Reescalar la Imagen
    ImageResize(&rigth_player, rigth_player.width*1.5,rigth_player.height*1.5);
    ImageResize(&left_player, left_player.width*1.5,left_player.height*1.5);
    ImageResize(&image_minion, image_minion.width*0.3, image_minion.height*0.3);
    ImageResize(&image_brute, image_brute.width*0.4, image_brute.height*0.4);
    
    //Transformar sprites a texturas
    Texture2D  rigth_sprite = LoadTextureFromImage(rigth_player);
    Texture2D  left_sprite = LoadTextureFromImage(left_player);
    Texture2D  minion_sprite = LoadTextureFromImage(image_minion);
    Texture2D  brute_sprite = LoadTextureFromImage(image_brute);
    
    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);


    //Animacion de los enemigos
    Rectangle frame_brute = {0.0f, 0.0f, (float)brute_sprite.width/4, (float)brute_sprite.height};
    Rectangle frame_minion = {0.0f, 0.0f, (float)minion_sprite.width/4, (float)minion_sprite.height};
    int frame_cont_enemigo = 0;
    int frame_actual_enemigo = 0;

    //Animacion del el Jugador
    Texture2D player_sprite = rigth_sprite;
    Rectangle frame_player = {0.0f, 0.0f, (float)player_sprite.width/5, (float)player_sprite.height};
    int frame_cont_jugador = 0;
    int frame_actual_jugador = 0;



    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);

    // Main loop
    while(!WindowShouldClose()){

        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta);
	
	// Antes de dibujar hay que ver el sentido en el cual se movera y la velocidad.
	
	//Sentido
	if(IsKeyDown(KEY_A))player_sprite = left_sprite;
	if(IsKeyDown(KEY_D))player_sprite = rigth_sprite;
	
	//Velocidad
	float velocidad = (sqrt(sta->pla.ent.vx*sta->pla.ent.vx+sta->pla.ent.vy*sta->pla.ent.vy));
	frame_cont_enemigo++;
	frame_cont_jugador++;
	if(frame_cont_jugador >= (60	/velocidad)){
		frame_cont_jugador = 0;
		frame_actual_jugador++;
		if(frame_actual_jugador > 5)frame_actual_jugador = 0;
		
		frame_player.x = (float)frame_actual_jugador*(float)player_sprite.width/4;
	}
	
	
	
        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            //draw_state(lvl, sta);
            draw_state(lvl,sta,player_sprite,brute_sprite, minion_sprite, frame_player, &frame_brute, &frame_minion, &frame_actual_enemigo, &frame_cont_enemigo);
            DrawText("Presente profe!",190,200,20,LIGHTGRAY);

        EndDrawing();

    }
    
    //Quitar texturas
    UnloadTexture(rigth_sprite);
    UnloadTexture(left_sprite);
    UnloadTexture(minion_sprite);
    UnloadTexture(brute_sprite);
    UnloadTexture(player_sprite); 

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}

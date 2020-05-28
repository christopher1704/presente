#include "draw.h"

#include <raylib.h>

void draw_level(const level *lvl){
    // Draw cells, iterate, including borders outside the level
    for(int y=-1;y<=lvl->size_y;y++){
        for(int x=-1;x<=lvl->size_x;x++){
            char cell = level_get(lvl,x,y);
            // If the cell is a wall, paint it
            if(cell=='#'){
                DrawRectangle(TILE_SIZE*x,TILE_SIZE*y,TILE_SIZE,TILE_SIZE,BROWN);
            }
        }
    }
}
//void draw_state(const level *lvl, const state *sta){
void draw_state(const level *lvl,const state *sta, Texture2D player_sprite, Texture2D brute_sprite, Texture2D minion_sprite, Rectangle frame_player, Rectangle *frame_brute, Rectangle *frame_minion, int *frame_actual_enemigo, int *frame_cont_enemigo){

    // Initialize a camera to be used as drawing context
    Camera2D cam;
    // make the camera follow the player
    cam.target.x = sta->pla.ent.x;
    cam.target.y = sta->pla.ent.y;
    // make it so that the player is in the middle of the screen
    cam.offset.x = GetScreenWidth()/2.0;
    cam.offset.y = GetScreenHeight()/2.0;
    // set the camera rotation to 0
    cam.rotation = 0.0;
    // set the camera zoom to 1
    cam.zoom = 1.0;

    // Draw everything relative to the camera from now on
    BeginMode2D(cam);

    // Draw level
    draw_level(lvl);

    // Draw enemies
    for(int i=0;i<sta->n_enemies;i++){
    
        // Get a copy of the enemy entity
        entity ent = sta->enemies[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity, color depends on the enemy type
        // Se cambia el dibujar circulos para dibujar los sprites dependiendo del tipo
        
        if(sta->enemies[i].kind == MINION){
        //     DrawCircleV(vec,ent.rad,YELLOW);
        // }else{
        //     DrawCircleV(vec,ent.rad,RED);
            if (*frame_cont_enemigo >= (60/FRAME_SPEED)){
            *frame_cont_enemigo = 0;
            *frame_actual_enemigo++;
            if(*frame_actual_enemigo > 5) *frame_actual_enemigo = 0;
            frame_minion->x= (float)*frame_actual_enemigo*(float)minion_sprite.width/4;    
        }
        DrawTextureRec(minion_sprite, *frame_minion, vec , WHITE);
    }
    	else{
            if(*frame_actual_enemigo > 5) *frame_actual_enemigo = 0;
            frame_brute->x = (float)*frame_actual_enemigo*(float)brute_sprite.width/4;
            DrawTextureRec(brute_sprite, *frame_brute, vec, WHITE);
    	
    }	
    }    

    // Draw player
    {
        // Get a copy of the player's entity
        entity ent = sta->pla.ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        
        // Draw a circle with the radius of the entity
        //DrawCircleV(vec,ent.rad,BLUE);
        
        //Dibujar textura acorde a la velocidad del jugador y los frames
        DrawTextureRec(player_sprite, frame_player, vec, WHITE);
    }

    // Draw bullets
    for(int i=0;i<sta->n_bullets;i++){
        // Get a copy of the bullet entity
        entity ent = sta->bullets[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity
        DrawCircleV(vec,ent.rad,PINK);
    }

    // Stop drawing relative to the camera
    EndMode2D();
}

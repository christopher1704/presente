#ifndef DRAW_H
#define DRAW_H

#include "level.h"
#include "state.h"
#include <raylib.h>
#include <stdio.h>

#define FRAME_SPEED 8
// Draws the cells of the level in the screen
void draw_level(const level *lvl);

// Draws the whole state and the level in the screen
//void draw_state(const level *lvl, const state *sta);
void draw_state(const level *lvl,const state *sta, Texture2D player_sprite, Texture2D brute_sprite, Texture2D minion_sprite, Rectangle frame_player, Rectangle *frame_brute, Rectangle *frame_minion, int *frame_actual_enemigo, int *frame_cont_enemigo);

#endif

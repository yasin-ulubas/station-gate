#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "types.h"
#include "assets.h"

/*----------------------------------------------------------------------------------
Aufgabe von game.c/.h Spielablauf steuern, Moduel aufrufen, Live/Score/Stats steuern
Macht außerdem main.c übersichtlicher
Nutzt state als Pointer, weil game den Zustand ändern muss
-------------------------------------------------------------------------------------*/

/* Initialisiert den Spielzustand
 * player_name wird gespeichert, score/live/day auf Startzustand gesetzt
*/
void game_init(game_state_t *state, const char *player_name);

/** 
 * Führt komplette Runde aus(MAX_DAYS * VISITORS_PER_DAY)
 * Nutzt: rules (Tagesregeln), generator (Besucher), vaildator, stats, ui
 */
bool game_run(game_state_t *state, const assets_t *assets);

#endif
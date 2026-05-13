#ifndef STATS_H
#define STATS_H

#include "types.h"

/*------------------------------------------------------------------------------------------
Tracken, ob richt/falsch + Gründe zählen + am Ende anzeigen
stats_record wird im Game-Loop pro Visitor aufgerufen
-------------------------------------------------------------------------------------------*/

/*
 * Initialisiert stats
 */
void stats_init(stats_t *s);

/*
 * Ein Besucher wurde bearbeitet:
 * player_correct: war die Spielerentscheidung richtig?
 * reason: Grund, falls es falsch war und zählen der falschen Entscheidungen
 */
void stats_record(stats_t *s, bool player_correct, deny_reason_t reason);

/*
 * Ausgabe am Ende (oder für Debug).
 */
void stats_print(const stats_t *s);

#endif
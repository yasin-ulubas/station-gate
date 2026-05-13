#ifndef RULES_H
#define RULES_H

#include <stdbool.h>
#include "types.h"

/*------------------------------------------------------------------------------------------
Wir haben data/day_rules/scenario_01.txt..., also Regeln sind Presets, nicht komplett random
Auswahl des heutigen Szenarios erfolgt dann in game.c (wählt Datei -> rules_load_from_files)
-------------------------------------------------------------------------------------------*/

/*
 * Setzt rules_t auf Standartwert (falls Szenario Keys fehlen)
 */
void rules_init(rules_t *r);

/*
 * Parst EIN Szenario aus Datei (z.B. data/day_rules/scenario_01.txt) in rules_t
 * Rückgabe false bei Dateifehler
 */
bool rules_load_from_file(const char *path, rules_t *out);

/*
 * Optional: Debug-Ausgabe der Regeln
 */
void rules_debug_print(const rules_t *r);

#endif
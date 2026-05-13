#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdbool.h>
#include "types.h"
#include "assets.h"

/*--------------------------------------
Erzeugt/bautzusammen aus folgenden Daten einen Visitor: 
visitor_ascii und visitor_attributes (Ordner) + Tagesregeln
--------------------------------------*/

/*
 * Erzeugt einen zufälligen Besucher
 * Name, Origin, Items, ggf. blacklist, expiry, access level, etc
 * Optional: orientiert sich an rules (z.B. im emergency_day eher Waffen auftauchen lassen)
 */
bool generator_make_visitor(visitor_t *new_visitor, assets_t *assets, const rules_t *rules);

/*
 * Optional: Für Debug/Entwicklung - gibt Besucherattribute als Text aus
 */
void generator_debug_print_visitor(const visitor_t *v);

#endif
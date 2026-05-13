#ifndef ASSETS_H
#define ASSETS_H

#include <stdbool.h>
#include "types.h"

/*-----------------------------------------------------------------------------------
assets lädt externe Daten (z.B. Namen, Regeln, Blacklist,...) aus Textdateien
und speichert sie in assets_t
-------------------------------------------------------------------------------------*/

/* Initialisiert assets_t auf "leer", verhindern so Zufallswerte
 * Nutzen: vor assets_load
*/
void assets_init(assets_t *a);

/* Lädt alle Assets aus Data-Ordner
 * z.B. Namensliste, Originliste, Itemliste, Blacklist, ...
 * Rückgabe: true, sonst false und am besten assets_free aufrufen
*/ 
bool assets_load(assets_t *a, const char *data_dir);

/* Gibt ganzen Speicher frei, der in assets_t reserviert wurde (hoffentlich dann mit dynamischer Speicherverwaltung)
 * Nutzen: für Programmende oder wenn load fehlschlägt
*/
void assets_free(assets_t *a);

/* Hilfsfunktionen
 * Zufällige Auswahl aus visitor_attributes Ordner
 * Nutzen: visitors_generate() ruft das auf
*/
const char *assets_random_name(assets_t *assets);
const char *assets_random_origin(assets_t *assets);
const ascii_design_t *assets_random_visitor_ascii_design(const assets_t *assets);

/* Gibt ein zufälliges Item aus der Item-Textdatei zurück
*/
item_t assets_random_item(const assets_t *assets);

#endif
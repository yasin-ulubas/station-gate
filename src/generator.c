#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

#include "generator.h"
#include "assets.h"

bool generator_make_visitor(visitor_t *v, assets_t *assets, const rules_t *rules){
    //Haben wir einen Besucher und Assets?
    if (v == NULL || assets == NULL || rules == NULL) return false;

    //Zufälligen Namen und Herkunft aus Assets
    const char *name_ptr = assets_random_name(assets);
    const char *origin_ptr = assets_random_origin(assets);

    //Namen in den Besucher kopieren
    //strncpy(ziel,quelle, maximale Länge)
    strncpy(v->name, name_ptr, MAX_NAME_LEN - 1);
    v->name[MAX_NAME_LEN - 1] = '\0';

    strncpy(v->origin, origin_ptr, MAX_ORIGIN_LEN - 1);
    v->origin[MAX_ORIGIN_LEN - 1] = '\0';

    // Zeiger auf das Bild im Asset-Speicher holen
    v->face = assets_random_visitor_ascii_design(assets);

    // Zufallswerte für Zahlen
    v->access_level = 1 + (rand() % 5); // Level 1 bis 5

    //Geburtsdaten generieren
    int real_birth_year = 2050 + (rand() % 59); // Geboren zwischen 2050 und 2108

    v->birth_year_id = real_birth_year;
    v->birth_year_doc = real_birth_year;

    // 80 % haben das Dokument dabei
    v->has_required_doc = ((rand() % 100) < 95);

    // 30 Prozent Fälschung (nur sinnvoll, wenn Dokument vorhanden ist)
    if (v->has_required_doc && ((rand() % 100) < 30)) {
        v->birth_year_id = real_birth_year + (rand() % 5) + 1;
    }

    //Pass-Ablaufdatum relativ zum aktuellen Regel-Jahr 
    if (v->has_required_doc) {
        v->expiry_year = rules->current_year + (rand() % 10) - 2; 
    } else {
        v->expiry_year = 0; // Egal doc fehlt sowieso
    }

    int num_items = rand() % (MAX_ITEMS_PER_VISITOR + 1);
    v->item_count = 0;

    for( int i = 0; i < num_items; i++){
        //random item
        item_t item = assets_random_item(assets);

        //Wenn es kein "leeres" Item ist, pack es in den Koffer
        if (item.category != ITEMCAT_NONE){
            v->items[v->item_count] = item;
            v->item_count++;
        }
    }

    return true;
}

// Debug: Zeigt an welche Daten der Besucher hat
void generator_debug_print_visitor(const visitor_t *v){
    printf("===== GENERIERTER BESUCHER ====\n");
    printf("Name:   %s\n", v->name);
    printf("Land:   %s\n", v->origin);
    printf("Level:  %d\n", v->access_level);
    printf("Ablauf: %d\n", v->expiry_year);
}
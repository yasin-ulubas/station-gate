#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assets.h"
#include "config.h"

static void shuffle_list(char **list, size_t count){
    if (count <= 1) return;

    for (size_t i = 0; i < count - 1; i++){
        // Zufällige position
        size_t j = i + rand() / (RAND_MAX / (count - i) + 1);

        // Tausche Element i mit j
        char *temp = list[j];
        list[j] = list[i];
        list[i] = temp;
    }
}

// Statische Hilfsfunktion: Parsen von Items
static bool parse_item_category(const char *text, item_category_t *cat) {
    if (!text || !cat) return false;

    if (strcmp(text, "FOOD") == 0) {
        *cat = ITEMCAT_FOOD;
        return true;
    } else if (strcmp(text, "MEDICINE") == 0) {
        *cat = ITEMCAT_MEDICINE;
        return true;
    } else if (strcmp(text, "TOOL") == 0) {
        *cat = ITEMCAT_TOOL;
        return true;
    } else if (strcmp(text, "WEAPON") == 0) {
        *cat = ITEMCAT_WEAPON;
        return true;
    }

    return false;
}


//Alles auf Null setzen mithilfe Struct Pointer
void assets_init(assets_t *assets){
    if (!assets) {
        return;
    }
    assets->name_count = 0;
    assets->current_name_idx = 0;

    assets->origins = NULL;
    assets->origin_count = 0;
    assets->current_origin_idx = 0;

    assets->items = NULL;
    assets->item_count = 0;

    assets->designs = NULL; 
    assets->design_count = 0;

}

void assets_free(assets_t *assets){
    if (assets->names != NULL){
        // Erst jeden einzelnen String löschen
        for (size_t i = 0; i < assets->name_count; i++){
            free(assets->names[i]);
        }

        //Liste der Zeiger löschen
        free(assets->names);

        //Zeiger auf Null
        assets->names = NULL;
        assets->name_count = 0;
    }

    //Herkunftsorte aufräumen
    if (assets->origins != NULL){
        for(size_t i = 0; i < assets->origin_count; i++){
            free(assets->origins[i]);
        }
        
        free(assets->origins);

        assets->origins = NULL;
        assets->origin_count = 0;
    }

    // Items aufräumen
    if (assets->items != NULL) {
        free(assets->items);
        assets->items = NULL;
        assets->item_count = 0;
    }

    // Designs aufräumen
    if (assets->designs){
        for(size_t i = 0; i < assets->design_count; i++){
            for(size_t j = 0; j < assets->designs[i].line_count; j++){
                free(assets->designs[i].lines[j]);
            }
            free(assets->designs[i].lines);
        }
        free(assets->designs);
    }
}

// Items aus Textdatei laden
static bool assets_load_items(assets_t *assets, const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) return false;

    // Zählen wie viele Zeilen es gibt
    char line[256];
    size_t count = 0;

    while (fgets(line, sizeof(line), file)) {

        // Zeilenende entfernen
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Kommentare und leere Zeilen überspringen
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        // ";" als Trennzeichen
        if (!strchr(line, ';')) {
            continue;
        }

        count++;
    }

    // Wenn keine Items vorhanden, dann crasht nicht alles, aber es gibt dann halt keine Items
    if (count == 0) {
        fclose(file);
        assets->items = NULL;
        assets->item_count = 0;
        return true;
    }

    // Speicher reservieren: Array aus item_t
    item_t *items = malloc(count * sizeof(item_t));
    if (!items) {
        fclose(file);
        return false;
    }

    // Einlesen und umwandeln
    rewind(file);
    size_t idx = 0;

    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') line[len - 1] = '\0';

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        char *sep = strchr(line, ';');
        if (!sep) {
            continue;
        }

        *sep = '\0';
        char *name = line;
        char *cat_text = sep + 1;

        //Safety-Check: beide Seiten müssen Text enthalten
        if (name[0] == '\0' || cat_text[0] == '\0') {
            continue;
        }

        item_category_t cat;
        if (!parse_item_category(cat_text, &cat)) {
            //Kategorie unbekannt, Zeile ignorieren
            continue;
        }

        // Items in Array kopieren
        strncpy(items[idx].name, name, sizeof(items[idx].name) - 1);
        items[idx].name[sizeof(items[idx].name) - 1] = '\0';
        items[idx].category = cat;

        idx++;
        if (idx == count) {
            break;
        }
    }

    fclose(file);

    // Ergebnis in Assets speichern
    assets->items = items;
    assets->item_count = idx;

    // Im Fall von 0 gültigen Items, alles aufräumen
    if (assets->item_count == 0) {
        free(assets->items);
        assets->items = NULL;
    }

    return true;
}

// Hilfsfunktion
static bool load_list(const char *path, char ***out_list, size_t *out_count){
    FILE *file = fopen(path, "r");
    if (file == NULL){
        return false; // datei nicht gefunden
    }

    // Zeilen zählen
    size_t lines = 0;
    char buffer[256];

    // fgets liest bis zum nächsten Zeilenumbruch oder bis der Buffer voll ist
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        // Leere Zeilen überspringen 
        if (strlen(buffer) > 1){
            lines++;
        }
    }

    // Speicher für das Array von Zeigern reservieren
    // Wir brauchen Platz für 'lines' viele Zeiger (char*)
    // malloc carried
    *out_list = malloc(lines * sizeof(char *));
    if (*out_list == NULL){
        fclose(file);
        return false; // Nur wenn kein RAM mehr übrig ist
    }

    // Datei zurückspulen, um sie nochmal zu lesen
    rewind(file);

    // Strings jetzt speichern
    size_t i = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL){
        buffer[strcspn(buffer, "\n")] = 0; // String Ende

        // strdup reserviert speicher für denn String UND kopiert ihn
        // wichtig weil buffer gleich überschrieben wird
        if (strlen(buffer) > 0){
            (*out_list)[i] = strdup(buffer); // strdup oder malloc + strcpy
            i++;
        }

    }

    // Ergebnisanzal nach außen geben
    *out_count = lines;
    fclose(file); 
    return true;
}


static bool load_single_ascii_file(const char *path, ascii_design_t *design){
    if(!load_list(path, &design->lines, &design->line_count)){
        return false;
    }

    design->width = 0;
    for (size_t i = 0; i < design->line_count; i++){
        size_t len = strlen(design->lines[i]);
        if(len > design->width){
            design->width = len;
        }
    }
    return true;
}

static bool assets_load_ascii_art(assets_t *assets){
    #define MAX_ASCII_DESIGNS 20

    // Temporäres array
    ascii_design_t temp_designs[MAX_ASCII_DESIGNS];
    size_t count = 0;
    char path[256];

    // Schleife fürs Laden
    for (int i = 1; i <= MAX_ASCII_DESIGNS; i++){
        //Pfad zusammenbauen
        snprintf(path, sizeof(path), "data/visitors_ascii/visitor_ascii_%02d.txt", i);

        ascii_design_t design;

        if (!load_single_ascii_file(path, &design)){
            // Datei nicht gefunden also ende der liste
            break;
        }

        // Wenn gefunden dann ins temporäre array speichern
        temp_designs[count] = design;

        count++;
    }

    if (count == 0) return false;

    //passenden Speicher im Asset Struct reservieren
    assets->designs = malloc(count * sizeof(ascii_design_t));

    if (!assets->designs) return false;

    // Rüberkopieren
    for (size_t i = 0; i < count; i ++){
        assets->designs[i] = temp_designs[i];
    }

    assets->design_count = count;

    return true;
}



bool assets_load(assets_t *assets, const char *data_dir){
    (void)data_dir;

    // Lade Namen
    // Wir übergeben die adreses von assets->names (&...) damit die Fubnktion sie ändern kann
    if (!load_list(ASSET_PATH_NAMES, &assets->names, &assets->name_count)){
        printf("Fehler: Konnte Namen nicht laden aus %s\n", ASSET_PATH_NAMES);

        return false;
    }

    if (!load_list(ASSET_PATH_ORIGINS, &assets->origins, &assets->origin_count)) {
        assets_free(assets);

        return false;
    }

    if (!assets_load_items(assets, ASSETS_PATH_ITEMS)) {
        assets_free(assets);

        return false;
    }

    if(!assets_load_ascii_art(assets)){
        printf("Warnung: konnte keine ASCII Bilder laden!\n");

        // Wir returnen nicht false, weil sonst startet das spiel einfach ohne Bilder für Visitor
        assets->designs = NULL;
        assets->design_count = 0;
    }

    // Namen mischen und Zähler nullen
    shuffle_list(assets->names, assets->name_count);
    assets->current_name_idx = 0;

    shuffle_list(assets->origins, assets->origin_count);
    assets->current_origin_idx = 0;

    return true;
}

// Zufälligen namen holen
const char *assets_random_name(assets_t *assets){
    if (assets->name_count == 0) return "Unknown";

    //ganzer Stapel durch?
    if (assets->current_name_idx >= assets->name_count){
        // JA  -> neu mischen und von vorne
        shuffle_list(assets->names, assets->name_count);

        assets->current_name_idx = 0;
    }

    //Nimm den nächsten namen und erhöhe den Zähler
    return assets->names[assets->current_name_idx++];
}

//Zufällige Herkunft holen
const char *assets_random_origin(assets_t *assets){
if (assets->origin_count == 0) return "Unknown";

    if (assets->current_origin_idx >= assets->origin_count) {
        shuffle_list(assets->origins, assets->origin_count);

        assets->current_origin_idx = 0;
    }

    return assets->origins[assets->current_origin_idx++];
}

// Zufälliges Item holen
/* Warum Rüchgabe per Wert (item_t) und nicht als Pointer?
 * Jeder Besucher soll eigene Kopie besitzen
*/
item_t assets_random_item(const assets_t *assets) {
    item_t empty_item;
    
    memset(&empty_item, 0, sizeof(empty_item));

    // Platzhalter, kein Item vorhanden
    strncpy(empty_item.name, "None", sizeof(empty_item.name) - 1);
    empty_item.category = ITEMCAT_NONE;

    if (assets == NULL || assets->items == NULL || assets->item_count == 0) {
        return empty_item;
    }

    size_t idx = (size_t)(rand() % (int)assets->item_count);
    return assets->items[idx]; // Kopie des Items

}


//Zufälligen Pfad zu einem Bild holen
const ascii_design_t *assets_random_visitor_ascii_design(const assets_t *assets){
    // Bilder geladen?
    if(!assets || assets->design_count == 0){
        return NULL;
    }

    // zufälliger index
    int idx = rand() % assets->design_count;

    // adresse des Designs im Arbeitsspeicher
    return &assets->designs[idx];
}
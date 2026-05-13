#include "ui.h"
#include "assets.h"
#include <stdio.h>
#include <string.h>

bool ui_print_file(const char *path) {
    
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        return false;
    }

    char line[512];

    while (fgets(line, sizeof(line), file) != NULL) {
        fputs(line, stdout);
    }

    fclose(file);
    return true;
}

bool ui_read_line(char *buf, unsigned bufsize) {

    // Sicherheitscheck
    if (buf == NULL || bufsize == 0) {
        return false;
    }

    // Eingabe: 
    if (fgets(buf, bufsize, stdin) == NULL) {
        return false;
    }

    // \n am Ende entfernen
    unsigned len = strlen(buf);
    if (len > 0 && buf[len -1] == '\n') {
        buf[len - 1] = '\0';
    }

    return true;
}

static const char* get_face_line(const visitor_t *v, int line_idx){
    if(v->face != NULL && line_idx >= 0 && (size_t)line_idx < v->face->line_count){
        return v->face->lines[line_idx];
    }
    return "           "; // Leerzeichen als Platzhalter
}

static void print_passport(const visitor_t *v){
    printf("\n");
    printf(" _________________________________________________ \n");
    printf("| P A S S P O R T               | FOTO            |\n");
    printf("|-------------------------------|-----------------|\n");

    //5 Zeilen (Text links, Bild rechts)
    for (int i = 0; i < 5; i++) {
        char text_left[40] = "";

        // Text für die linke Seite
        switch(i) {
            // %.19s: Maximal 19 Zeichen drucken
            case 0: snprintf(text_left, 40, "Name:   %.23s", v->name); break;
            case 1: snprintf(text_left, 40, "Origin: %.23s", v->origin); break;
            case 2: snprintf(text_left, 40, "Born:   %d", v->birth_year_doc); break;
            case 3: snprintf(text_left, 40, "Expire: %d", v->expiry_year); break;
            //default case:
            default: snprintf(text_left, 50, " "); 
            break;
        }
        // %-30s : 30 breit, %-16s : 16 breit
        printf("| %-30s| %-16s|\n", text_left, get_face_line(v, i));
    }
    printf("|_______________________________|_________________|\n");
}

static void print_id_card(const visitor_t *v){
    printf("\n");
    printf(" _________________________________________________ \n");
    printf("| I D   C A R D                 | FOTO            |\n");
    printf("|-------------------------------|-----------------|\n");

    for (int i = 0; i < 5; i++) {
        char text_left[40] = "";

        switch(i) {
            case 0: snprintf(text_left, 40, "Name:   %.23s", v->name); break;
            case 1: snprintf(text_left, 40, "Level:  %d", v->access_level); break;
            case 2: snprintf(text_left, 40, "Born:   %d", v->birth_year_id); break;
            // Zeile 3 und 4 leer lassen beim Text
            default: snprintf(text_left, 40, " "); 
            break;
        }

        printf("| %-30s| %-16s|\n", text_left, get_face_line(v, i));
    }
    printf("|_______________________________|_________________|\n");
    
    // Items unter der ID Card anzeigen
    if (v->item_count > 0) {
        printf("\n===================================================\n");
        printf("           GEPÄCK SCANNER (%zu Objekt/e):\n", v->item_count);
        printf("---------------------------------------------------\n");

        for(size_t k=0; k < v->item_count; k++) {
            // Einfache Anzeige der Items
            char *cat = "Unbekannt";
            if(v->items[k].category == ITEMCAT_WEAPON) cat = "WAFFE";
            else if(v->items[k].category == ITEMCAT_FOOD) cat = "Essen";
            else if(v->items[k].category == ITEMCAT_TOOL) cat = "Werkzeug";
            else if(v->items[k].category == ITEMCAT_MEDICINE) cat = "Medizin";
            printf("  -> %-20.20s [%s]\n", v->items[k].name, cat);
        }
    } else {
        printf("\n [i] Gepäck: Leer\n");
    }
}

static void print_rules_short(const rules_t *rules){
    printf("\n===================================================\n");
    printf("               TAGES-REGELN (Jahr: %d)\n", rules->current_year);
    printf("===================================================\n");
    printf(" - Dokumentenpflicht: %s\n", rules->require_doc ? "JA" : "NEIN");
    if (rules->forbid_weapons) printf(" - ACHTUNG: Waffen verboten!\n");
    if (rules->emergency_mode) printf(" - NOTSTAND: Nur Level %d - %d erlaubt!\n", rules->min_level, rules->max_level);
    if (rules->night_mode) printf(" - NIGHTMODE: Nur Level %d - %d erlaubt!\n", rules->min_level, rules->max_level);
    printf("===================================================\n");
}
/*Interaktion:*/
user_decision_t ui_interact_visitor(const visitor_t *v, const rules_t *rules) {
    char input;
    int view_mode = 0; // 0 = Passport (Start), 1 = ID Card, 2 = Regeln
    
    // Endlosschleife, bis eine Entscheidung (A oder D) getroffen wird
    while (true) {
        
        // 1. Anzeige je nach Modus
        if (view_mode == 0) {
            if (v->has_required_doc){
                print_passport(v);
            } else {
                printf("\n");
                printf("    [!] DOKUMENT FEHLT [!]\n");
                printf("    Kein Ausweisdokument verfügbar!\n");
                printf("  \n%.23s: Ich habe meine Papiere leider verloren.\n", v->name);
            }
        }
        else if (view_mode == 1){
            if(v->has_required_doc){
                print_id_card(v);
            } else {
                printf("\n");
                printf("    [!] DOKUMENT FEHLT [!]\n");
                printf("    Keine ID-Card verfügbar!\n");
                printf("  \n%.23s: Ich habe meine Papiere leider verloren.\n", v->name);
            }
        }
        else if (view_mode == 2){
            print_rules_short(rules);
        }
        
        // Menü
        printf("\n       [P]assport  [I]D-Card  [R]egeln\n");
        printf("---------------------------------------------------\n");
        printf("               [A]CCEPT    [D]ENY\n");
        printf("Dein Befehl: ");

        // Eingabe lesen
        int result = scanf(" %c", &input);

        // Buffer leeren
        if (result == 1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        // Logik
        switch (input) {
            // Ansicht wechseln
            case 'p': case 'P': view_mode = 0; break;
            case 'i': case 'I': view_mode = 1; break; // Egal ob 'i' oder 'I': Beide Fälle führen diesen Code aus
            case 'r': case 'R': view_mode = 2; break;

            // Entscheidung treffen (Schleife verlassen)
            case 'a': case 'A':
                printf("\n===================================================\n");
                printf("              >> EINREISE GENEHMIGT <<\n");
                printf("---------------------------------------------------\n");
                return USER_ALLOW; // Rüclgabe an game.c
            case 'd': case'D':
                printf("\n===================================================\n");
                printf("              >> EINREISE ABGELEHNT <<\n");
                printf("---------------------------------------------------\n");
                return USER_DENY; // Rückgabe an game.c

            default: 
                printf("\n>>> Ungueltige Eingabe! <<<\n");
                break;
        }
    }
}
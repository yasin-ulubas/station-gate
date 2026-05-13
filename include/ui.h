#ifndef UI_H
#define UI_H

#include <stdbool.h>
#include "types.h"

#define COL_RESET "\033[0m"
#define COL_RED "\033[31m"
#define COL_GREEN "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_BLUE "\033[34m"

#define COL_BOLD_WHITE "\e[1;37m"
#define COL_BOLD_BLUE "\e[1;34m"
/*----------------------------------------------------------------------------------
    Wichtiger Unterschied zwischen ui.h und assets.h:
    ui.h liest Daten und druckt sie (Ergebnis Text auf dem Bildschirm)
    assets.h liest Daten und parst Daten (Ergebnis Structs und Arrays im Speicher)
-----------------------------------------------------------------------------------*/                                                 

/* ==== Ausgabe ==== */

/* Druckt Textdatei (ASCII-Design) auf stdout 
 * Rückgabe: true, wenn Datei öffnet & gedruckt werden konnte, sonst false
**/
bool ui_print_file(const char *path);


/* ==== Eingabe ==== */

/* Liest Zeile mit stdin in buf (buf = Bennenung für temporären Speicher im Arbeitsspeicher)
 * Entfernt all \n, wenn vorhanden
 * Nutzen: Spielernamen, "drücke Enter", freie Texte, etc. 
**/
bool ui_read_line(char *buf, unsigned bufsize);

/* ==== Spiel-Interaktion ==== */

/* Zeigt Besucherdaten an und erlaubt Wechseln zwischen Dokumenten (Pass/ID).
 * Fragt am Ende nach Entscheidung (Allow/Deny).
 * Rückgabe: USER_ALLOW oder USER_DENY
 */
user_decision_t ui_interact_visitor(const visitor_t *v, const rules_t *rules);

#endif
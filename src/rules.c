#include "rules.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------
Setzt alle Regeln auf sichere Standartwertem
Regeln gelten, wenn kein spezielles Scenario geladen wurde
---------------------------------------------------------*/

void rules_init(rules_t *rules)
{
    // Sicherheitscheck: verhindert Absturz bei NULL
    if (!rules) {
        return;
    }

    // Das aktuelle Jahr im Spiel
    // Wird benutzt, um abgelaufene Dokumente zu erkennen
    rules->current_year = 2126;

    // Erlaubter Bereich für Zugangsstufen
    // Alles außerhalb wird vom Validator abgelehnt
    rules->min_level = 1;
    rules->max_level = 5;

    // Gibt an, ob Besucher zwingend ein gültiges Dokument brauchen
    rules->require_doc = true;

    // Nachtmodus: könnte später strengere Regeln aktivieren
    rules->night_mode = false;

    // Notfallmodus: könnte bestimmte Items oder Level verbieten
    rules->emergency_mode = false;

    // Waffen verboten?
    rules->forbid_weapons = true;
}

// Lädt Regelszenario aus Textdatei
bool rules_load_from_file(const char *path, rules_t *rules) {
    if (!path || !rules) {
        return false;
    }

    // Default setzen
    rules_init(rules);

    // Datei öffnen
    FILE *file = fopen(path, "r");
    if (!file) {
        return false;
    }

    // Zeilenweise lesen
    char line_buffer[256];

    while (fgets(line_buffer, sizeof(line_buffer), file)) {

        // \n entfernen 
        size_t len = strlen(line_buffer);
        if (len > 0 && line_buffer[len - 1] == '\n') {
            line_buffer[len - 1] = '\0';
        }

        // Leere Zeilen überspringen
        if (line_buffer[0] == '\0') {
            continue;
        }

        // Mögliche Kommentare in Datei überspringen
        if (line_buffer[0] == '#') {
            continue;
        }

        // Wir suchen in Zeile nach "=", trennt Schlüsselwort von Wert
        char *equals = strchr(line_buffer, '=');
        //Wenn kein "=" vorhanden, ignorieren und nächste Zeile
        if (!equals) {
            continue;
        }

        // Zeile aufteilen in zwei Strings
        *equals = '\0';
        char *key = line_buffer;    // Regelname
        char *value = equals + 1;   // Regelwert

        // Aktuelles Jahr
        if (strcmp(key, "current_year") == 0) {
            rules->current_year = atoi(value);
        }

        // Minimales Access-Level
        else if (strcmp(key, "min_level") == 0) {
            rules->min_level = atoi(value);
        }

        // Maximales Access-Level
        else if (strcmp(key, "max_level") == 0) {
            rules->max_level = atoi(value);
        }

        // Dokumentpflicht: 1->Dokument notwendig, 0->Dokument nicht notwendig
        else if (strcmp(key, "require_doc") == 0) {
            rules->require_doc = (atoi(value) != 0);
        }

        // Nighmode, kann später strengere Regeln aktivieren
        else if (strcmp(key, "night_mode") == 0) {
            rules->night_mode = (atoi(value) != 0);
        }

        // Notfallmodus, kann bestimmte Level oder Items verbieten
        else if (strcmp(key, "emergency_mode") == 0) {
            rules->emergency_mode = (atoi(value) != 0);
        }

        // Waffen erlaubt?
        else if (strcmp(key, "forbid_weapons") == 0) {
            rules->forbid_weapons = (atoi(value) != 0);
        }

        else {
            // Weitere Regeln können hinzgefügt werden
        }

    }

    fclose(file);
    return true;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "stats.h"

/*
 * Initialisiert die Statistik.
 */
void stats_init(stats_t *s)
{
    if (s == NULL) {
        return;
    }

    // Setzt alle Felder der Struktur auf 0
    memset(s, 0, sizeof(stats_t));
}

/*
 * Speichert eine Entscheidung des Spielers.
 *
 * player_correct:
 *   true  -> richtige Entscheidung
 *   false -> falsche Entscheidung
 *
 * reason:
 *   wird hier NICHT ausgewertet,
 *   da stats_t keine Detailgründe speichert
 */
void stats_record(stats_t *s, bool player_correct, deny_reason_t reason)
{
    if (s == NULL) {
        return;
    }

    // reason wird nicht benutzt → Warnung vermeiden
    (void)reason;

    if (player_correct) {
        s->correct++;
    } else {
        s->wrong++;
    }
}

/*
 * Gibt die Statistik im Terminal aus.
 */
void stats_print(const stats_t *s)
{
    if (s == NULL) {
        return;
    }
    printf("\n===================================================\n");
    printf("                 SPIELSTATISTIK");
    printf("\n---------------------------------------------------\n");
    printf("\nRichtig entschieden: %d\n", s->correct);
    printf("Falsch entschieden:  %d\n", s->wrong);
    printf("\n---------------------------------------------------");
    printf("\n===================================================\n");
}

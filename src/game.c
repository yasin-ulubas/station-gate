#include "game.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rules.h"
#include "generator.h"
#include "validator.h"
#include "ui.h"
#include "stats.h"
#include "stats.h"

// Hilfsfunktion: Auf Enter warten
static void wait_for_enter_game(void) {
    printf("\n> Drücke [ENTER] zum Fortfahren <");

    int c;

    //Zeichen bis Enter verwerfen
    while ((c = getchar()) != '\n') {}
}

// Hilfsfunktion: Zufällig Tages-Regeln aussuchen
static void build_random_rules_path(char *rules_path, size_t rules_path_size) {
    unsigned chosen_scenario = 1u + (unsigned)(rand() % SCENARIO_COUNT);
    snprintf(rules_path, rules_path_size, "data/day_rules/scenario_%02u.txt", chosen_scenario); 
}

void game_init(game_state_t *state, const char *player_name) {
    if (!state) {
        return;
    }

    // Startwerte
    state->day = 1;
    state->lives = START_LIVES;
    state->score = 0;

    // Spielernamen speichern
    if (player_name && player_name[0] != '\0') {
        strncpy(state->player_name, player_name, MAX_PLAYER_NAME_LEN - 1);
        state->player_name[MAX_PLAYER_NAME_LEN - 1] = '\0';
    } else {
        strncpy(state->player_name, "Player", MAX_PLAYER_NAME_LEN - 1);
        state->player_name[MAX_PLAYER_NAME_LEN - 1] = '\0';
    }
}

bool game_run(game_state_t *state, const assets_t *assets) {
    if (!state || !assets) {
        return false;
    }

    printf("\n===================================================\n");
    printf("                   SPIELSTART");
    printf("\n===================================================\n");
    printf("\nWilkommen, KONTROLLEUR \n");
    printf("\nSpieler: <%s>\n", state->player_name);

    // Statistik für das ganze Game
    stats_t stats;
    stats_init(&stats);

    wait_for_enter_game();
    
    // Hauptschleife Tage
    while (state->day <= MAX_DAYS && state->lives > 0) {
        // Tagesregeln laden
        rules_t rules;
        rules_init(&rules);

        // Zufälliges Szenario aufrufen
        char rules_path[256];
        build_random_rules_path(rules_path, sizeof(rules_path));

        if (!rules_load_from_file(rules_path, &rules)){
            // Nicht abbrechen, einfach default Regeln benutzen
            printf("\nWarnung: Konnte Regeln nicht laden!: %s\n", rules_path);
            printf("--> Nutze default Regeln.\n");
        }

        // Tages-Intro
        printf("\n===================================================\n");
        printf("                 TAG %u / %d BEGINNT\n", state->day, MAX_DAYS);
        printf("---------------------------------------------------\n");
        printf(COL_RED"\nLeben: %d "COL_RESET"| "COL_YELLOW"Score: %d\n"COL_RESET, state->lives, state->score);
        printf("\n---------------------------------------------------\n");
        printf("===================================================\n");

        wait_for_enter_game();

        // Regel-Übersicht
        printf("\n===================================================\n");
        printf("                  HEUTIGE REGELN\n");
        printf("---------------------------------------------------\n");
        printf("- Jahr:             %d\n", rules.current_year);
        printf("- Zugangslevel:     %d - %d\n", rules.min_level, rules.max_level);
        printf("- Dokumentpflicht?  %s\n", rules.require_doc ? "JA" : "NEIN");
        printf("- Waffen verboten?  %s\n", rules.forbid_weapons ? "JA" : "NEIN");
        printf("- Nightmode?        %s\n", rules.night_mode ? "JA" : "NEIN");
        printf("- Emergency mode?   %s\n", rules.emergency_mode ? "JA" : "NEIN");
        printf("---------------------------------------------------\n");
        printf("===================================================\n");

        wait_for_enter_game();

        // Besucher-Schleife
        for (int i = 0; i < VISITORS_PER_DAY && state->lives > 0; i++) {
            printf("\n===================================================\n");
            printf("                BESUCHER %d / %d\n", i+1, VISITORS_PER_DAY);
            printf("---------------------------------------------------\n");

            visitor_t v;

            // Generator braucht assets_t* --> wir müssten casten
            // Generator soll außerdem assets eigentlich nicht verändern
            if (!generator_make_visitor(&v, (assets_t *)assets, &rules)) {
                printf("Fehler: Konnte Besucher nicht generieren!\n");
                break;
            }

            // Spieler interagiert (Besucher anschauen und dann accept/deny)
            user_decision_t user_decision = ui_interact_visitor(&v, &rules);

            // Validator entscheidet richtig oder falsch
            result_t res = validator_check(&v, &rules);

            // Spielerentscheidung bewerten
            // korrekt, wenn Spieler-Allow == res.allow
            bool player_allowed = (user_decision == USER_ALLOW);
            bool correct = (player_allowed == res.allow);

            // Stats updaten
            stats_record(&stats, correct, res.reason);

            if (correct) {
                state->score += 1;
                printf(">> Gute Wahl! "COL_YELLOW"(+1 Score)"COL_RESET" | Score: %d\n", state->score);
            } else {
                state->lives -= 1;
                printf(">> WIESO LÄSST DU DEN REIN?!\n");
                printf(">> Grund: %s\n", validator_reason_text(res.reason));
                printf(">> "COL_RED"(-1 Lives)"COL_RESET" | Lives: %d\n", state->lives);
            }

            wait_for_enter_game();
        }

        // Tag beenden und nächsten einleiten
        if (state->lives > 0) {
            printf("\n===================================================\n");
            printf("\n>> Ende von Tag %d. (Score=%d, Lives=%d)\n", state->day, state->score, state->lives);
            printf("---------------------------------------------------\n");
            state->day += 1;
            wait_for_enter_game();
        }
    }

    // Spielende
    printf("\n===================================================\n");
    if (state->lives <= 0) {
        printf(COL_RED"                   GAME OVER\n"COL_RESET);
        printf("---------------------------------------------------\n");
    } else {
        printf(COL_YELLOW"Herzlichen Glückwunsch!"COL_RESET" Alle Tage geschafft. Guten Hunger!\n");
        printf("---------------------------------------------------\n");
    }
    printf("Endscore: %d\n", state->score);
    printf("---------------------------------------------------\n");
    printf("===================================================\n");

    wait_for_enter_game();

    // Statistik anzeigen
    stats_print(&stats);

    wait_for_enter_game();

    return true;
}
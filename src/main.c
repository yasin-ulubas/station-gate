#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // für time (Zufall)
#include <unistd.h>

#include "ui.h"
#include "types.h"
#include "assets.h"
#include "config.h"
#include "game.h"

static void wait_for_enter(void) {
    printf("\n> Drücke "COL_BOLD_WHITE"[ENTER]"COL_RESET" zum Fortfahren <\n");
    int c;
    // Zeichen bis Enter verwerfen
    while ((c = getchar()) != '\n') {}
}

static void show_screen_and_pause(const char *path) {
    if (!ui_print_file(path)) {
        printf("\nKonnte Datei nicht öffnen: %s\n", path);
    }

    wait_for_enter();
}

int main(void) {
    // Zufall initialiseren
    srand((unsigned)time(NULL));

    // Assets laden
    assets_t assets;
    assets_init(&assets);

    if (!assets_load(&assets, "data")) {
        printf("FEHLER: Konnte Assets nicht laden.\n");
        return EXIT_ERR_INPUT;
    }

    //Startbildschirm
    ui_print_file(SCREEN_TITLE);
    sleep(1.5);
    printf("\n───────────────────────────────────────────────────\n");
    wait_for_enter();

    // Menü-Schleife
    unsigned running = 1;
    while (running) {
        ui_print_file(SCREEN_MENU);

        printf("\n> Wähle zwischen (%d und %d) zum Fortfahren < ", MENU_MIN, MENU_MAX);


        //Sicheres Einlesen (Fix für Enum Pointer Warnung)
        unsigned user_choice;
        if (scanf("%u", &user_choice) != 1) {
            printf("Ungültige Eingabe!\n");
            assets_free(&assets);
            return EXIT_ERR_INPUT;
        }

        getchar();

        //Eingabe: Menüauswahl
        menu_choice_t menu_choice;

        menu_choice = (menu_choice_t)user_choice;

        if (user_choice > MENU_MAX) {
            printf("Auswahl außerhalb des gültigen Bereichs!\n");
            assets_free(&assets);
            return EXIT_ERR_INPUT;
        }

        switch(menu_choice) {
            case MENU_START: {
                // Eingabe: Spielernamen
                char player_name[MAX_PLAYER_NAME_LEN];
                printf("\nBitte Spielernamen eingeben: ");
                scanf("%23s", player_name);

                getchar();

                // Spiel starten
                game_state_t state;
                game_init(&state, player_name);
                game_run(&state, &assets);

                break;
            }
            case MENU_INSTRUCTIONS:
                show_screen_and_pause(SCREEN_INSTRUCTIONS);
                break;
            case MENU_EXIT:
                running = 0;
                break;
        }
    }

    assets_free(&assets);

    sleep(1);
    printf("\nKein Einsatz.\nKeine Mission.\nKein Dürüm.\n"COL_RED"Programm beendet."COL_RESET"\n");
    return EXIT_OK;
}

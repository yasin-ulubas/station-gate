#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <stdbool.h>

/* ===== Globale Konstanten ===== */
#define MAX_DAYS 7
#define START_LIVES 3
#define VISITORS_PER_DAY 10

#define MAX_NAME_LEN 32     // Besuchername (aus Datei)
#define MAX_ORIGIN_LEN 24   // Herkunft von Besucher (aus Datei)

#define MAX_PLAYER_NAME_LEN 24  // Spielername (User-Eingabe)

#define MAX_ITEMS_PER_VISITOR 3

#define MENU_MIN MENU_START
#define MENU_MAX MENU_EXIT

#define SCENARIO_COUNT 4

#define EXIT_OK 0
#define EXIT_ERR_INPUT 1

/* ===== Menü & Spieler-Input ===== */
typedef enum {
    MENU_START = 0,
    MENU_INSTRUCTIONS,
    MENU_EXIT
} menu_choice_t;

typedef enum {
    USER_ALLOW = 0,
    USER_DENY
} user_decision_t;

/* ===== Gründe für Ablehnung ===== */
typedef enum {
    REASON_NONE = 0,        // Kein Ablehnungsgrund (Einreise erlaubt)

    REASON_EXPIRED,
    REASON_MISSING_DOC,
    REASON_MISMATCH,
    REASON_WRONG_LEVEL,
    REASON_FORBIDDEN_ITEM,
    REASON_EMERGENCY_MODE,
} deny_reason_t;

/* ===== Item-Kategorie ===== */
typedef enum {
    ITEMCAT_NONE = 0,
    ITEMCAT_FOOD,
    ITEMCAT_MEDICINE,
    ITEMCAT_TOOL,
    ITEMCAT_WEAPON
} item_category_t;

/* ===== Item zu Kategorie ===== */
typedef struct {
    char name[20];
    item_category_t category;
} item_t;

/* ===== ASCII-Designs ===== */
typedef struct {
    char **lines;
    size_t line_count;
    size_t width;
} ascii_design_t;

/* ===== Besucherdaten ===== */
typedef struct {
    char name[MAX_NAME_LEN];
    char origin[MAX_ORIGIN_LEN];

    const ascii_design_t *face;

    int access_level;

    // Dokumente
    bool has_required_doc;
    int expiry_year;

    // Mismatch-Szenarien
    int birth_year_id;
    int birth_year_doc;

    // Items
    item_t items[MAX_ITEMS_PER_VISITOR];
    size_t item_count;

} visitor_t;

/* ===== Täglich variierende Regeln ===== */
typedef struct {
    int current_year;
    int min_level;
    int max_level;
    
    bool night_mode;
    bool emergency_mode;

    bool require_doc;

    bool forbid_weapons;
} rules_t;

/* ===== Ergebnis ===== */
typedef struct {
    bool allow;
    deny_reason_t reason;
} result_t;

/* ===== Spielzustand ===== */
typedef struct {
    char player_name[MAX_PLAYER_NAME_LEN];
    int day;
    int lives;
    int score;
} game_state_t;

/* ===== Statistik ===== */
typedef struct {
    int total_visitors;
    int correct;
    int wrong;
} stats_t;


/* ===== Assets ===== */
typedef struct {
    ascii_design_t *designs;
    size_t design_count;

    char **names;
    size_t name_count;
    size_t current_name_idx;

    char **origins;
    size_t origin_count;
    size_t current_origin_idx;

    rules_t day_rules[MAX_DAYS];

    item_t *items;
    size_t item_count;

} assets_t;


#endif
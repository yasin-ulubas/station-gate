#include <stdio.h>
#include <string.h>
#include "types.h"
#include "validator.h" 
#include "rules.h"

// Hilfsfunktion für schöne Ausgaben
void assert_test(const char *test_name, int expected, int actual) {
    if (expected == actual) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s (Erwartet: %d, Bekommen: %d)\n", test_name, expected, actual);
    }
}

int main() {
    printf("Starte Logik-Tests (Datei wird eingelesen) \n=====================\n");

    rules_t test_rules;

    rules_init(&test_rules);

    const char *filepath = "data/day_rules/test_logic_rules.txt";

    printf("Lade Regeln aus '%s'...\n", filepath);

    
    // Regeln (Eingabedatei)
    test_rules.current_year = 2000;
    test_rules.require_doc = true;      // Ausweis Pflicht
    test_rules.forbid_weapons = true;   // Waffen verboten
    test_rules.min_level = 1;
    test_rules.max_level = 5;

    // Der perfekte Besucher
    visitor_t v1 = {0};
    // Daten manuell füllen
    strcpy(v1.name, "Gut gemacht");
    strcpy(v1.origin, "Kebap Town");
    v1.has_required_doc = true;
    v1.expiry_year = 2005;
    v1.birth_year_doc = 1980;
    v1.birth_year_id = 1980;
    v1.access_level = 3;
    v1.item_count = 0;


    result_t res1 = validator_check(&v1, &test_rules); 

    if (res1.allow == 0){
        printf("\n[DEBUG] Der Validator hat abgelehnt! Grund: %s\n", validator_reason_text(res1.reason));
    }
    assert_test("Perfekter Besucher soll rein", 1, res1.allow);


    // Besucher ohne Pass
    visitor_t v2 = v1; 
    strcpy(v2.name, "Ne geht so nicht");
    v2.has_required_doc = false; 

    result_t res2 = validator_check(&v2, &test_rules);
    assert_test("Besucher ohne Pass muss abgelehnt werden", 0, res2.allow);


    // Besucher mit Waffe
    visitor_t v3 = v1;
    strcpy(v3.name, "Rambo");
    v3.item_count = 1;
    v3.items[0].category = ITEMCAT_WEAPON; 
    strcpy(v3.items[0].name, "Messer");

    result_t res3 = validator_check(&v3, &test_rules);
    assert_test("Besucher mit Waffe muss abgelehnt werden", 0, res3.allow);


    // Abgelaufener Pass
    visitor_t v4 = v1;
    strcpy(v4.name, "Alter Pass");
    v4.expiry_year = 1999; 

    result_t res4 = validator_check(&v4, &test_rules);
    assert_test("Abgelaufener Pass muss abgelehnt werden", 0, res4.allow);

    printf("\nTests abgeschlossen.\n");
    return 0;
}
#include "validator.h"
#include <stddef.h> 

// Hilfsfunktionen zum Erzeugen eines result_t, untere Code wird lesbarer

//Ergebnis für "Einreise erlaubt"
static result_t make_allow(void) {
    result_t r;
    r.allow = true;
    r.reason = REASON_NONE;
    return r;
}

// Ergebnis für "Einreise verweigert"
static result_t make_deny(deny_reason_t reason) {
    result_t r;
    r.allow = false;
    r.reason = reason;
    return r;
}

// Hilfsfunktion: checkt ob Visitor eine Waffe dabei hat
static bool visitor_has_weapon(const visitor_t *v) {
    if (!v) return false;

    for (size_t i = 0; i < v->item_count; i++) {
        if (v->items[i].category == ITEMCAT_WEAPON) {
            return true;
        }
    }
    return false;
}

// Haupt-Validierungsfunktion: Darf Besucher rein? Warum?
result_t validator_check(const visitor_t *v, const rules_t *rules) {
    // Sicherheitscheck: wenn irgendwas NULL ist, lieber ablehnen
    if (!v || !rules) {
        return make_deny(REASON_NONE);
    }

    // 1) Emergency Mode: wenn aktiv erst ab Level 3
    if (rules->emergency_mode) {
        if (v->access_level < 3) {
            return make_deny(REASON_EMERGENCY_MODE);
        }
    }

    // 2) Dokumentpflicht
    if (rules->require_doc && !v->has_required_doc) {
        return make_deny(REASON_MISSING_DOC);
    }

    // 3) Ablaufdatum (nur prüfen, wenn beide Dokument vorhanden ist)
    if (v->has_required_doc) {
        if (v->expiry_year < rules->current_year) {
            return make_deny(REASON_EXPIRED);
        }
    }

    // 4) Mismatch bei Geburtsjahren (nur wenn Dokument vorhanden ist)
    if (v->has_required_doc) {
        if (v->birth_year_doc != v->birth_year_id) {
            return make_deny(REASON_MISMATCH);
        }
    }

    // 5) Access Level (immer prüfen)
    if (v->access_level < rules->min_level || v->access_level > rules->max_level) {
        return make_deny(REASON_WRONG_LEVEL);
    }

    // 6) Verbotene Items: Waffen
    if (rules->forbid_weapons) {
        if (visitor_has_weapon(v)) {
            return make_deny(REASON_FORBIDDEN_ITEM);
        }
    }

    // Wenn nichts verletzt wurde -> erlauben
    return make_allow();
}

// Übersetzung von deny_reason_t in Text
const char *validator_reason_text(deny_reason_t reason) {
    switch (reason) {
        case REASON_NONE:           
            return "OK";
        case REASON_EXPIRED:        
            return "Dokument abgelaufen";
        case REASON_MISSING_DOC:    
            return "Dokument fehlt";
        case REASON_MISMATCH:       
            return "Daten stimmen nicht ueberein";
        case REASON_WRONG_LEVEL:    
            return "Falsches Access-Level";
        case REASON_FORBIDDEN_ITEM: 
            return "Verbotener Gegenstand";
        case REASON_EMERGENCY_MODE: 
            return "Notfallmodus: Zugang erst ab Level 3";
        default:                    
            return "Unbekannter Grund";
    }
}
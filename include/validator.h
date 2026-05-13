#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "types.h"

/*-----------------------------------------------------------------------------
Prüfen ob ein Besucher rein darf und warum (Feedback bei falscher Entscheidung)
-------------------------------------------------------------------------------*/

/*
 * Prüft Besucher gegen Tagesregeln und gibt Ergebnis zurück
 * result.allow = true/false
 * result.reason = konkreter Grund (für UI/Stats)
 */
result_t validator_check(const visitor_t *v, const rules_t *rules);

/*
 * Übersetzt deny_reason_t in einen erklärenden Text
 * Bei falscher Entscheidung können wir direkt ausgeben: "Falsch, weil ..."
 */
const char *validator_reason_text(deny_reason_t reason);

#endif
# station_gate

🚧 Border Control Terminal — C Terminal Game
Ein terminalbasiertes Entscheidungs- und Logikspiel inspiriert von Kontrollsystemen wie Papers, Please.
Der Spieler übernimmt die Rolle eines Grenzkontrolleurs und muss Besucher anhand dynamischer Tagesregeln überprüfen, Dokumente kontrollieren und richtige Entscheidungen treffen.

Das Projekt wurde im Rahmen eines Uni-Projekts vollständig in C entwickelt und legt den Fokus auf:

- modulare Softwarearchitektur
- Speicherverwaltung
- Dateiverarbeitung
- Zustandsverwaltung
- Validierungslogik
- saubere Trennung von Game Logic & UI


🎮 Gameplay
Jeden Tag gelten neue Regeln:
- Dokumentpflicht
- erlaubte Access-Level
- Waffenverbote
- Emergency-Mode
- Night-Mode


Für jeden Besucher musst du entscheiden:

✅ Einreise erlauben
❌ Einreise verweigern

Eine falsche Entscheidung kostet Leben.


✨ Features
- Dynamisches Regel- und Validierungssystem
- Zufällig generierte Besucher
- ASCII-basierte Dokumente & UI
- Asset-System für Namen, Herkunft, Items & ASCII-Art
- Statistiksystem für richtige/falsche Entscheidungen
- Eigene Logiktests (test_logic.c)
- Defensive Programmierung & NULL-Checks
- Modularer Aufbau mit Header-/Source-Trennung


🏗️ Projektstruktur
├── main.c
├── game.c
├── generator.c
├── validator.c
├── rules.c
├── ui.c
├── assets.c
├── stats.c
│
├── *.h
│
├── data/
│   ├── screens/
│   ├── day_rules/
│   ├── visitor_attributes/
│   └── visitors_ascii/
│
└── test_logic.c


🔹 Modulare Architektur
Modul	          Verantwortung

game	          Hauptspielablauf
validator	      Regelprüfung & Entscheidungen
generator	      Besucher-Generierung
rules	          Laden dynamischer Tagesregeln
assets	        Laden externer Daten & ASCII-Art
ui	            Terminaldarstellung & Eingabe
stats	          Statistiksystem


👨‍💻 Autoren
Student der Technischen Universität Hamburg
Bennet, Micka und Yasin

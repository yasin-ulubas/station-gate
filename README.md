# station-gate

🚧 **Border Control Terminal** — Ein terminalbasiertes Entscheidungs- und Logikspiel in C, inspiriert von Spielen wie *Papers, Please*.

In *station-gate* übernimmt der Spieler die Rolle eines Grenzkontrolleurs und muss Besucher anhand dynamischer Tagesregeln überprüfen, Dokumente kontrollieren und Entscheidungen treffen. Das Projekt wurde vollständig in **C** entwickelt und legt den Fokus auf modulare Softwarearchitektur, Speicherverwaltung und Zustandslogik.

## Features

### Gameplay

Jeden Tag gelten neue Regeln:

- 📄 Dokumentpflicht
- 🔐 Erlaubte Access-Level
- 🚫 Waffenverbote
- 🚨 Emergency-Mode
- 🌙 Night-Mode

Für jeden Besucher muss entschieden werden:

✅ **Einreise erlauben**  
❌ **Einreise verweigern**

Eine falsche Entscheidung kann Konsequenzen haben.

### Technische Schwerpunkte

- Modulare Softwarearchitektur
- Speicherverwaltung in C
- Dateiverarbeitung
- Zustandsverwaltung
- Validierungslogik
- Trennung von Game Logic & UI

## Motivation

Dieses Projekt entstand im Rahmen eines Uni-Projekts an der Technischen Universität Hamburg und hatte das Ziel, ein komplexeres Softwaresystem in **C** zu entwickeln.

Besonderer Fokus lag auf:

- sauberem Softwaredesign
- modularer Architektur
- Speicherverwaltung
- Teamarbeit in einem größeren Projekt

## 📋 Requirements

Für das Projekt werden folgende Abhängigkeiten benötigt:

- **Git**
- **C-Compiler** (z. B. GCC)
- **Make**

## 🛠️ Installation / Getting Started

Repository klonen:

```bash
git clone https://github.com/yasin-ulubas/station-gate.git
cd station-gate
```

Projekt kompilieren:

```bash
make
```

Spiel starten:

```bash
./station-gate
```

> Unter Windows ggf. `station-gate.exe` ausführen.

## ▶️ Usage

### Spiel starten

Nach erfolgreicher Kompilierung kann das Spiel direkt über das Terminal gestartet werden:

```bash
./station-gate
```

## 👨‍💻 Contributors

Projekt der Technischen Universität Hamburg

- **Bennet**
- **Micka**
- **Yasin**

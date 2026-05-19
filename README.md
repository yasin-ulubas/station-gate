# station-gate

🚧 **Border Control Terminal** — Ein terminalbasiertes Entscheidungs- und Logikspiel in C, inspiriert von Spielen wie *Papers, Please*.

In *station-gate* übernimmt der Spieler die Rolle eines Grenzkontrolleurs und muss Besucher anhand dynamischer Tagesregeln überprüfen, Dokumente kontrollieren und Entscheidungen treffen. Das Projekt wurde vollständig in **C** entwickelt und legt den Fokus auf modulare Softwarearchitektur, Speicherverwaltung und Zustandslogik.

## Features

## 🎮 Gameplay

In **station-gate** übernimmst du die Rolle eines Grenzkontrolleurs an einem Sicherheitsterminal. Deine Aufgabe ist es, eintreffende Besucher anhand täglich wechselnder Sicherheitsvorgaben zu überprüfen und über ihre Einreise zu entscheiden.

Jeder Besucher bringt unterschiedliche Informationen und Dokumente mit. Deine Entscheidung basiert auf den **zufällig generierten Regeln des aktuellen Tages**, wodurch jede Spielrunde unterschiedlich verläuft.

### 🎲 Dynamische Tagesregeln

Zu Beginn jedes Tages wird zufällig vorgegebene Kombinationen auf Tagesregeln ausgewählt. Dadurch verändert sich das Gameplay kontinuierlich und Entscheidungen müssen immer wieder neu bewertet werden. Ein Tag besteht aus zehn Kontrollen. Nach sieben Tagen ist das Spiel beendet und es wird eine Statistik angezeigt.

Mögliche Regeln sind:

#### 📄 Dokumentpflicht
Besucher müssen ihre Dokumente dabei haben (immer aktiviert).

#### 🔐 Access-Level
Nicht jeder Besucher besitzt die notwendige Sicherheitsfreigabe. Der angegebene Access-Level muss den aktuellen Anforderungen des jeweiligen Tages entsprechen.

#### 🚫 Waffenverbot
Besucher dürfen keine verbotenen Gegenstände oder Waffen mitführen. Verdächtige Personen müssen abgewiesen werden.

#### 🚨 Emergency-Mode
Im Ausnahmezustand gelten verschärfte Sicherheitsmaßnahmen und strengere Kontrollen.

#### 🌙 Night-Mode
Veränderte Bedingungen erschweren die Überprüfung und erhöhen den Entscheidungsdruck.

### ⚖️ Entscheidungen treffen

Für jeden Besucher musst du genau eine Entscheidung treffen:

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

Bei dem Uni-Projekts bestand die Möglichkeit, das Thema frei zu wählen. Unser Ziel war es, ein Projekt zu entwickeln, das uns persönlich interessiert und gleichzeitig die technischen Anforderungen der Veranstaltung erfüllt.

Da wir alle gerne Videospiele spielen, wollten wir bewusst ein Projekt umsetzen, das einen spielerischen Charakter besitzt und die Umsetzung komplexer Logik mit einer kreativen Idee verbindet. Inspiriert von regelbasierten Entscheidungsspielen wie *Papers, Please* entstand so die Idee eines terminalbasierten Grenzkontrollspiels.

Trotz des technischen Fokus auf **Speicherverwaltung, Zustandslogik, Dateiverarbeitung und modularer Architektur in C** wollten wir das Projekt bewusst etwas humorvoller und kreativer gestalten. Deshalb enthalten verschiedene Elemente des Spiels bewusst humoristische Details – darunter kreative Namen sowie Besucherherkünfte von Planeten aus dem *Star Wars*-Universum.

Besonderer technischer Fokus lag auf:

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

# PinBoom Control System

Dieses Projekt implementiert ein **sicherheitskritisches Steuerungssystem** mit **zwei Arduino-Mikrocontrollern**.  
Es wurde entwickelt, um die Logik, Steuerung und Sicherheitsfunktionen für ein **PinBoom-System** bereitzustellen.

---

## 🔍 Projektübersicht
Das System besteht aus **zwei getrennten Steuerungen**, die zusammenarbeiten:

1. **Arduino-Logik (Main Controller)**  
   - Verantwortlich für die Hauptlogik und Steuerung des PinBoom-Systems.  
   - Zuständig für die Ansteuerung von Aktoren, die Überwachung von Sensoren und die Ausführung der Betriebsmodi.  

2. **Arduino-Sicherheit (Safety Controller)**  
   - Übernimmt den **Not-Aus-Zyklus** und die **Sicherheitsfreigabe**.  
   - Stellt sicher, dass das System im Fehler- oder Notfall in einen sicheren Zustand versetzt wird.  

---

## 📂 Projektstruktur

```
PinBoom/
│
├── README.md # Projektübersicht
│
├── program-main/ # Logik & Steuerung (Arduino 1)
│ ├── src/
│ │ └── main.ino
│ └── ...
│
└── program-safety/ # Not-Aus & Sicherheitslogik (Arduino 2)
├── src/
│ └── safety.ino
└── ...
```

---

## ⚙️ Hardware
- **Arduino 1**: Hauptcontroller für die Logik und Steuerung
- **Arduino 2**: Sicherheitscontroller für Not-Aus und Freigabe

- Zusätzliche Hardware:
    - Motor
    - induktiver Näherungssensor
    - Taster
    - Not-Aus
    - 2x Arduino
    - Spannungsregler
    - Netzteil 230VAC -> 24VDC
    - 4x Relais
    - Drehzahlregler

---

## 🛠️ Software
- **Arduino IDE** oder PlatformIO
- Programmiersprache: **C++ (Arduino-Sketches)**

### Programme:
- `program-main` → Hauptlogik
- `program-safety` → Sicherheitslogik

---

## 🔒 Sicherheitskonzept
Das System verwendet eine **redundante Steuerung**:

- Wenn der Sicherheitscontroller (Arduino 2) **keine Freigabe** erteilt, bleibt das Hauptsystem gesperrt.
- Der Sicherheits erteilt die Freigabe erst, wenn die **Latenz** zum Hauptcontroller **unter 5ms** liegt und alle **Sicherheitselemente unbetätigt** sind
- Bei Auslösung des **Not-Aus**:
  - Aktoren werden sofort deaktiviert.
  - Der Hauptcontroller erhält ein Sperrsignal.
- Die Latenz zum Hauptcontroller fällt über 5ms / Verbindung zum Hauptcontroller geht verloren
  - Aktoren werden sofort deaktiviert.
  - Der Hauptcontroller sperrt sich selbst, bis die Latenz wieder unter 5ms liegt

---

## ▶️ Installation & Upload
1. **Repository klonen**
    ```bash
    git clone https://github.com/deinname/PinBoom-Control-System.git
    ```
2. **Arduino 1 (Main Controller) flashen**
    - Öffne `program-main/src/main.ino` in der Arduino IDE
    - Wähle den passenden Board-Typ & Port
    - Hochladen
3. **Arduino 2 (Safety Controller) flashen**
    - Öffne `program-safety/src/safety.ino`
    - Hochladen

---
## 🛠️ Verbessungen

  -Drehgeber für genauere Positionierung
  
---

## 📜 Lizenz
Dieses Projekt steht unter der **MIT-Lizenz**

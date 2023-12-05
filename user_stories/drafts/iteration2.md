
## CLI Argumente Parser
- ID: 420
- Beschreibung
    - Als User muss es mir möglich sein verschiedene Parameter und Einstellungen des Programms zu verändern, indem ich CLI Argumente beim Start des Programms übergebe, um den Output des Programms anzupassen zu können, ohne das Programm dafür neu kompilieren zu müssen.
- Akzeptanzkriterium
    - CLI Argumente werden richtig und vollständig geparst. Es gibt eine Hilfe Seite mit --help. Die verschiedenen Argumente funktionieren genau so wie in der Hilfe Seite beschrieben.
- Story Points: 5

## Entfernen von Nick- und Schwankbewegungen aus Scans
- ID: 421
- Beschreibung
    - Als User ist es mir wichtig, dass bei der Erstellung der Karte aus den Frames, Nick- und Schwankbewegungen der Bahn mit beachtet und kompensiert werden, um eine Karte von höherer Genauigkeit zu erhalten.
- Akzeptanzkriterium
    - Die Position der Punkte wird entsprechend der IMU Daten angepasst
- Story Points: 5

## Export zu segmentierten Karten Format
- ID: 4
- Beschreibung
    - Als Nutzer bietet mir das System die Möglichkeit, ausgewählte Scans zu einer Karte zu kombinieren, die das effiziente Zugreifen auf einzelne Segmente der Karte ermöglicht.
- Akzeptanzkriterium
    - Das Untersystem liest die Daten korrekt ein und gibt die zusammengeführte Karte aus.
    - Das Format ermöglicht, durch Unterteilung in Abschnitte, unabhängig von der Gesamtgröße der Karte, einzelne Segmente effizient zu verarbeiten.
- Story Points: 8

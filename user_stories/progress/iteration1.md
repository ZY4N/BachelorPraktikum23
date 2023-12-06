## Einlesen von Daten aus Rosbags
- ID: 0
- Beschreibung
    - Als Nutzer kann ich dem System im Rahmen des Projekts Innotrams entstandene Sensordaten als Rosbags zur Verarbeitung bereitstellen.
- Akzeptanzkriterium
    - Falls alle für die Verarbeitung relevante Daten in dem Rosbag vorhanden sind und sich in der erwarteten Repräsentation befinden, wird die Datei korrekt eingelesen.
    - Ansonsten gibt das Programm einen Fehler aus und terminiert.
- Story Points: 2

## Entfernung dynamischer Objekte
- ID: 1
- Beschreibung
    - Als ein Nutzer, kann ich diesem Untersystem eine beliebige Anzahl von Scans geben, aus denen das Untersystem alle Punkte von Objekten entfernt, die sich zwischen den Scans signifikant bewegt haben.
- Akzeptanzkriterium
    - Alle Punkte von Objekten, die sich zwischen den Scans signifikant bewegt haben, werden entfernt.
    -  Das Untersystem gibt die Scans wieder im Eingabeformat aus.
- Story Points: 3
## Format zur Zwischenspeicherung von Scans
- ID: 2
- Beschreibung
     - Als Nutzer ist es mir möglich, die System-internen Scans als Dateien zu überblicken, und das Format ermöglicht mir das effiziente Laden in andere Untersysteme.
- Akzeptanzkriterium:
    - Alle internen Datenaustausche von Scans zwischen Untersystemen erfolgen in einem Dateiformat.
  - Das Format ermöglicht ein effizientes Laden in alle diese Untersysteme, insbesondere dem dynamischen Objektentferner.
- Story Points: 3

## Distanzfilterung von Punktdaten
- ID: 3
- Beschreibung:
	- Als Nutzer des Programms möchte ich, dass sich das Programm auf die Punkte im für die Bahn relevanten Bereich beschränkt, um die Datenmenge zu verringern und von unwichtigen Details zu abstrahieren.
- Akzeptanzkriterium:
	- Der Benutzer kann eine maximale Distanz angeben. Punkte, die zum Zeitpunkt des Scans weiter als die maximale Distanz vom Lidar entfernt sind, werden nicht im Output berücksichtigt.
- Story Points: 2
    
## Geschwindigkeits Entzerrung
- ID: 4
- Beschreibung:
	- Als Nutzer des Programms möchte ich, dass selbst wenn die Scans bei einer hohen Geschwindigkeit aufgenommen werden, die Scanpunkte angemessen aufbereitet werden.
- Akzeptanzkriterium:
	 - Man kann sichtlich erkennen, dass, wenn die Bahn mit hoher Geschwindigkeit (über 30 km/h) frontal auf ein Objekt zufährt, die Punkte nicht in Fahrtrichtung verschoben sind.
- Story Points: 5 

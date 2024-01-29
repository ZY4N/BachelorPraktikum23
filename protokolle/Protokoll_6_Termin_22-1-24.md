### Review letzter Sprint
- Aktueller Stand der Implementation mithilfe der Projekt-Pitch-Präsentation veranschaulicht
- Demonstration des überarbeiteten Reframers der die Daten in Chunks aufteilt
	- Punkt 0/0 nicht 100 % in der Mitte vom Lui
	- Der Reframer bearbeitet Rosbags in separaten Zeitblöcken und lädt zusätzlich Daten vor und nach jedem Block, um den nötigen Kontext für Splines bereitstellen zu können (und Lücken zu vermeiden)
	- Transformationen und Velocity werden mit Padding geladen
	- Effizienzmessung: 12 Minuten zum Verarbeiten der Daten auf Severins Computer
		- Größter Abschnitt: Laden der Rosbags → Potenzielle Verbesserung durch Multithreading
- Vorstellung von KIT’s Removert
	- Entfernung einer Straßenbahn
	- Artefakte semi-dynamischer Autos sichtbar
	- Effizienz: weniger als 20 Sekunden zur Bearbeitung eines Chunks
	- max. 220 Frames 
	- Nur innerhalb definiertem Bereich generiert
	- Padding auf Blöcken nötig, da Removert Namen gleicher Länge benötigt
		- potenziell Probleme durch unbekannte Höchstmenge

### Weiterer Verlauf
- Entfernung semi-dynamischer Objekte
	- Idee: Entfernung Voxelbasiert → Menschen entfernen mittels Voxeleditor
	- Idee Alexander: Überlebenswahrscheinlichkeit von Voxels anhand Voxeldichte berechnen
		- Verworfen, da auch Basis von Removert etc. → Artefakte durch Bahnen und Taxis, die immer an derselben Stelle stehen
	- Idee: Spline Deadzones einführen
		- Verworfen, da Schilder zu nah an den Splines sind, die nicht entfernt werden dürfen
	- Entfernung semi-dynamischer Objekte könnte zu Fehlern in den statischen Objekten dahinter führen
	- Weitere Überlegungen, wie mit semi-dynamischen Objekte verfahren werden sollte, vonseiten aller noch nötig

### Nächste Iteration
- Removert testen
- Dokumentation von Code
- Tests schreiben
- Potenziell Performance von Reframer erhöhen
	- nicht unbedingt nötig, da Programm auch über Nacht laufen kann
- Überlegungen über Entfernung semi-dynamischer Objekte
	- Was ist Aufwand ärmste Implementierung?
	- Potenziell Voxelbasierten Entferner implementieren, unabhängig davon, welche und wie Voxels schlussendlich markiert werden

### Sonstiges
- Daten
	- potenziell Filter laufend bis Donnerstag → mehr Daten abholen
	- Momentan theoretisch genug Daten, um zu testen
		- mehr Daten immer willkommen
		- potenzielles Bottleneck wegen großer Datenmenge
- Ein Abschnitt bisher nicht kartografiert, da erst später zu Fahrten hinzugefügt wurde
- Splines
	- bisher noch nicht benötigt
	- potenziell irgendwann um Punkte noch gerader zu ziehen
	- potenziell für Custom Editor
- Es ist möglich, auf GitLab Binaries hochzuladen
	- Es ist möglich, Rosbags für die CI Pipeline zum Testen hochzuladen
- Alexander ist ab dem 8.2.24 im Urlaub

#### Nächster Termin 6.2.24 um 9 Uhr in Person

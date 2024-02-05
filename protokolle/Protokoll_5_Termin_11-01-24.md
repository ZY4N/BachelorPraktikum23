Protokoll vom 11.1.24 für den 5. Termin um 10:00
## Besprechung der Ergebnisse der letzten Iteration 

### Reframer Demo
Severin präsentiert den aktuellen stand von Reframer:
- Die Gesamtfunktionalität ist gut:
	- Die Punkte der Testdaten werden gut angepasst.
	- Es wird eine ausführliches Log des Prozesses erstellt.
	- Dem Reframer können nun Optionen übergeben werden (Default-Werte existieren).
	- Es werden Punkte die zu weit vom LIDAR entfernt sind, gelöscht. 
	- Die Performance ist gut (derzeit bei 20min für 130 GB), aber möglicherweise noch optimierbar.
### Removert
Greys demonstriert Removert.
- Die Gesamtfunktionalität ist okay:
	- Generell wurden dynamische Objekte gut entfernt; Menschen und fahrende Busse und Bahnen sind kaum zu sehen.
	- Problem sind bei stehenden Bussen und Bahnen (wie z.B. an Haltestellen) diese hinterlassen große Artefakte am Boden.
	- der Datensatz musste auf 300m um den Lui und auf jedes 3. Frame reduziert um in den Ram(16GB) zu passen
		=> Daten müssen für Removert segmentiert werden

Die Implementierung des Chunkformats würde das Datenmengenproblem lösen. Dies wird das Hauptziel für diese Iteration.
### Test-Pipeline
Leo zeigt unsere Probleme fürs ausführliche Testen auf.
Für gute Tests benötigen wir:
- Dedizierte Testhardware
- Einen Datensatz, der öffentlich zugänglich sein kann.

AG schaut, was er tun kann.
## Miscellaneous
### Spline Informationen
Relevante Daten zu Splines sind im Gitlab-Repository FZD/MAAS/Map zu finden.
- Besonders relevant sind
	 - Die rohen Splinedaten:
		`map/output/map.pkl`
	- Beispiel wie man Python mit der Spline Karte umgeht:
		`map/trammap/map.py`

### Probleme für den AG
- Wir können nicht mit dem Main-Branch mergen.
- VPN- und Silo-Zugriff sind immer noch nicht vorhanden.
- Test-Pipeline
### Plan für die nächsten Iteration
Wir erstellen und implementieren das Chunkformat.
Nächster Termin: Montag, 22. Januar 2024, 9:00 Uhr

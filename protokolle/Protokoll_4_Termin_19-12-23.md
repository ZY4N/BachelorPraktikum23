
# Ergebnisse letzter Iteration
- Arbeit an User Story `ID 6: Entfernen von Nick- und Schwankbewegungen aus Scans` nicht abgeschlossen
	- Im IMU Topic befinden sich keine Rotations Daten
	- Wahrscheinlich wegen Implementations Fehler in [converter.cpp](https://git.rwth-aachen.de/fzd/maas/ros/-/blame/master/src/2_sense/localization/src/converter.cpp#L12)
	- Alexander konnte sich wegen Krankheit noch nicht darum kümmern
	- Urheber des in Frage stehenden Codes schreibt zur Zeit Dissertation und hat nur begrenzt Zeit für Korrekturen
- Entscheidung für Removert (dazu später mehr)
- Argument Parser noch nicht fertig integriert
- Parsen von Lidar Topics ist jetzt Modular
	- Alexander empfiehlt Ibeo Lidar, wegen hoher Komplexität, nicht zu nutzen
- Leos Krankheitsfall (hatte keinen Einfluss auf die Entwicklung)

# Verbesserungsvorschläge für Sprintplanung
- Max spricht Probleme mit Sprintplanung an
	- Sprintplanung dauerte bis weit in Iteration
	- Nimmt viel Zeit von Implementation
- Sprintplanung sollte im Meeting festgelegt werden
	- User Stories **vor** Meeting formuliert werden
	- Beim Meeting nur **Prioritisierung und Akzeptanzkriterien** abklären
- Während Iteration kann bei Problemen Rücksprache stattfinden
# Neue Datensätze
- Alexander gibt Severin Festplatte mit neuen Rosbags
- Stellt klar, dass Daten nicht verloren, verbreitet oder nach dem Projekt bestehen bleiben dürfen
- Die Festplatte enthält 11 Rosbags mit localized Datensätzen
- Diese sollten korrekte Rollwinkel beinhalten
- Stellt Daten von  `/imu` und `/imu/corrected` bereit
- localized Datensätze enthalten neben korrigierten Daten auch alle normalen Rohdaten Topics
- Die korrigierten Positionen wurden orthogonal auf den Schienen Spline projeziert
# Frage nach Genauigkeit von Daten
- GPS sollte keinen Drift haben
- Kovarianz Matrix gibt Genauigkeit an
- Für diese Iteration auf "/tf" Topic verlassen
- Falls Korrektur nötig ist, sollten Schienen Splines Verwendet werden
	- Die Schienensegmente wurden mit sehr hoher Genauigkeit eingescannt
	- bestehen als 3D Splines *irgendwo*
	- Nur Mittelspur, keine Roll Informationen
	- Alexander sucht Splines, findet aber Output nicht
		- Wird nochmal danach schauen
	

# Programm zur Entfernung dynamischer Objekte
- Simon und Greys stellen Optionen vor
	- [Dynablocks](https://github.com/ethz-asl/dynablox)
		- leider Rosbags
	- [Removert](https://github.com/irapkaist/removert)
		- Von KIT für Autos mit LiDAR Scannern 
		- Multi Threaded
		- ganz toll (...)
	- [3DTK Peopleremover](https://github.com/3DTK/3DTK/tree/master/src/peopleremover)
		- ineffizientes Dateienformat
		- Teils Single Threaded Execution
		- Code Qualitäts Probleme
- Alexander's Feedback
	- Removert ist angemessene Wahl
	- KITTI Format ist Industry Standard und kann in Projekt verwendet werden
	- Removert sollte ggf. modular austauschbar sein (z.b.: durch 3DTK pplreomver)
	- Lizenz
		- Removert Lizenz ist nicht besonders wichtig solange Removert nicht angepasst werden muss
		- Projekt muss nicht zwingend EUPL nutzen
		- Entscheidung hat Zeit, da Projekt erstmal intern bleibt
	
# Planung für diese Iteration
- Für diese Iteration liegt der Fokus auf der Entfernung dynamischer Objekte
- Kann vorgezogen werden, da dies auch ohne perfekt korrigierte Datensätze möglich ist
- Datensätze können in darauf folgenden Iterationen noch korrigiert werden.
- CI Pipeline wird ausgearbeitet
- Argparser wird fertig integriert
- Implementation von Exporter zu KITTI Format (bereits implementiert)

# Frage nach (CI-Pipeline) Hardware
- Frage von Team: Auf welcher Hardware läuft CI Pipeline
	- Er findet noch raus auf was es läuft
	- Wenn es darauf in angemessener Zeit läuft, läuft es auch auf Ziel Hardware
	- Docker wäre gut
	- Leo setzt sich mit CI Pipeline auseinander
	- Bitte Docker erstellen
	- Zur Orientierung Alexanders Arbeits PC hat
		- Eine Ryzen 12 Kern CPU
		- 16GB RAM
		- eine RTX 2070
	- CUDA kann erwartet werden, OpenCL wäre aber besser

# Data Vault
- Alexander fragt ob Emails mit OpenVPN Zugangsdaten (an Greys und Severin) angekommen sind
- Greys und Severin meinen keine Emails bekommen zu haben
- Alexander möchte nochmal nachfragen was daraus wird
- (Zugriff auf Server wäre zur Zeit selbst mit OpenVPN Zugangsdaten noch nicht möglich)

# Kleinigkeiten
- Wegen Bugs mit Email Program wurden Termin Absprachen fälschlicherweise mehrfach verschickt
- Auf der Messe können Punkt Daten grundsätzlich gezeigt werden aber Kamera Daten nicht
# Nächster Termin
-  4.1.2024 um 10 Uhr über Zoom (weil Räume nicht geheizt werden)

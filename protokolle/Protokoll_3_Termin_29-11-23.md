### Review letzter Sprint
- Es war nicht möglich, in den Projektabschnitten Map, Map Webserver und Ros Code zu sehen 
	- Lösung durch Änderung des Status auf Gitlap von Guest zu Reporter
- Code in proof_of_concept Branch
- Gute Ergebnisse in allen Bereichen außer dem Peopleremover
		- Theoretisch Verarbeitung von Scans mehrerer Sensoren möglich, wenn auch noch nicht getestet
- Probleme des Peopleremovers beinhalteten, nicht terminieren und falsche Ergebnisse
		- Möglicherweise nötig, mehr Daten zu einer Position zu geben
		- Frage zu weiterem Vorgehen, ob weiter an dem Peopleremover gearbeitet werden soll, um diesen benutzbar zu machen und ein weiteres Datenformat einzubinden

### Reaktion AG zu weiterem Verlauf
- Fokus für weiteres Vorgehen erst mal auf Erstellen einer sauberen 3D Karte, in der die dynamischen Objekte noch nicht rausgefiltert werden
	- kein Verziehen in 3 Dimensionen / Spiralen
	- danach erst dynamische und semidynamische Objekte rausfiltern
- Nutzung von Slams 
	- Verweis auf hdl_graph_slam
		- nimmt allerdings keine tf Frames
	- Vectorslams 
			- Augenmerk auf Ringschlüsse/loop closure
	- Achtung, da floor-detection für Straßenbahnen ungeeignet ist und viele Slams dieses über ranslack benutzen
	- Nutzung von kamerabasierten Slams potenziell unnötig, allerdings Überlegung als zusätzliche Datenquelle
- Potenzielle Nutzung von Dynoblox zur Entfernung dynamischer Objekte
	- für Echtzeit gedacht
	- Paper dazu wollte AG in Matrix veröffentlichen
- Anpassung, dass Lidarscans von weiteren Positionen verarbeitet werden können
	- Bezug auf Verarbeitung mehrerer Scans von jetzigen festen Positionen an der InnoTram
- Datenspeicherung potenziell in Junk Datei Format der point cloud
	- AG sichtet Daten über Mashlap
- Potenzielle Nutzung von NavSatFix Massages
	- Magnetdaten sind potenziell leicht schief

### Weitere Informationen und Anmerkungen
- Auch weiterhin noch kein Zugriff auf Daten-Silo, wobei schon 2 VPM-Accounts eingerichtet (Grace & Severin)
- Auch in Zukunft Verwendung von Rosbags
- Laufzeit muss nicht schneller sein als Bahn Daten sammelt, da voraussichtlich nicht alle Daten verwendet werden
- Sensorpositionen
	- Sensorposition ist auf Höhe der Schienenoberkante auf Höhe des ersten Drehmoments
	- GPS liegt genau zwischen den 2 Schienen direkt über dem Sensor
		- Genauigkeit wird angegeben über Schätzwert und genausten Wert und liegt im cm Bereich


### Aufgaben für nächsten Sprint
- (Graphenbasierte) Slams finden und auszuprobieren, um über längere Strecken saubere Karten zu bekommen
- Konsistente 3D Karte erstellen
- Alles zueinander mappen, filtern und bearbeiten mithilfe von point cloud library
- Wenn die Bahn in Haltestellen stehen bleibt Punkte filtern

#### nächster Termin 13.12.23 9 Uhr gleicher Ort
#### darauf folgender Termin 3.1.24 Uhr per Zoomcall
 - Einladungslink wurde in Matrix Chat geschickt
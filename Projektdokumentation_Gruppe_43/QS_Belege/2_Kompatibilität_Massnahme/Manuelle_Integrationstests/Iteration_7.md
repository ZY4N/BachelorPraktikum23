- Durchgeführt am #TODO um #TODO
- Durchgeführt von #TODO 
- Getestete Funktionalitäten: 
## Angepasster Testplan
1. Compilen des Scan Combiners
	- **Erwartetes Ergebnis:** Programm kompiliert fehlerfrei. 
2. Ausführung des Scan Combiners mit dem Ausgabe Format UOS und dem Metadaten Format JSON. 
	- Der Input sind beliebige, vom Arbeitgeber zur Verfügung gestellte, Rosbags, die gemeinsam eine Zeitspanne von mindestens 30 Minuten abdecken.
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im UOS-Format und Metadaten im JSON-Format 
3. Überprüfung der JSON Datei durch Python-Script
	- **Erwartetes Ergebnis:** Phython-Script liefert zurück das Datei fehlerfrei gelsen werde konnten.
4. Ausführung des People Removers mit den eben erzeugten Punkt- und Positionsdaten im UOS-Format als Eingabe
	- Ab dem Punkt an dem die Daten in Zellen aufgeteil sind, wird stichprobenartig eine Zelle ausgewählt.
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im UOS-Format und Metadaten im JSON-Format. Bei der visuellen Besichtigung sind alle punkte auf der entsprechenden Checkliste erfüllt.
5. Überprüfung der JSON Datei durch Python-Script
	- **Erwartetes Ergebnis:** Phython-Script liefert zurück das Datei fehlerfrei gelsen werde konnten.
6. Überprüfen der Ordnerstruktur für die Zellaufteilung
	- **Erwartetes Ergebnis:** Alle Punkte der Ordnerstruktur (Zellen)-Checkliste sind erfüllt.
7. Ausführung des Scan Combiners mit dem Ausgabe Format KITTI und dem Metadaten Format JSON
	- Der Input sind beliebige, vom Arbeitgeber zur Verfügung gestellte, Rosbags, die gemeinsam eine Zeitspanne von mindestens 30 Minuten abdecken.
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im KITTI-Format und Metadaten im JSON-Format
8. Überprüfung der JSON Datei durch Python-Script
	- **Erwartetes Ergebnis:** Phython-Script liefert zurück das Datei fehlerfrei gelsen werde konnten.
9. Ausführung des Removert mit den eben erzeugten Punkt- und Positionsdaten im KITTI-Format als Eingabe
	- Ab dem Punkt an dem die Daten in Zellen aufgeteilt sind, wird stichprobenartig eine Zelle ausgewählt.
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im KITTI-Format und Metadaten im JSON-Format. Bei der visuellen Besichtigung sind alle punkte auf der entsprechenden Checkliste erfüllt.
10. Überprüfen der Ordnerstruktur für die Zellaufteilung
	- **Erwartetes Ergebnis:** Alle Punkte der Ordnerstruktur (Zellen)-Checkliste sind erfüllt.
11. Compilen des kitti2pcl-Programms
	- **Erwartetes Ergebnis:** Programm kompiliert fehlerfrei.
12. Einlesen der KITTI Ausgabe mit dem kitti2pcl Programm
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im PCL-Format
13. Visuelles Überprüfen der Ausgabe des kitti2pcl Programms
	- Bei der visuellen überprüfung  wird die "combined.pcl"-Datei, die die Punkte aus allen angegebenen Zellen kombiniert, benutzt.
	- **Erwartetes Ergebnis:** Alle Punkte der visuelle Überprüfung-Checkliste sind erfüllt.



### Compilen des Scan Combioners
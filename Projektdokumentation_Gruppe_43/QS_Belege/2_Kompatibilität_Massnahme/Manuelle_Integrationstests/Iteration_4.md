- Durchgeführt am #TODO um #TODO
- Durchgeführt von #TODO 
- Getestete Funktionalitäten: 
## Angepasster Testplan
1. Compilen des Scan Combiners
	- **Erwartetes Ergebnis:** Programm kompiliert fehlerfrei.
2. Ausführung des Scan Combiners mit dem Ausgabe Format UOS
	- Der Input sind beliebige, vom Arbeitgeber zur Verfügung gestellte, Rosbags, die gemeinsam eine Zeitspanne von mindestens 30 Minuten abdecken.
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im UOS-Format
3. Ausführung des People Removers mit den eben erzeugten Punkt- und Positionsdaten im UOS-Format als Eingabe
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im UOS-Format. Bei der visuellen Besichtigung sind alle punkte auf der entsprechenden Checkliste erfüllt.
4. Ausführung des Scan Combiners mit dem Ausgabe Format KITTI
	- Der Input sind beliebige, vom Arbeitgeber zur Verfügung gestellte, Rosbags, die gemeinsam eine Zeitspanne von mindestens 30 Minuten abdecken.
	- Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im KITTI-Format
5. Ausführung des Removert mit den eben erzeugten Punkt- und Positionsdaten im KITTI-Format als Eingabe
	- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im KITTI-Format. Bei der visuellen Besichtigung sind alle punkte auf der entsprechenden Checkliste erfüllt.
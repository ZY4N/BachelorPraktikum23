##### 1. Compilen des Scan Combiners
- **Erwartetes Ergebnis:** Programm kompiliert fehlerfrei.
##### 2. Ausführung des Scan Combiners mit dem Ausgabe Format UOS und dem Metadaten Format JSON. 
- Der Input sind beliebige, vom Arbeitgeber zur Verfügung gestellte, Rosbags, die gemeinsam eine Zeitspanne von mindestens 30 Minuten abdecken.
- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im UOS-Format und Metadaten im JSON-Format
##### 3. Überprüfung der JSON Datei durch Python-Script
- **Erwartetes Ergebnis:** Phython-Script liefert zurück das Datei fehlerfrei gelsen werde konnten.
#####  4. Ausführung des People Removers mit den eben erzeugten Punkt- und Positionsdaten im UOS-Format als Eingabe
- Ab dem Punkt an dem die Daten in Zellen aufgeteil sind, wird stichprobenartig eine Zelle ausgewählt.
- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im UOS-Format und Metadaten im JSON-Format. Bei der visuellen Besichtigung sind alle punkte auf der entsprechenden Checkliste erfüllt.
##### 5. Überprüfung der JSON Datei durch Python-Script
- **Erwartetes Ergebnis:** Phython-Script liefert zurück das Datei fehlerfrei gelsen werde konnten.
##### 6. Überprüfen der Ordnerstruktur für die Zellaufteilung
- **Erwartetes Ergebnis:** Alle Punkte der Ordnerstruktur (Zellen)-Checkliste sind erfüllt.
##### 7. Ausführung des Scan Combiners mit dem Ausgabe Format KITTI und dem Metadaten Format JSON. 
- Der Input sind beliebige, vom Arbeitgeber zur Verfügung gestellte, Rosbags, die gemeinsam eine Zeitspanne von mindestens 30 Minuten abdecken.
- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im UOS-Format und Metadaten im JSON-Format
##### 8. Überprüfung der JSON Datei durch Python-Script
- **Erwartetes Ergebnis:** Phython-Script liefert zurück das Datei fehlerfrei gelsen werde konnten.
##### 9. Ausführung des Removert mit den eben erzeugten Punkt- und Positionsdaten im KITTI-Format als Eingabe
- Ab dem Punkt an dem die Daten in Zellen aufgeteil sind, wird stichprobenartig eine Zelle ausgewählt.
- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im KITTI-Format und Metadaten im JSON-Format. Bei der visuellen Besichtigung sind alle punkte auf der entsprechenden Checkliste erfüllt.
##### 10. Überprüfen der Ordnerstruktur für die Zellaufteilung
- **Erwartetes Ergebnis:** Alle Punkte der Ordnerstruktur (Zellen)-Checkliste sind erfüllt.
#### 11. Compilen des kitti2pcl-Programms
- **Erwartetes Ergebnis:** Programm kompiliert fehlerfrei.
#### 12. Einlesen der KITTI ausgabe mit dem kitti2pcl Programm
- **Erwartetes Ergebnis:** Programm wird fehlerfrei ausgeführt und liefert den gewünschten Output im PCL-Format
#### 13. Visuelles Überprüfen der Ausgabe des kitti2pcl Programms
- Bei der visuellen überprüfung  wird die "combined.pcl"-Datei, die die Punkte aus allen angegebenen Zellen kombiniert, benutzt.
- **Erwartetes Ergebnis:** Alle Punkte der visuelle Überprüfung-Checkliste sind erfüllt.

##### Getestete Funktionalitäten:
- **Scan Combiner:** Einlesen der Rosbags, Ausgabe der Punkte im UOS-Format, Ausgabe der Punkte im KITTI-Format, Ausgabe der Metadaten im JSON-Format, Ausgabe aufgeteilt in Zellen (umgesetzt durch Ordnerstruktur)
- **kitti2pcl:** Einlesen des KITTI-Formats, Einlesen mehrerer Zellen aus einem Ordner, Ausgabe der Punkte im PCL-Format, Kombinieren mehrer

### Textuell
Zuerst müssen Sicherheitshalber die Unit Tests Kompiliert und Durchgeführt werden. Dann muss das Hauptprogramm einmal jeweils mit allen möglichen Ausgabeformaten auf unbearbeiteten Rosbags ausgeführt werden. Die Rosbags müssen dabei eine Fahrzeit von mindestens 40 Minuten abdecken. Alle ausgegebenen Daten müssen überprüft werden indem sie von einem Programm eingelesen werden, dass das entsprechende Format als Eingabe akzeptiert. Im Speziellen wurde für das UOS-Format der People Remover von 3DTK, für das KITTI-Format der Removert von #TODO und für das JSON-Format ein Python Script welches die in Python integriete JSON-Libary verwendet. 

### Checkliste für die Ordnerstruktur (Zellen)
- [ ] Im Angegebenen Order befinden sich nur Ordner. Diese sind nach dem Folgenden Schema benannt: chunk\<x\>\_\<y\>
- [ ] Stichpunktartige Überprüfung einem Zellordner: In dem Zellordner befinden sich sich die Punktdaten für einen Chunk, sowie eine meta.json-Datei mit den dazugehörigen Metadaten
- [ ] Die Ränder der Zelle sind in der visuellen Überprüfung klar zu erkennen (Bei einer Zelle am Rand der Aufnahme entsprechend weniger)

### Chechliste für die visuelle Überprüfung
- [ ] Grobe Strukturen statischer Objekte sind klar zu Erkennen 
- [ ] Keine deutlich sichtbare Verschlechterung der Qualität im Vergleich zum letzten Scan (zum Beispiel "dicke" des Bodens)
- [ ] Kontinuierliches Bild (keine Sichtbaren Schnitte, Stufen wo keine hin gehören)

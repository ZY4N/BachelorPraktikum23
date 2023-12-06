
## CLI Argumente Parser
- ID: 695
- Beschreibung
	- Als User muss es mir möglich sein unten aufgelistete Parameter und Einstellungen des Programms zu verändern, indem ich CLI Argumente beim Start des Programms übergebe, um den Output des Programms anzupassen zu können, ohne das Programm dafür neu kompilieren zu müssen.
- Akzeptanzkriterium
	- CLI Argumente werden richtig und vollständig geparst. Es gibt eine Hilfe Seite mit --help. Die verschiedenen Argumente funktionieren genau so wie in der Hilfe Seite beschrieben.
	- Konkrete Angaben sollen möglich sein:
		- Angabe beliebiger Anzahl an rosbag-Dateinamen als Eingabe für das Programm.
		- Angabe eines Ausgabe Ordners
		- Angabe ein oder mehrerer Lidar-Sensor-Topic
		- Ein Begin- und ein Endzeitpunkt
		- Maximal zugelassene radiale Distanz der Punkte vom Lidar-Sensor
		- Maximal zugelassene periphere Distanz der Punkte vom Lidar-Sensor
		- Maximale, auf einmal verarbeite Zeitblockgröße.
		- Maximale Abweichung zwischen Scanposition und eigenen Scans
		- Anzahl an verwendeten Threads
- Story Points: 5

## Entfernen von Nick- und Schwankbewegungen aus Scans
- ID: 696
- Beschreibung
	- Als User ist es mir wichtig, dass bei der Erstellung der Karte aus den Frames, Nick- und Schwankbewegungen der Bahn mit beachtet und kompensiert werden, um eine Karte von höherer Genauigkeit zu erhalten.
- Akzeptanzkriterium
	- Die Position der Punkte wird entsprechend der IMU Daten angepasst. Wenn die IMU zum Beispiel eine Neigung von x° in eine Richtung erkennt, werden die Punkte, die zu diesem Zeitpunkt aufgenommen wurden, um x° um die Sensorposition in die Gegenrichtung gedreht.
- Story Points: 8

## Export zu segmentierten Karten Format
- ID: 697
- Beschreibung
	- Als Nutzer bietet mir das System die Möglichkeit, ausgewählte Scans zu einer Karte zu kombinieren, die das effiziente Zugreifen auf einzelne Segmente der Karte ermöglicht.
- Akzeptanzkriterium
	- Bei einem Fehler wird eine aussagekräftige Fehlermeldung ausgegeben, das Programm terminiert und es werden keine Daten falsch verändert.
	- Das Untersystem liest die Daten korrekt ein und gibt die zusammengeführte Karte aus.
	- Das Format ermöglicht, durch Unterteilung in Abschnitte, unabhängig von der Gesamtgröße der Karte, einzelne Segmente effizient auslesen zu können.
	- Hierbei bedeutet "effizient", dass auf einem PC oder Server, der nach 2013 hergestellt wurde, mit minimal 16Gb Arbeitsspeicher, das Laden eines Segmentes nicht mehr als doppelt so lange dauert, wie die Daten von der Festplatte in den Arbeitsspeicher zu laden.
- Story Points: 8

# Viability von Pplremover evaluaten und ggf. Alternative finden
- ID: 698
- Beschreibung

## Datenformat entwickeln
- ID: 699
- Beschreibung
	- Als Nutzer benötige ich ein internes Zwischenformat, dass speziell auf die Problemstellung des Erstellens einer dynamischen Straßenkarte angepasst ist, damit die anfallenden Daten mit maximaler Effizienz übertragen und gespeichert werden können.
- Akzeptanzkriterium
	- Das Format wird so geschrieben, dass es die anfallenden Daten in diesem kompakter, übersichtlicher und effizienter übertragen und abspeichern kann. Dieses Format wird als internes Format benutzt, wie beschrieben in der User Story ID 2.
- Story Points: 8

## Internes Datenformat in Peopleremover einlesen
- ID: 6910
- Beschreibung
	- Als Nutzer möchte ich die Möglichkeit haben, das auf Effizienz ausgelegte interne Datenformat mit dem Peopleremover nutzen zu können.
- Akzeptanz
	- der Peopleremover liest Daten aus dem internen Dateienformat korrekt ein.
	- der Peopleremover schreibt Daten in das interne Datenformat aus.
- Story Points 8
## Effizientes Verarbeiten von Scans aus vielen verschiedenen Positionen
- ID: 6911
- Beschreibung
	- Wenn ich dem People Remover Lidar Frames aus vielen verschiedenen Positionen gebe, kann dieser diese Frames problemfrei und effizient verarbeiten.
- Akzeptanz
	- Die Zeitkomplexität des Peopleremovers steigt nur um O(n) mit der Anzahl der Lidar Frames.
- Story Points 8
- 
## Serializer für internes Datenformat
- ID: 6912
- Beschreibung
	- Als Nutzer kann ich meine LIDAR Frame Daten, nach der Vorbearbeitung, als das durch ID:2 definierte  Datenformat speichern. Das speichern der Daten geschieht möglichst schnell und ich kann einstellen wie viele Threads genutzt werden sollen um das speichern zu beschleunigen. 
- Akzeptanzkriterium
	- Die Daten werde so wie spezifiziert gespeichert. Es werden alle Punkte korrekt und ohne Verlust gespeichert. Alle gewünschten/möglichen Threads werden bestmöglich ausgenutzt. 
- Story Points: 5
- 
## Parser für internes Datenformat
- ID: 6913
- Beschreibung
	- Als Nutzer, möchte ich, dass die benötigte Informationen aus Lidar Frame Daten automatisch eingelesen werden
- Akzeptanzkriterium
	- Die Daten werden korrekt und vollständig geparst.
- Story Points: 5


## Entfernung dynamischer Objekte
- ID: 1
- Beschreibung
    - Als ein Nutzer, kann ich diesem Untersystem eine beliebige Anzahl von Scans geben, aus denen das Untersystem alle Punkte von Objekten entfernt, die sich zwischen den Scans signifikant bewegt haben.
- Akzeptanzkriterium
    - Alle Punkte von Objekten, die sich zwischen den Scans signifikant bewegt haben, werden entfernt.
    -  Das Untersystem gibt die Scans wieder im Eingabeformat aus.
- Story Points: 21
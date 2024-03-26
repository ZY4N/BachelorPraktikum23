# Statusmeeting Protokolle Iteration 7
---

## Checkliste 1 zu User Storie 23. PCL Converter 



## Statusmeeting 1 zu User Story 23. PCL Converter 
- Datum: 11.02.2024 10:00 Uhr - 10:30 Uhr
- Entwickler\*innen: Greys Fankyeyeva
- Code Buddy: Alicia Gleichmann
- Kontext:
	- Rechtschreibfehler
- Beispiel:
	- kitty2pcd Projektname
- Diagnose:
	-  Eigenname falsch geschrieben
- Aktion:
	- kitti einsetzen
- Sonstiges:
	- Bisherige Dokumentation und Implementation ist korrekt bis auf den Eigennamen-Fehler
		- Direkt korrigiert
	- Code noch nicht sonderlich weit, was da ist besprochen
- Nächstes Meeting am: 18.02.2024 um 10:00 Uhr

---

## Checkliste 1 zu User Storie 24. Programm parallelisieren 



## Statusmeeting 1 zu User Story 24. Programm parallelisieren 
- Datum: 11.02.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Greys Fankyeyeva
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	-  -
- Aktion:
	- -
- Sonstiges:
	- System läuft schneller durch
	- Parallelisierung des Auslesens der Rosbags noch nicht abgeschlossen
	- Keine Lesbarkeitsfehler in Dokumentation oder Code
- Nächstes Meeting am: 18.02.2024 um 12:30 Uhr

---

## Checkliste 1 zu User Storie 25. Unterstützung weiterer LiDAR-Sensoren 



## Statusmeeting 1 zu User Story 25. Unterstützung weiterer LiDAR-Sensoren 
- Datum: 12.02.2024 15:30 Uhr - 16:00 Uhr
- Entwickler\*innen: Simon Riese, Severin Pelikan
- Code Buddy: Greys Fankyeyeva
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Keine Lesbarkeitsfehler in Dokumentation oder Code
	- Severin hat seinen Teil schon fertig, Simon macht seinem Teil in der zweiten Hälfte der Iteration
- Nächstes Meeting am: 19.02.2024 um 15:30 Uhr

---

## Checkliste 1 zu User Storie 26. Erweiterung der Metadaten um Sensortypen und Rosbag-Topic 



## Statusmeeting 1 zu User Story 26. Erweiterung der Metadaten um Sensortypen und Rosbag-Topic 
- Datum: 11.02.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Simon Riese
- Code Buddy: Leonhard Steinecke
- Kontext:
	- Logikoperator nicht ausgeschrieben
- Beispiel:
	- ! statt not in metadata_jason.hpp
- Diagnose:
	- Schlechter lesbar
- Aktion:
	- Austauschen
- Sonstiges:
	- Lesbarkeitsanforderungen sind erfüllt für den jetzigen Stand der Implementation
	- Kurz noch mal angesprochen, wo in die Metadaten die Rosbag-Topics geschrieben werden sollen
- Nächstes Meeting am: 18.02.2024 um 12:30 Uhr

---

## Statusmeeting 1 zu User Story 27. Erstellung von Testdatensätzen 
- Datum: 11.02.2024 13:30 Uhr - 14:15 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Simon Riese
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Da kein Code oder Dokumentation oder Text vorhanden ist, ist Lesbarkeit nicht von Bedarf
	- Rosbag gefunden, der einen interessanten Output liefert
	- Demonstration des geplanten Outputs
	- Zuschneiden des Rosbags zu einem kleineren Zeitabschnitt und Herausschneiden von Daten, die zu Problemen mit dem Datenschutz führen könnten
		- nur notwendige Daten zum Ausführen des Programms beibehalten 
- Nächstes Meeting am: 18.02.2024 um 13:30 Uhr

---

## Checkliste 1 zu User Storie 28. Dynamisches Anpassen des LiDAR-Topics und LiDAR-Sensortyps über CLI



## Checkliste 1 zu User Storie 29. Dynamisches Anpassen der Anzahl der verwendeten Threads über CLI



## Statusmeeting 1 zu User Story 28. Dynamisches Anpassen des LiDAR-Topics und LiDAR-Sensortyps über CLI, 29. Dynamisches Anpassen der Anzahl der verwendeten Threads über CLI und 30. Hinzufügen eines "Help"-Kommandos
- Datum: 11.02.2024 15:00 Uhr - 15:30 Uhr
- Entwickler\*innen: Alicia Gleichmann
- Code Buddy: Severin Pelikan
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Umsetzung der US 28 und 29 wie alle anderen Parameter auch -> keine Lesbarkeitsfehler
	- US 28 und 29 abgeschlossen 
		- Tests gehen durch
	- US 30 noch nicht begonnen
- Nächstes Meeting am: 18.02.2024 um 15:00 Uhr

---

## Checkliste 2 zu User Storie 23. PCL Converter 



## Statusmeeting 2 zu User Story 23. PCL Converter 
- Datum: 18.02.2024 10:00 Uhr - 10:45 Uhr
- Entwickler\*innen: Greys Fankyeyeva
- Code Buddy: Alicia Gleichmann
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- In der Checkliste alles abgehakt
	- Alle Tests gehen durch
	- Demonstration eines pcl Viewer Angewandt an konvertierte kitti Daten und Vergleich der Ausgabe


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 2 zu User Storie 24. Programm parallelisieren 



## Statusmeeting 2 zu User Story 24. Programm parallelisieren 
- Datum: 18.02.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Greys Fankyeyeva
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Checklist Punkte alle abgehackt 
	- Demonstration der CPU Auslastung


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 2 zu User Storie 25. Unterstützung weiterer LiDAR-Sensoren 



## Statusmeeting 2 zu User Story 25. Unterstützung weiterer LiDAR-Sensoren 
- Datum: 19.02.2024 15:30 Uhr - 16:00 Uhr
- Entwickler\*innen: Simon Riese, Severin Pelikan
- Code Buddy: Greys Fankyeyeva
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Keine Lesbarkeitsfehler in Dokumentation oder Code
	- Besprechung der Implementation


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 1 zu User Storie 26. Erweiterung der Metadaten um Sensortypen und Rosbag-Topic 



## Statusmeeting 2 zu User Story 26. Erweiterung der Metadaten um Sensortypen und Rosbag-Topic 
- Datum: 18.02.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Simon Riese
- Code Buddy: Leonhard Steinecke
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Keine Probleme im Code oder in der Dokumentation
	- Code kurz besprochen
	- Alle Tests laufen durch


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Statusmeeting 2 zu User Story 27. Erstellung von Testdatensätzen 
- Datum: 18.02.2024 13:30 Uhr - 14:15 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Simon Riese
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Testdatensatz ist richtig benannt 
	- Läuft durch das Programm und der Output sieht gut aus
		- Demo, wie das Repo geladen wird und mit dem Testdatensatz durchläuft


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 1 zu User Storie 30. Hinzufügen eines "Help"-Kommandos



## Statusmeeting 2 zu User Story 30. Hinzufügen eines "Help"-Kommandos
- Datum: 18.02.2024 15:00 Uhr - 15:45 Uhr
- Entwickler\*innen: Alicia Gleichmann
- Code Buddy: Severin Pelikan
- [x] alle besprochenen Änderungen wurden umgesetzt
- Kontext:
	- Einrücken der Beschreibung und Standardwerte in der Help Ausgabe
- Beispiel:
	- max_scan_position_deviation Beschreibung Standardwert
	  max_radial_distance Beschreibung Standardwert
- Diagnose:
	- Die Beschreibungen und Standardwerte sind schlechter zu erkennen
- Aktion: 
	- Beschreibungen und Standardwerte so einrücken, sodass alle auf einer Höhe sind
- Sonstiges: 
	- Einrücken der Ausgabe von Help passt zu keinem Punkt in der Checkliste, macht es dennoch lesbarer
	- Direkt umgesetzt
	- Restliche Dokumentation und Implementation sind Lesbar


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 18.02.2024
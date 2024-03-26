# Statusmeeting Protokolle Iteration 3
---

## Checkliste 1 zu User Storie 0. Einlese-Option für Rosbag-Dateien



## Statusmeeting 1 zu User Story 0. Einlese-Option für Rosbag-Dateien
- Datum: 07.12.2023 12:30Uhr - 13:00 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Severin Pelikan
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
	- Tests laufen durch, Vorzeichenfehler
	- Rest des Codes hat sich nicht mehr verändert
	- Dementsprechend keine Weiteren Statusmeetings von Nöten

---

## Checkliste 1 zu User Storie 3. Integration von dynamischem Logging-System


## Checkliste 1 zu User Storie 6. Verringerung von Aufnahmetransformationen



## Statusmeeting 1 zu User Story 3. Integration von dynamischem Logging-System und 6. Verringerung von Aufnahmetransformationen
- Datum: 08.12.2023 16:00 Uhr - 18:15 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Ersatz durch Alicia Gleichmann
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- Dokumentation teils noch unvollständig
- Beispiel:
	- eig. überall
- Diagnose:
	- Dokumentation ist wichtig fürs Codeverständnis
- Aktion:
	- Dokumentation fertig schreiben
- Sonstiges:
	- Leonhard Steinecke wurde krank, deshalb ist Alicia Gleichmann Ersatz Code Buddy
	- Übrigen Logger Level wurden integriert und vorgeführt
		- keine Lesbarkeitsfehler im Code und Tests laufen durch
		- Demo der verschiedenen Logger Level
		- Dementsprechend keine weiteren Statusmeetings mehr notwendig
	- Verringerung der Aufnahmetransformationen
		- Implementation fast fertig, Doku und Tests fehlen noch
		- Vorhandene Dokumentation scheint Richtig, ist aber auch teils noch mehr stichpunktartig als Fließtext
- Nächstes Meeting am: 15.12.2023 um 16:00 Uhr

---

## Checkliste 1 zu User Storie 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI



## Statusmeeting 1 zu User Story 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI
- Datum: 09.12.2023 12:30 Uhr - 13:15 Uhr
- Entwickler\*innen: Alicia Gleichmann, Severin Pelikan
- Code Buddy: Simon Riese
- Kontext:
	- Dokumentation noch unvollständig
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- fertig Dokumentieren
- Sonstiges:
	- arx Parser vollständig implementiert, Dokumentation noch unvollständig
	- Was an Dokumentation schon da ist, sieht gut aus
	- Kompiliert bei Severin, aber nicht bei Alicia
		- Herausfinden warum
- Nächstes Meeting am: 16.12.2023 um 12:30 Uhr

---

## Checkliste 1 zu User Storie 6. Verringerung von Aufnahmetransformationen



## Statusmeeting 2 zu User Story 6. Verringerung von Aufnahmetransformationen
- Datum: 15.12.2023 16:00 Uhr - 16:30 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Ersatz durch Alicia Gleichmann
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
	- Leonhard Steinecke ist krank, deshalb ist Alicia Gleichmann Ersatz Code Buddy
	- Tests laufen durch
	- Grob Änderungen noch mal besprochen
	- alle Punkte der Checkliste konnten abgehakt werden


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 1 zu User Storie 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI



## Statusmeeting 2 zu User Story 7. Dynamisches Anpassen von Ein- und Ausgabepfaden über CLI
- Datum: 16.12.2023 12:30 Uhr - 13:30 Uhr
- Entwickler\*innen: Alicia Gleichmann, Severin Pelikan
- Code Buddy: Simon Riese
- [x] alle besprochenen Änderungen wurden umgesetzt 
- Kontext:
	- Flag Identifier sind nicht passend gewählt
- Beispiel:
	- --input und -i
- Diagnose:
	- Da Input und Output immer angegeben werden müssen und der Input aus mehreren Rosbags bestehen kann, sollten diese über die positional Arguments angegeben werden
- Aktion:
	- Input Pfade über positional Arguments angeben
- Sonstiges:
	- Hatte nicht kompiliert, weil Alicia gcc 10 und nicht 11 nutzt, deshalb andere Implementation von Span was zu Problemen geführt hat
		- Höchst mögliche Version in Ubuntu 20, deshalb Code angepasst 
	- Input über Positional Arguments angeben im Meeting umgesetzt

Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 16.12.2023
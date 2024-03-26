
# Statusmeeting Protokolle Iteration 4
---

## Checkliste 1 zu User Storie 8. Entfernen von Nick- und Schwankbewegungen aus Scans



## Statusmeeting 1 zu User Story 8. Entfernen von Nick- und Schwankbewegungen aus Scans
- Datum: 29.12.2023 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Severin Pelikan
- Code Buddy: Leonhard Steinecke
- Kontext:
	- -
- Beispiel:
	- -
- Diagnose:
	- -
- Aktion:
	- -
- Sonstiges:
	- Passt alles so weit schon geschrieben
	- Dokumentation bei schon implementierten Teilen großteils fertig und korrekt
	- Noch fertig dokumentieren, aber da erst Zwischenstand ok
- Nächstes Meeting am: 06.01.2024 um 12:30 Uhr

---

## Checkliste 1 zu User Storie 9. Integration von Removert in Scan Combiner



## Statusmeeting 1 zu User Story 9. Integration von Removert in Scan Combiner
- Datum: 29.12.2023 10:00 Uhr - 10:45 Uhr
- Entwickler\*innen: Simon Riese
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
	- Umsetzung bis jetzt sehr ähnlich zu User Story 4, keine Fehler
	- Frage zu Kitti Format noch mal nachgeschaut bei KIT wegen Transformationsspeicherung in einem extra Ordner
- Nächstes Meeting am: 06.01.2024 um 10:00 Uhr

---

## Statusmeeting 1 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 29.12.2023 15:00 Uhr - 15:15 Uhr
- Entwickler\*innen: Severin Pelikan, Greys Fankyeyeva
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
	- Removert wurde heruntergeladen
	- Angefangen den externen Testdatensatz auszuprobieren, scheint bisher gut
- Nächstes Meeting am: 07.01.2024 um 12:30 Uhr

---

## Checkliste 1 zu User Storie 11. Docker integration für Zielsystem 



## Statusmeeting 1 zu User Story 11. Docker integration für Zielsystem 
- Datum: 29.12.2023 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Leonhard Steinecke
- Code Buddy: Alicia Gleichmann
- Kontext:
	- Dokumentation in Fließtext
- Beispiel:
	- -
- Diagnose:
	- Fließtext 
- Aktion:
	- Stichpunkte Ausformulieren
- Sonstiges: 
	- kein C++ Code, deshalb mussten die spezifischen C++ Code Abschnitte in der Checkliste überspungen werden (gilt auch für zweites Statusmeeting)
	- Sieht bis jetzt gut aus 
	- Dokumentation ist bisher nur stichpunktartig, aber scheint korrekt
- Nächstes Meeting am: 06.01.2024 um 14:00 Uhr

---

## Checkliste 1 zu User Storie 12. Dynamisches Anpassen des Ausgabeformats über CLI



## Checkliste 1 zu User Storie 14. Anpassung der Arbeitsspeicherauslastung über CLI



## Statusmeeting 1 zu User Story 12. Dynamisches Anpassen des Ausgabeformats über CLI, 13. Dynamisches Anpassen der Loggerkonfiguration über CLI, 14. Anpassung der Arbeitsspeicherauslastung über CLI und 15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI
- Datum: 28.12.2023 12:30 Uhr - 13:30 Uhr
- Entwickler\*innen: Alicia Gleichmann
- Code Buddy: Severin Pelikan
- Kontext:
	- Identifier nicht passend gewählt
- Beispiel:
	-  --o_format
- Diagnose:
	- Weniger verständlich, was der Parameter macht
- Aktion:
	- umbenennen
- Sonstiges: 
	- Bisher nur Anpassung des Ausgabeformats und Anpassung der Arbeitsspeicherauslastung angefangen
	- Anpassung des Ausgabeformats fertig bis auf Tests
	- Besprochen, wie alle restlichen Parameter heißen sollen: 
		- --frame-format
		- --log-level oder -l
		- --time-per-block
		- --max-radial-dist und --max-peripheral-dist
- Nächstes Meeting am: 06.01.2024 15:00 Uhr

---

## Statusmeeting 2 zu User Story 8. Entfernen von Nick- und Schwankbewegungen aus Scans
- Datum: 06.01.2024 12:30 Uhr - 13:00 Uhr
- Entwickler\*innen: Severin Pelikan
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
	- Tests gehen nicht durch
	- Herausgefunden die benötigten Daten des IMU-Sensors sind fehlerhaft, deshalb User Storie verworfen


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- kein Abschluss der User Story und keine Änderungen, da die User Story nicht übernommen wird.

---

## Checkliste 2 zu User Storie 9. Integration von Removert in Scan Combiner



## Statusmeeting 2 zu User Story 9. Integration von Removert in Scan Combiner
- Datum: 06.01.2024 10:00 Uhr - 10:30 Uhr
- Entwickler\*innen: Simon Riese
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
	- Code zusammen durchgegangen
	- Keine Probleme in der Dokumentation und auch keine verbotenen Operationen verwendet


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Statusmeeting 2 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 07.01.2024 12:30 Uhr - 14:00 Uhr
- Entwickler\*innen: Severin Pelikan, Greys Fankyeyeva
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
	- Removert läuft auf unseren Daten durch
	- Braucht ziemlich lange zum Durchlaufen
	- Nach dem Durchlauf sind noch semi-dynamische Objekte zu erkennen (Bahn)
		- Übernahme in nächste Iteration


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- User Story wurde in die nächste Iteration übernommen. Änderungen werden bis zum nächsten Code Buddy Meeting umgesetzt. 

---

## Checkliste 2 zu User Storie 11. Docker integration für Zielsystem 



## Statusmeeting 2 zu User Story 11. Docker integration für Zielsystem 
- Datum: 06.01.2024 14:00 Uhr - 14:30 Uhr
- Entwickler\*innen: Leonhard Steinecke
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
	- Docker Container läuft und die Dokumentation ist auch korrekt


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

---

## Checkliste 2 zu User Storie 11. Docker integration für Zielsystem 



## Checkliste 2 zu User Storie 11. Docker integration für Zielsystem 



## Checkliste 2 zu User Storie 11. Docker integration für Zielsystem 



## Checkliste 2 zu User Storie 11. Docker integration für Zielsystem 



## Statusmeeting 2 zu User Story 12. Dynamisches Anpassen des Ausgabeformats über CLI, 13. Dynamisches Anpassen der Loggerkonfiguration über CLI, 14. Anpassung der Arbeitsspeicherauslastung über CLI und 15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI
- Datum: 06.01.2024 15:00 Uhr - 17:30 Uhr
- Entwickler\*innen: Alicia Gleichmann
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
	- Probleme mit Chrono Integration im arx 
		- Tests gingen nicht durch
		- Zusammen fertig implementiert
	- Die anderen User Stories sind Lesbar implementiert und dokumentiert


Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 06.01.2024
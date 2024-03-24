# Statusmeeting Protokolle

#TODO: geplante Userstories löschen, Rechtschreibung prüfen
geplante Userstories:
8. Entfernen von Nick- und Schwankbewegungen aus Scans 2 Push Abgelehnt weil korrupte Daten
9. Integration von Removert in Scan Combiner 2 Push
10. Entfernung dynamischer Objekte mittels Removert 0 Push
11. Docker integration für Zielsystem -  kein C++ 3 Push
12. Dynamisches Anpassen des Ausgabeformats über CLI 2 Push
13. Dynamisches Anpassen der Loggerkonfiguration über CLI 1 Push
14. Anpassung der Arbeitsspeicherauslastung über CLI 2 Push
15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI 1 Push

## Statusmeeting 1 zu User Story 8. Entfernen von Nick- und Schwankbewegungen aus Scans
- Datum: 29.12.2023 12:30 Uhr - 13 Uhr
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
	- Passt alles soweit schon geschrieben
	- Dokumentation bei schon implementierten Teilen großteils fertig und korrekt
	- Noch fertig dokumentieren, aber da erst Zwischenstand ok

## Statusmeeting 1 zu User Story 9. Integration von Removert in Scan Combiner
- Datum: 29.12.2023 10 Uhr - 10:45 Uhr
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
	- Umsetzung bis jetzt sehr ähnlich zu User Story 4 -> keine Fehler
	- Frage zu Kitti Format noch mal nachgeschaut bei KIT wegen Transformationsspeicherung in einem extra Ordner

## Statusmeeting 1 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 29.12.2023 15 Uhr - 15:15 Uhr
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
	- Angefangen den externe Testdatensatz auszuprobieren, scheint bisher gut

## Statusmeeting 1 zu User Story 11. Docker integration für Zielsystem 
- Datum: 29.12.2023 12:30 Uhr - 13 Uhr
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
	- kein C++ Code, deshalb mussten die spezifischen C++ Code Abschnitte in der Checkliste Überspungen werden (gilt auch für zweites Statusmeeting)
	- Sieht bis jetzt gut aus 
	- Dokumentation ist bisher nur Stichpunktartig aber scheint korrekt

## Statusmeeting 1 zu User Story 12. Dynamisches Anpassen des Ausgabeformats über CLI, 13. Dynamisches Anpassen der Loggerkonfiguration über CLI, 14. Anpassung der Arbeitsspeicherauslastung über CLI und 15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI
- Datum: 28.12.2023 12:30 Uhr - 13:30 Uhr
- Entwickler\*innen: Alicia Gleichmann
- Code Buddy: Severin Pelikan
- Kontext:
	- 
- Beispiel:
- Diagnose:
- Aktion:
- Sonstiges: 
	- Bisher nur Anpassung des Ausgabeformats und Anpassung der Arbeitsspeicherauslastung angefangen
	- Anpassung des Ausgabeformats fertig bis auf Tests
	- 

## Statusmeeting 2 zu User Story 8. Entfernen von Nick- und Schwankbewegungen aus Scans
- Datum: 6.1.2024 12:30 Uhr - 13 Uhr
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
	- Herausgefunden die benötigten Daten zum Winkel der Tram sind Fehlerhaft, deshalb User Storie verworfen
---
- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- kein Abschluss der User Story und keine Änderungen, da die User Story nicht übernommen wird.

## Statusmeeting 2 zu User Story 9. Integration von Removert in Scan Combiner
- Datum: 6.1.2024 10 Uhr - 10:30 Uhr
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
---
- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

## Statusmeeting 2 zu User Story 10. Entfernung dynamischer Objekte mittels Removert
- Datum: 7.1.2024 12:30 Uhr - 14 Uhr
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
	- Braucht ziemlich lange zum durchlaufen
	- Ist das erste mal abgestürzt
	- Nach dem durchlauf sind noch semi-dynamische Objekte zu erkennen (Bahn)
		- Übernahme in nächste Iteration
---
- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 
	- User Story wurde in die nächste Iteration übernommen. Änderungen werden bis zum nächsten Code Buddy Meeting umgesetzt. 

## Statusmeeting 2 zu User Story 11. Docker integration für Zielsystem 
- Datum: 6.1.2024 14 Uhr - 14:30 Uhr
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
---
- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: -

## Statusmeeting 2 zu User Story 12. Dynamisches Anpassen des Ausgabeformats über CLI, 13. Dynamisches Anpassen der Loggerkonfiguration über CLI, 14. Anpassung der Arbeitsspeicherauslastung über CLI und 15. Dynamisches Anpassen der maximalen radialen und peripheren Distanzen über CLI
- Datum: 6.1.2024 15 Uhr - 17:30 Uhr
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
	- 
---
- Umsetzung der besprochenen Änderungen vor Abschluss der User Story am: 